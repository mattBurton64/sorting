#!/bin/bash
# This script is designed to compile and test the various different parameter passing programs in both C++ and Java

### COMPILING ###
echo -e "Compiling programs\n==================" # section header
./Script/compile.sh cpp value # compiles the value.cpp program
./Script/compile.sh cpp reference # compiles the reference.cpp program
./Script/compile.sh cpp value-result # compiles the value-result.cpp program
#./Script/compile.sh cpp name # compiles the name.cpp program
#./Script/compile.sh cpp result # compiles the result.cpp program
#./Script/compile.sh cpp scope # compiles the scope.cpp program
#./Script/compile.sh cpp alias # compiles the alias.cpp program
#./Script/compile.sh cpp side-effect # compiles the side-effect.cpp program

./Script/compile.sh java value # compiles the value.java program
#./Script/compile.sh java reference # compiles the reference.java program
#./Script/compile.sh java value-result # compiles the value-result.java program
#./Script/compile.sh java name # compiles the name.java program
#./Script/compile.sh java result # compiles the result.java program
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
echo -e "\nvalue.java" # program label
cd ./Source/java
java Value # runs the test

#echo -e "\nreference.java" # program label
#Reference # runs the test

#echo -e "\nvalue-result.java" # program label
#Value-result # runs the test

#echo -e "\nname.java" # program label
#Name # runs the test

#echo -e "\nresult.java" # program label
#Result # runs the test

#echo -e "\nscope.java" # program label
#Scope # runs the test

#echo -e "\nalias.java" # program label
#Alias # runs the test

#echo -e "\nside-effect.java" # program label
#Side-effect # runs the test

echo "Testing complete"
exit # success
