echo "Updating submodules..."
git submodule update --init --recursive

echo "Building Boost.Build..."
cd external/boost/
./bootstrap.sh
./b2
./b2 headers

echo "Building project..."
cd ../../
if [ ! -d "build" ]; then
  mkdir build
fi
cd build
echo "Removing everything in build..."
rm -rf *
echo "Building project..."
cmake ..
make
echo "Done building project."
