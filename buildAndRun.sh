#clear terminal
clear
rm ./bin/main

# build steps
mkdir build
cd build
make clean
cmake ..
make
cd ..
rm -rf build

# run
./bin/main ./tests/binDataLast.asm