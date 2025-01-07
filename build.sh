cd /home/mikkel/repos/MDV
rm -rf build
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=../windows-x64-toolchain.cmake
cmake --build . --parallel 6

