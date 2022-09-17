#include <jsonwork.hpp>

#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonParseError>
#include <QJsonObject>

#include <QFuture>
#include <QtConcurrent>
#include <QDir>
#include <QFile>

#define RESULT_FOLDER_NAME "result"

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
        auto json_arr = doc[key_1].toArray();

        for (auto it = json_arr.cbegin(); it != json_arr.cend(); ++it)
        {
            auto pkg_name = QJsonValue(*it)[key_2].toString();
            auto pkg_version = QJsonValue(*it)[key_3].toString();

            pkg_names_and_versions[pkg_name] = pkg_version;
        }
    }

    return pkg_names_and_versions;
}

/**
 * @brief JsonWork::getUniquePkgsToWrite
 * Parses the response from the server to get packages whose names
 * match the names from the @p uniquePkgNames, adding them to a class
 * variable, for further work with this data.
 * @param uniquePkgNames
 */
void JsonWork::getUniquePkgsToWrite(const QStringList& uniquePkgNames)
{
    QJsonDocument doc;
    QJsonParseError parse_error;

    doc = QJsonDocument::fromJson(_json_data.toUtf8(), &parse_error);

    if (parse_error.errorString().toInt() == QJsonParseError::NoError)
    {
        auto pkgs_arr = doc["packages"].toArray();

        for (auto it = pkgs_arr.cbegin(); it != pkgs_arr.cend(); ++it)
        {
            _data_to_write.append(*it);
        }

        _cnt_unique_pkg_names = uniquePkgNames.size();
    }
}

/**
 * @brief JsonWork::writeToJsonFile
 * Writes data to a json file in a separate thread and displays
 * information about the readiness.
 * @param arch
 * @param entryName
 * @todo Add a ready message to be printed during the execution of the
 * thread that writes the data.
 */
void JsonWork::writeToJsonFile(const QString& arch, const QString& entryName) const
{
    QFuture<void> future = QtConcurrent::run(this,
                                             &JsonWork::writeToJsonFileAsync,
                                             arch,
                                             entryName
                                             );
    while (future.isRunning())
    {
        qInfo() << "Writing...";
    }
    qInfo() << "Data for the " << arch << " architecture is written.";
}

/**
 * @brief JsonWork::writeToJsonFileAsync
 * Write @p arch architecture packages to a json file by the @p entryName
 * key.
 * @param arch
 * @param entryName
 */
void JsonWork::writeToJsonFileAsync(const QString& arch,
                                    const QString& entryName) const
{
    QDir dir("");
    if (!dir.exists(RESULT_FOLDER_NAME))
    { dir.mkdir(RESULT_FOLDER_NAME); }
    dir.setPath(QString("%1/%2").arg(dir.currentPath(), RESULT_FOLDER_NAME));

    QFile fout(QString("%1/%2.json").arg(dir.path(), arch));
    if (fout.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QJsonDocument doc;
        QJsonParseError parse_error;

        doc = QJsonDocument::fromJson(fout.readAll(), &parse_error);

        if (parse_error.errorString().toInt() == QJsonParseError::NoError)
        {
            auto cur_data(doc.object());

            QJsonObject json_pkgs{ {"packages", _data_to_write} };
            json_pkgs["length"] = _cnt_unique_pkg_names;

            cur_data[entryName] = json_pkgs;

            fout.reset();
            fout.write(QJsonDocument(cur_data).toJson());
        }

        fout.close();
    }
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
        auto json_arr = doc[key_1].toArray();

        for (auto it = json_arr.cbegin(); it != json_arr.cend(); ++it)
        {
            list_name_pkgs.append(QJsonValue(*it)[key_2].toString());
        }
    }

    return list_name_pkgs;
}
