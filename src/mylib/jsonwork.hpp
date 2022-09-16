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

signals:

private:
    QString _json_data;
};

#endif // JSONWORK_H
