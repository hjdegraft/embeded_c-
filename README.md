edcontrol

LED Daemon for S5
Setup Environment
Ubuntu 17.10

sudo apt-get install build-essential git

OSX

TBD

Setup Source Tree

repo init -m ledcontrol.xml -u git@github.com:DensityCo/embed-ledcontrol.git -b trunk
repo sync

Build Project

mkdir build
cd build
cmake ..
make
