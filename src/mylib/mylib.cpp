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

/**
 * @brief Mylib::getUniquePkgs
 * Looks for unique packages for both branches and then sets
 * them to the corresponding branch's class variable.
 * @param arch
 */
void Mylib::getUniquePkgs(const QString& arch)
{
    QStringList pkg_names_1 = _branch1.getPkgNames(arch);
    QStringList pkg_names_2 = _branch2.getPkgNames(arch);

    QStringList unique_pkg_names_fst_branch;
    for (auto&& name : pkg_names_1)
    {
        if (!pkg_names_2.contains(name))
        {
            unique_pkg_names_fst_branch.append(name);
        }
    }

    QStringList unique_pkg_names_scnd_branch;
    for (auto&& name : pkg_names_1)
    {
        if (!pkg_names_1.contains(name))
        {
            unique_pkg_names_scnd_branch.append(name);
        }
    }

    _branch1.setUniquePkgNames(unique_pkg_names_fst_branch);
    _branch2.setUniquePkgNames(unique_pkg_names_scnd_branch);
}
