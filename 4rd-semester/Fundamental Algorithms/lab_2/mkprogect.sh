mkdir $1

mkdir $1/bin
mkdir $1/install
mkdir $1/datasets
mkdir $1/src
touch $1/main.cpp
touch $1/makefile
touch $1/README.md

echo "FLAG = -O2 -Wall -Werror -Wextra -std=c++17" > $1/makefile
echo "clean: " > $1/makefile
echo "rm bin/*.o" > $1/makefile
echo "check:" > $1/makefile
echo "@cppcheck -j4 --enable=performance,portability,warning,style npp.6.5.3. src/" > $1/makefile
echo "@cppcheck -j4 --enable=performance,portability,warning,style npp.6.5.3. main.cpp" > $1/makefile
