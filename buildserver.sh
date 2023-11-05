echo "Updating package lists"
apt-get update
echo "Installing boost lib"
apt-get install -y libboost-all-dev
echo "Installing cmake"
apt-get install -y cmake
echo "Installing libconfig"
apt-get install -y libconfig++-dev

echo "Making the makefile"
make