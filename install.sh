make clean
make
sudo rmmod ones
sudo insmod ones.ko
sudo rm -rf /dev/ones
sudo mknod /dev/ones c 247 1
sudo chmod a+w+r /dev/ones
