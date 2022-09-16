#include <QCoreApplication>

#include <mylib.hpp>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Mylib lib("sisyphus", "p10");

    return a.exec();
}
