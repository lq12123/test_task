#ifndef BRANCH_H
#define BRANCH_H

#include <QObject>
#include <QUrl>

#define RESTAPI_URL "https://rdb.altlinux.org/api"
#define RESTAPI_ALL_ARCHS "site/all_pkgset_archs"
#define RESTAPI_ADDR "https://rdb.altlinux.org/api/export/" \
                     "branch_binary_packages"

class Branch : public QObject
{
    Q_OBJECT
public:
    explicit Branch(const QString& branchName, QObject *parent = nullptr);

    QStringList getArchs();

signals:

private:
    QString _branch_name;
    QStringList _supported_archs;

    QString sendQuery(const QUrl& url) const;
    void getSupportedArchs();
};

#endif // BRANCH_H
