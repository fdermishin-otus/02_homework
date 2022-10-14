mkdir ./build
cd ./build
cmake -DPATCH_VERSION=$1 -DBUILD_TESTING=$2 ../
cmake --build .
cmake --build . --target $3
