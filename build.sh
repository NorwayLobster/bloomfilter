rm -rf ../build
mkdir ../build
cd ../build
cmake ../buildPagesInvertedIndex
make -j
make install
