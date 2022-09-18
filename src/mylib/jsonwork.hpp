#ifndef JSONWORK_H
#define JSONWORK_H

#include <QObject>
#include <QHash>
#include <QJsonArray>

class JsonWork : public QObject
{
    Q_OBJECT
public:
    explicit JsonWork(const QString& jsonData, QObject *parent = nullptr);

    QHash<QString, QString> getPkgNamesAndVersions(const QString& key_1,
                                                   const QString& key_2,
                                                   const QString& key_3) const;
    QStringList getData(const QString& key_1, const QString& key_2) const;

    void getUniquePkgsToWrite(const QStringList& uniquePkgNames);
    void writeToJsonFile(const QString& arch, const QString& entryName,
                         const QString& folderName) const;

signals:

private:
    QString _json_data;
    QJsonArray _data_to_write;
    qint32 _cnt_unique_pkg_names;

    void writeToJsonFileAsync(const QString& arch,
                              const QString& entryName,
                              const QString& folderName
                              ) const;
};

#endif // JSONWORK_H
