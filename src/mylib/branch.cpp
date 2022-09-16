#include "branch.h"

#include <QUrlQuery>
#include "loader.hpp"
#include "jsonwork.h"

Branch::Branch(const QString& branchName, QObject* parent)
    : QObject{parent}, _branch_name{branchName} {}

/**
 * @brief Branch::getArchs
 * @return a list of supported architectures.
 */
QStringList Branch::getArchs()
{
    getSupportedArchs();
    return _supported_archs;
}

/**
 * @brief Branch::getSupportedArchs
 * Sends a request to the specified address to get the
 * architectures supported by the branch.
 */
void Branch::getSupportedArchs()
{
    QUrl target_url(QString("%1/%2").arg(RESTAPI_URL,
                                         RESTAPI_ALL_ARCHS));
    QUrlQuery query;
    query.addQueryItem("branch", _branch_name);
    target_url.setQuery(query);

    QString response(sendQuery(target_url));
    JsonWork json_parse(response);

    _supported_archs = json_parse.getData("archs", "arch");
}

/**
 * @brief Branch::sendQuery
 * @param url
 * @return the response received from the server to the request sent
 * to the @p url.
 */
QString Branch::sendQuery(const QUrl& url) const
{
    Loader loader(url);

    return loader.sendQuery();
}
