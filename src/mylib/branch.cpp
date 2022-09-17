#include <branch.hpp>

#include <QUrlQuery>
#include <loader.hpp>
#include <jsonwork.hpp>

#define RESTAPI_URL "https://rdb.altlinux.org/api"
#define RESTAPI_ALL_ARCHS "site/all_pkgset_archs"

#define RESTAPI_ADDR "https://rdb.altlinux.org/api/export/" \
                     "branch_binary_packages"

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

    auto response(sendQuery(target_url));
    JsonWork json_parse(response);

    _supported_archs = json_parse.getData("archs", "arch");
}

/**
 * @brief Branch::setUniquePkgNames
 * Sets a list of unique package names specific to this branch.
 * @param pkgNames
 */
void Branch::setUniquePkgNames(const QStringList& pkgNames)
{
    _unique_pkg_names = pkgNames;
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

/**
 * @brief Branch::getAllPackages
 * Adds parameters to the url and sends a request to get all
 * the @p arch architecture packages.
 * @param arch
 * @return a list of all @p arch architecture packages.
 */
QString Branch::getAllPackages(const QString& arch) const
{
    QUrl url(QString("%1/%2").arg(RESTAPI_ADDR, _branch_name));
    Loader loader(url);
    loader.addQueryParam("arch", arch);

    return loader.sendQuery();
}

/**
 * @brief Branch::getPkgNamesAndVersions
 * Gets a dictionary containing the package name (key) and
 * version (value) for the @p arch architecture.
 * @param arch
 */
void Branch::getPkgNamesAndVersions(const QString& arch)
{
    _response = getAllPackages(arch);
    JsonWork json_parser(_response);

    _pkg_names_and_versions = json_parser.getPkgNamesAndVersions("packages",
                                                                 "name",
                                                                 "version");
}

/**
 * @brief Branch::getPkgNames
 * Gets the package names from a dictionary containing the
 * package name and version for the @p arch architecture.
 * @param arch
 * @return a list of package names for @p arch architecture.
 */
QStringList Branch::getPkgNames(const QString& arch)
{
    getPkgNamesAndVersions(arch);

    QStringList pkg_names;

    auto keys = _pkg_names_and_versions.keys();
    for (auto&& key : keys)
    {
        pkg_names.append(key);
    }

    return pkg_names;
}

/**
 * @brief Branch::getResponse
 * @return the response that the server returned.
 */
QString Branch::getResponse() const
{
    return _response;
}

/**
 * @brief Branch::getUniquePkgNames
 * @return a list of unique package names.
 */
QStringList Branch::getUniquePkgNames() const
{
    return _unique_pkg_names;
}

/**
 * @brief Branch::getPkgNamesAndVersions
 * @return a dictionary containing package names and their
 * versions.
 */
QHash<QString, QString> Branch::getPkgNamesAndVersions() const
{
    return _pkg_names_and_versions;
}
