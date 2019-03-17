Sniffer part from tcpdump page https://www.tcpdump.org/pcap.html
And everything else except the main and some modifications from https://github.com/ArquintL/lifx-c-lib



It requires the libcap library :
(other you'll get this kind of error : pcap.h: No such file or directory

for ubuntu/debian (remove sudo if your debian doesn't have it)
you can do the following to intsall it :

sudo apt-get install libcap-dev
