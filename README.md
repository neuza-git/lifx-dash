####  Sniffer part from tcpdump page https://www.tcpdump.org/pcap.html
#### And everything else except the main and some modifications from https://github.com/ArquintL/lifx-c-lib


### Installation :
you can clone then just do _(I gotta create a new Makefile I know...)_
make



### How to start :
./listendash

_(for now it just run and listen for the traffic you can ctrl-c to quit but it does require to be run in background using for example [using the screen package that I find very easy to use](https://linuxize.com/post/how-to-use-linux-screen/))_



### Dependence :
It requires the *libpcap developer library* : (otherwise you'll get this error : pcap.h: No such file or directory)


For ubuntu/debian (remove sudo if you don't have it) :

sudo apt-get install libcap-dev


For redhat based distros :

yum install libpcap-devel
