#ifndef BRANCH_H
#define BRANCH_H

#include <QObject>
#include <QUrl>
#include <QHash>

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
    QStringList getPkgNames(const QString& arch);

    void setUniquePkgNames(const QStringList& pkgNames);

signals:

private:
    QString _response;
    QString _branch_name;
    QStringList _supported_archs;
    QStringList _unique_pkg_names;
    QHash<QString, QString> _pkg_names_and_versions;

    QString sendQuery(const QUrl& url) const;
    QString getAllPackages(const QString& arch) const;

    void getSupportedArchs();
    void getPkgNamesAndVersions(const QString& arch);
};

#endif // BRANCH_H
