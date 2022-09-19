#include <mylib.hpp>
#include <jsonwork.hpp>

#define OUTPUT_FOLDER "result" // the resulting default folder

Mylib::Mylib(const QString& branch1, const QString& branch2,
             const QString& outputFolderName, QObject* parent)
    : QObject{parent}, _branch1{branch1}, _branch2{branch2}
{
    if (outputFolderName.size())
    {
        _output_folder_name = outputFolderName;
    }
    else
    {
        _output_folder_name = OUTPUT_FOLDER;
    }
}

/**
 * @brief Mylib::compare
 * Iterates over the common architectures of both branches
 * and compares branches, looking for unique packages for each
 * branch, and also compares package versions.
 */
void Mylib::compare()
{
    auto archs = getCommonArchs();

    for (auto&& arch : archs)
    {
        compareBranches(arch);
        compareVersions(arch);
    }

    QTextStream(stdout) << "Done!" << Qt::endl;
}

/**
 * @brief Mylib::getCommonArchs
 * @return a list of common architectures supported by both
 * branches.
 */
QStringList Mylib::getCommonArchs()
{
    QStringList common_archs;

    auto branch_archs_1 = _branch1.getArchs();
    auto branch_archs_2 = _branch2.getArchs();

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
    auto pkg_names_1 = _branch1.getPkgNames(arch);
    auto pkg_names_2 = _branch2.getPkgNames(arch);

    QStringList unique_pkg_names_fst_branch;
    for (auto&& name : pkg_names_1)
    {
        if (!pkg_names_2.contains(name))
        {
            unique_pkg_names_fst_branch.append(name);
        }
    }

    QStringList unique_pkg_names_scnd_branch;
    for (auto&& name : pkg_names_2)
    {
        if (!pkg_names_1.contains(name))
        {
            unique_pkg_names_scnd_branch.append(name);
        }
    }

    _branch1.setUniquePkgNames(unique_pkg_names_fst_branch);
    _branch2.setUniquePkgNames(unique_pkg_names_scnd_branch);
}

/**
 * @brief Mylib::compareBranches
 * Performs a comparison of two branches, and then writes the
 * unique packages of each branch to a json file under the keys
 * "uniquePkgsInFirstBranch" and "uniquePkgsInSecondBranch".
 * @param arch
 */
void Mylib::compareBranches(const QString& arch)
{
    getUniquePkgs(arch);

    JsonWork json_worker_1(_branch1.getResponse());
    JsonWork json_worker_2(_branch2.getResponse());

    json_worker_1.getUniquePkgsToWrite(_branch1.getUniquePkgNames());
    json_worker_2.getUniquePkgsToWrite(_branch2.getUniquePkgNames());

    json_worker_1.writeToJsonFile(arch,
                                  "uniquePkgsInFirstBranch",
                                  _output_folder_name);
    json_worker_2.writeToJsonFile(arch,
                                  "uniquePkgsInSecondBranch",
                                  _output_folder_name);
}

/**
 * @brief Mylib::compareVersions
 * Selects common @p arch architecture packages, the version
 * of which in the first branch is greater than in the second,
 * then writes their json file using the "largerVersionPkgs"
 * key.
 * @param arch
 */
void Mylib::compareVersions(const QString& arch)
{
    // the names and versions of the packages of the first branch
    auto pkg_fst_branch =
           _branch1.getPkgNamesAndVersions();

    // the names and versions of the packages of the second branch
    auto pkg_scnd_branch =
           _branch2.getPkgNamesAndVersions();

    QStringList result_pkg_names;

    auto pkg_names = pkg_fst_branch.keys();
    for (auto&& pkg_name : pkg_names)
    {
        auto pkg_version_1 = pkg_fst_branch[pkg_name];
        auto pkg_version_2 = pkg_scnd_branch[pkg_name];

        if (!pkg_version_1.isEmpty() && !pkg_version_2.isEmpty() &&
                pkg_version_1 > pkg_version_2)
        {
            result_pkg_names.append(pkg_name);
        }
    }

    JsonWork json_worker(_branch1.getResponse());

    json_worker.getUniquePkgsToWrite(result_pkg_names);

    json_worker.writeToJsonFile(arch,
                                "largerVersionPkgs",
                                _output_folder_name);
}
