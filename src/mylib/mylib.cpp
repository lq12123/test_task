#include <mylib.hpp>

Mylib::Mylib(const QString& branch1, const QString& branch2,
             QObject* parent)
    : QObject{parent}, _branch1{branch1}, _branch2{branch2} {}


void Mylib::compare()
{}

/**
 * @brief Mylib::getCommonArchs
 * @param arch
 * @return a list of common architectures supported by both
 *  branches.
 */
QStringList Mylib::getCommonArchs(const QString& arch)
{
    QStringList common_archs;

    QStringList branch_archs_1 = _branch1.getArchs();
    QStringList branch_archs_2 = _branch2.getArchs();

    for (auto&& arch : branch_archs_1)
    {
        if (branch_archs_2.contains(arch))
        {
            common_archs.append(arch);
        }
    }

    return common_archs;
}
