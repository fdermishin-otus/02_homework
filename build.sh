mkdir ./build
cd ./build
cmake -DBUILD_TESTING=$1 ../
cmake --build .
cmake --build . --target $2
