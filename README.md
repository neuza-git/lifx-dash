# This code allow you to use your amazon dash buttons to toggle the power of your lifx

_If you already know the mac address of your button skip directly to the installation part._

## Detect your Amazon Dash boutton mac addresses (you can also try via your router web interface)
Make sure that you have configured your button with the amazon application but not yet selected any product so it can detect the button and you don't end up buying anything

Also they'll tends to spam your phone if you haven't linked any product, so make sure to disable some notification on their app ;)

#### On linux/unix, install the tcpdump package and use the following command right before pressing your dash button : 
`tcpdump -lve | grep "Request who-has"`

you may want to press the dash button again after few seconds if it didn't work but the mac address on th left is the mac address of your dash button


#### On windows :
not tested but you may try to install tcpdump and apply as filter, *arp*.

Then press your dash button and see what mac address comes often _(the first mac address of the lines)_


### Installation :
Make sure to edit the file *buttons.h* first to insert your amazon dash mac address

`make`

### Examples of use :
`./dashbutton`

`screen -md dashbutton`

_(for now it just run and listen for the network traffic you can ctrl-c to quit but it does require to be run in background manually, for example I personally use [the screen package](https://linuxize.com/post/how-to-use-linux-screen/) that is easy to use.)_


### Dependence :
It requires the *libpcap developer library* : (otherwise you may get this error : pcap.h: No such file or directory)


For ubuntu/debian (remove sudo if you don't have it) :

`sudo apt-get install libpcap-dev`


For redhat based distros :

`yum install libpcap-devel`


####  Sniffer part from tcpdump page https://www.tcpdump.org/pcap.html
#### And everything else except the main and some modifications from https://github.com/ArquintL/lifx-c-lib
