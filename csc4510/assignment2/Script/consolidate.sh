#!/bin/bash
# This script is designed to compile and test the various different parameter passing programs in both C++ and Java

### COMPILING ###
echo -e "Compiling programs\n==================" # section header
./Script/compile.sh cpp value # compiles the value.cpp program
./Script/compile.sh cpp reference # compiles the reference.cpp program
./Script/compile.sh cpp value-result # compiles the result.cpp program
#./Script/compile.sh cpp scope # compiles the scope.cpp program
#./Script/compile.sh cpp alias # compiles the alias.cpp program
#./Script/compile.sh cpp side-effect # compiles the side-effect.cpp program

./Script/compile.sh java Value # compiles the value.java program
./Script/compile.sh java Reference # compiles the reference.java program
./Script/compile.sh java ValueResult # compiles the value-result.java program
#./Script/compile.sh java scope # compiles the scope.java program
#./Script/compile.sh java alias # compiles the alias.java program
#./Script/compile.sh java side-effect # compiles the side-effect.java program

### TESTING ###
echo -e "\nTesting\n=======" # section header
# C++
echo "value.cpp" # program label
./Source/cpp/value.o # runs the test

echo -e "\nreference.cpp" # program label
./Source/cpp/reference.o # runs the test

echo -e "\nvalue-result.cpp" # program label
./Source/cpp/value-result.o # runs the test

#echo -e "\nname.cpp" # program label
#./Source/cpp/name.o # runs the test

#echo -e "\nresult.cpp" # program label
#./Source/cpp/result.o # runs the test

#echo -e "\nscope.cpp" # program label
#./Source/cpp/scope.o # runs the test

#echo -e "\nalias.cpp" # program label
#./Source/cpp/alias.o # runs the test

#echo -e "\nside-effect.cpp" # program label
#./Source/cpp/side-effect.o # runs the test

# Java
echo -e "\nValue.java" # program label
cd ./Source/java
java Value # runs the test

echo -e "\nReference.java" # program label
java Reference # runs the test

echo -e "\nValueResult.java" # program label
java ValueResult # runs the test

#echo -e "\nName.java" # program label
#java Name # runs the test

#echo -e "\nResult.java" # program label
#java Result # runs the test

#echo -e "\nScope.java" # program label
#java Scope # runs the test

#echo -e "\nAlias.java" # program label
#java Alias # runs the test

#echo -e "\nSide-effect.java" # program label
#java Side-effect # runs the test

echo "Testing complete"
exit # success
