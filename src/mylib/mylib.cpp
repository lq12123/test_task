#include "mylib.h"

#include <QDebug>

Mylib::Mylib(const QString& branch_1, const QString& branch_2,
             QObject* parent)
    : QObject{parent} {}
