cd Sources/quazip
rm quazip/zconf.h quazip/zlib.h
mkdir build
cd build
cmake ..
make
sudo make install
cd ../../..
