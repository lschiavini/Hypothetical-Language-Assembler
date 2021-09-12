# build steps
mkdir build
cd build
make clean
cmake ..
make
cd ..
rm -rf build
# run
./bin/main ./filetest.asm

