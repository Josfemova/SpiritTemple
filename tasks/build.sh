cd Server 
rm -rf build
mkdir build
cd build
cmake ..
cd ..
cmake --build build/ --config Release
cd ..
Server/build/server