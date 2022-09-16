#include <jsonwork.hpp>

#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonParseError>
#include <QJsonObject>

JsonWork::JsonWork(const QString& jsonData, QObject* parent)
    : QObject{parent}, _json_data{jsonData} {}

/**
 * @brief JsonWork::getPkgNamesAndVersions
 * Parses the data passed to the json method (@p key_1) extracting
 * package names and versions from them.
 * @param key_1
 * @param key_2
 * @param key_3
 * @return a QHash containing the package name (key) and version (value).
 */
QHash<QString, QString> JsonWork::getPkgNamesAndVersions(const QString& key_1,
                                                   const QString& key_2,
                                                   const QString& key_3) const
{
    QJsonDocument doc;
    QJsonParseError parse_error;

    doc = QJsonDocument::fromJson(_json_data.toUtf8(), &parse_error);

    QStringList list_name_pkgs;

    // key: pkg name, value: pkg version
    QHash<QString, QString> pkg_names_and_versions;

    if (parse_error.errorString().toInt() == QJsonParseError::NoError)
    {
        QJsonArray json_arr = doc[key_1].toArray();

        for (auto it = json_arr.cbegin(); it != json_arr.cend(); ++it)
        {
            QString pkg_name = QJsonValue(*it)[key_2].toString();
            QString pkg_version = QJsonValue(*it)[key_2].toString();

            pkg_names_and_versions[pkg_name] = pkg_version;
        }
    }

    return pkg_names_and_versions;
}

/**
 * @brief JsonWork::getData
 * Parses json data and gets a list of values for the specified keys.
 * @param key_1
 * @param key_2
 * @return a list QStringList of elements given the keys @p key_1 and @p key_2.
 */
QStringList JsonWork::getData(const QString& key_1, const QString& key_2) const
{
    QJsonDocument doc;
    QJsonParseError parse_error;

    doc = QJsonDocument::fromJson(_json_data.toUtf8(), &parse_error);

    QStringList list_name_pkgs;

    if (parse_error.errorString().toInt() == QJsonParseError::NoError)
    {
        QJsonArray json_arr = doc[key_1].toArray();

        for (auto it = json_arr.cbegin(); it != json_arr.cend(); ++it)
        {
            list_name_pkgs.append(QJsonValue(*it)[key_2].toString());
        }
    }

    return list_name_pkgs;
}
