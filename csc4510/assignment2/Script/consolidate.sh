#!/bin/bash
# This script is designed to compile and test the various different parameter passing programs in both C++ and Java

### COMPILING ###
echo -e "Compiling programs\n==================" # section header
./Script/compile.sh cpp value # compiles the value.cpp program
./Script/compile.sh cpp reference # compiles the reference.cpp program
./Script/compile.sh cpp value-result # compiles the result.cpp program
./Script/compile.sh cpp scope # compiles the scope.cpp program
./Script/compile.sh cpp alias # compiles the alias.cpp program
./Script/compile.sh cpp delete # compiles the delete.cpp program


./Script/compile.sh java Value # compiles the value.java program
#./Script/compile.sh java Reference # compiles the reference.java program
./Script/compile.sh java ValueResult # compiles the value-result.java program
./Script/compile.sh java Scope # compiles the scope.java program
#./Script/compile.sh java Alias # compiles the alias.java program
#./Script/compile.sh java Side-effect # compiles the side-effect.java program

### TESTING ###
echo -e "\nTesting\n=======" # section header
# C++
echo "value.cpp" # program label
./Source/cpp/value.o # runs the test

echo -e "\nreference.cpp" # program label
./Source/cpp/reference.o # runs the test

echo -e "\nvalue-result.cpp" # program label
./Source/cpp/value-result.o # runs the test

echo -e "\nscope.cpp" # program label
./Source/cpp/scope.o # runs the test

echo -e "\nalias.cpp" # program label
./Source/cpp/alias.o # runs the test

echo -e "\ndelete.cpp" # program label
./Source/cpp/delete.o # runs the test

# Java
echo -e "\nValue.java" # program label
cd ./Source/java
java Value # runs the test

#echo -e "\nReference.java" # program label # Java does not support passing by reference for primitives
#java Reference # runs the test

echo -e "\nValueResult.java" # program label
java ValueResult # runs the test

echo -e "\nScope.java" # program label
java Scope # runs the test

#echo -e "\nAlias.java" # program label # Java does not support pointers so you can't have multiple variables referencing the same memory locations
#java Alias # runs the test

echo "Testing complete"
exit # success
