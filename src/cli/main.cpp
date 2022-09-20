#include <QCoreApplication>

#include <getopt.h>
#include <mylib.hpp>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <version.h>

#define BUFSIZE 32

void printHelp()
{
    std::cout << "DESCRIPTION\n" <<
                 "\tThe program compares two branches passed to it as input, "
                 "obtained through the '/export/branch_binary_packages/"
                 "{branch}' method of the public REST API "
                 "'https://rdb.altlinux.org/api', searching for unique "
                 "packages of branch 1, the version of which is greater "
                 "than the version of the packages of branch 2.\n\n\tAt the end, "
                 "the program writes the result to a json file with the name "
                 "of the architecture to which the listed packages "
                 "belong." << std::endl;
    std::cout << "\nPARAMS\n" <<
                 "\t-h, --help        - information about the program\n" <<
                 "\t-v, --version     - the current version of the program\n" <<
                 "\t-b1 <branch name> - the name of the first branch\n" <<
                 "\t-b2 <branch name> - the name of the second branch\n" <<
                 "\t-o, --output      - path to the folder where the result " <<
                 "of the program will be saved. By default, if the " <<
                 "parameter is not specified, the result is saved to the " <<
                 "'result' folder of the current directory\n";
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    char branch_name_1[BUFSIZE+1];
    char branch_name_2[BUFSIZE+1];
    char output_folder[BUFSIZE+1];

    struct option opts[] = {
        {"help",    no_argument,	   0, 'h'},
        {"version", no_argument, 	   0, 'v'},
        {"output",  required_argument, 0, 'o'}
    };

    int branch_cnt = 0;
    int opchar     = 0;

    while( -1 != (opchar = getopt_long(argc, argv, "hvbo:1:2:", opts, nullptr)) )
    {
        switch(opchar)
        {
        case 'h':
            printHelp();
            return EXIT_SUCCESS;
        case 'v':
            std::cout << "Current program version: " << g_cur_version << std::endl;
            return EXIT_SUCCESS;
        case 'b':
            break;
        case '1':
            if (branch_cnt != 2)
            { sprintf(branch_name_1, "%s", optarg); ++branch_cnt; }
            break;
        case '2':
            if (branch_cnt != 2)
            { sprintf(branch_name_2, "%s", optarg); ++branch_cnt; }
            break;
        case 'o':
            sprintf(output_folder, "%s", optarg);
            break;
        default:
            std::cout << "Invalid parameters passed!" << std::endl;
        }
    }

    if (opterr)
    {
        if (branch_cnt < 2)
        {
            std::cout << "Specify names for both branches." << std::endl;
        } else
        {
            Mylib lib(branch_name_1, branch_name_2, output_folder);
            lib.compare();
        }
    }

    return a.exec();
}
