rm -rf ../build
mkdir ../build
cd ../build
cmake ../bloomfilter
make -j
make install
