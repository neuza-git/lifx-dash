####  Sniffer part from tcpdump page https://www.tcpdump.org/pcap.html
#### And everything else except the main and some modifications from https://github.com/ArquintL/lifx-c-lib

#### Installation
you can clone then just do (I gotta create a new Makefile I know...)
make

### Dependence :

It requires the libcap library :
(other you'll get this error : pcap.h: No such file or directory

For ubuntu/debian (remove sudo if you don't have it)
sudo apt-get install libcap-dev

For redhat based distros :
yum install libpcap-devel
