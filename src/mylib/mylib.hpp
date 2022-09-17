#ifndef MYLIB_H
#define MYLIB_H

#include <QtCore/qglobal.h>
#include <QObject>
#include <branch.hpp>

#if defined(MYLIB_LIBRARY)
#  define MYLIB_EXPORT Q_DECL_EXPORT
#else
#  define MYLIB_EXPORT Q_DECL_IMPORT
#endif

class MYLIB_EXPORT Mylib : public QObject
{
    Q_OBJECT

public:
    explicit Mylib(const QString& branch1, const QString& branch2,
                   QObject* parent = nullptr);

    void compare();
private:
    Branch _branch1;
    Branch _branch2;

    QStringList getCommonArchs(const QString& arch);

    void getUniquePkgs(const QString& arch);
    void compareBranches(const QString& arch);
    void compareVersions(const QString& arch);
};

#endif // MYLIB_H
