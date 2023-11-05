echo "Updating submodules..."
git submodule update --init --recursive

echo "Building project..."
if [ ! -d "build" ]; then
  mkdir build
fi
cd build
echo "Removing everything in build..."
sudo rm -rf *
echo "Building project..."
cmake ..
make
echo "Done building project."
