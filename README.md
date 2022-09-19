# test_task
![qt5](https://img.shields.io/badge/QT-5.15.2-brightgreen) ![qt5](https://img.shields.io/badge/QT-6-brightgreen) ![openssl](https://img.shields.io/badge/OpenSSL-1.1.1x-brightgreen) ![platform](https://img.shields.io/badge/platform-linux-orange)
___
Shared library for working with [REST API](https://rdb.altlinux.org/api/). Searches for unique packages for each of the two branches, and also looks for packages whose version is greater in the first branch than in the second. The result of the work is written to a json file with the name of the architecture to which the selected packages belong.
## Build from source
## Requirements
+ **Recommended Qt 5.x.x or Qt 6**
+ **Cmake v3.2 <=**
+ **OpenSSL v1.1.1x**
+ **The GNU toolchain**
+ **GNU make**

**NOTE**: The project contains a script to download the required OpenSSL version (only works for Linux).
## Building
	git clone https://github.com/lq12123/test_task.git
	cd test_task
	mkdir build && cd build
	cmake ..
	cmake --build .
___
## Installation
	git clone https://github.com/lq12123/test_task.git
	cd test_task
	cmake ..
	make install
## CLI Usage
	cli -b1 [branch_1] -b2 [branch_2] -o [RESULTING PATH]
*RESULTING PATH* - path where to save the result of the program. By default, the result is saved in a folder called "result".

*branch_1* - the name of the first branch.

*branch_2* - the name of the first branch.

Type "-v"or "--version" to find out the current version of the program. Use the "-h" or "--help" option to get help about the program.
