#ifndef MYLIB_H
#define MYLIB_H

#include <QtCore/qglobal.h>
#include <QObject>

#include <QNetworkReply>

#if defined(MYLIB_LIBRARY)
#  define MYLIB_EXPORT Q_DECL_EXPORT
#else
#  define MYLIB_EXPORT Q_DECL_IMPORT
#endif

class MYLIB_EXPORT Mylib : public QObject
{
    Q_OBJECT

public:
    explicit Mylib(const QString& branch_1, const QString& branch_2,
                   QObject* parent = nullptr);

    void compare();
    void Test() const;

private:
};

#endif // MYLIB_H
