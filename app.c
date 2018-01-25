/*
 **  LIFX C Library
 **  Copyright 2016 Linard Arquint
 */


#define BUTTON1 "b4:7c:9c:e3:f2:62"

#include <stdio.h>
#include <unistd.h>

#include "lifx.h"
#include "bulb.h"
#include "color.h"
#include <pcap.h>
#include <stdio.h>
#include <stdint.h>
#include <netinet/ether.h>

typedef struct __attribute__((__packed__)) EtherHeader {
	const struct ether_addr destAddr;
	const struct ether_addr sourceAddr;
} EtherHeader;

static void toggleBulbs(bulb_service_t **bulbs)
{
	int i;
	bool state;
	int	allon;

	i = 0;
	allon = 1;
	while (bulbs[i] != NULL)
	{
		getPower(bulbs[i++], &state);
		if (!state)
			allon = 0;
	}
	i = 0;
	while (bulbs[i] != NULL)
		setPower(bulbs[i++], ((allon == 0) ? 0 : 1), 0);

}

void	sign(void)
{
	int res;

	res = init_lifx_lib();
	bulb_service_t **bulbs;
	res = discoverBulbs(&bulbs);
	//printBulbs(bulbs);
	toggleBulbs(bulbs);
	close_lifx_lib();

}


static void printBulb(bulb_service_t *bulb) {
	printf("bulb\n");
	printf("    target: %llu\n", bulb->target);
	printf("    service: %d\n", bulb->service);
	printf("    port: %d\n", bulb->port);
	printf("----\n");
}

static void printBulbs(bulb_service_t **bulbs) {
	int bulb_counter = 0;
	while (bulbs[bulb_counter] != NULL) {
		printBulb(bulbs[bulb_counter]);
		bulb_counter++;
	}
}

static int printCurrentPowerLevel(bulb_service_t *bulb) {
	bool on;
	int res;
	if ((res = getPower(bulb, &on))) {
		printf("getPower error: %d\n", res);
		return -1;
	}
	printf("bulb is turned %s\n", on ? "on" : "off");
	return 0;
}

static int testPower(bulb_service_t *bulb) {
	int res;
	if ((res = setPower(bulb, true, 500))) {
		printf("setPower error: %d\n", res);
		return -1;
	}
	sleep(2);
	if (printCurrentPowerLevel(bulb)) {
		return -1;
	}
	if ((res = setPower(bulb, false, 500))) {
		printf("setPower error: %d\n", res);
		return -1;
	}
	sleep(1);
	if (printCurrentPowerLevel(bulb)) {
		return -1;
	}
	return 0;
}

static int testColor(bulb_service_t *bulb) {
	// get color to set the same color afterwards
	bool on;
	color_t orig_color;
	char label[33];
	int res;
	if ((res = getColor(bulb, &on, &orig_color, label))) {
		printf("getColor error: %d\n", res);
		return -1;
	}
	printf("bulb state\n");
	printf("    name: %s\n", label);
	printf("    on: %s\n", on ? "yes" : "no");
	printf("    hue: %d\n", orig_color.hue);
	printf("    saturation: %d\n", orig_color.saturation);
	printf("    brightness: %d\n", orig_color.brightness);
	printf("    kelvin: %d\n", orig_color.kelvin);
	printf("----------\n");

	sleep(2);

	// test: blue color (hue: 240°, saturation: 100%, brightness: 100%)
	color_t blue = {
		.hue = (uint16_t)((float)240 / 360 * 65535),
		.saturation = 65535,
		.brightness = 65535,
		.kelvin = 9000,
	};
	color_t white = {
		.hue = 0,
		.saturation = 0,
		.brightness = 0xFFFF,
		.kelvin = 3500,
	};
	color_t green = {
		.hue = 0x5555,
		.saturation = 0xFFFF,
		.brightness = 0xFFFF,
		.kelvin = 0x0DAC,
	};

	if ((res = setColor(bulb, blue, 1000))) {
		printf("setColor (blue) error: %d\n", res);
		return -1;
	}

	sleep (3); 

	if ((res = setColor(bulb, green, 0))) {
		printf("setColor (green) error: %d\n", res);
		return -1;
	}

	sleep (2); 

	// revert color:
	if ((res = setColor(bulb, white, 500))) { // duration: 2 sec
		printf("setColor (white) error: %d\n", res);
		return -1;
	}

	sleep (2); // 3 sec

	return 0;
}	

int main(void) {
	pcap_t *handle;         /* Session handle */
	char *dev;          /* The device to sniff on */
	char errbuf[PCAP_ERRBUF_SIZE];  /* Error string */
	struct bpf_program fp;      /* The compiled filter */
	char filter_exp[] = "port bootps";  /* The filter expression */
	bpf_u_int32 mask;       /* Our netmask */
	bpf_u_int32 net;        /* Our IP */
	struct pcap_pkthdr header;  /* The header that pcap gives us */
	const u_char *packet;       /* The actual packet */
	const struct EtherHeader *eth;

	/* Define the device */
	dev = pcap_lookupdev(errbuf);
	if (dev == NULL)
		return(2);
	/* Find the properties for the device */
	if (pcap_lookupnet(dev, &net, &mask, errbuf) == -1) {
		net = 0;
		mask = 0;
	}
	/* Open the session in promiscuous mode */
	handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
	if (handle == NULL)
		return(2);
	/* Compile and apply the filter */
	if (pcap_compile(handle, &fp, filter_exp, 0, net) == -1)
		return(2);
	if (pcap_setfilter(handle, &fp) == -1)
		return(2);
	/* Grab a packet */
	while (1)
	{
		packet = pcap_next(handle, &header);
		if (packet)
		{
			eth = (EtherHeader *)packet;
			if (strcmp(BUTTON1, ether_ntoa(&eth->sourceAddr)) == 0)
				sign();
			//printf("%s\n", ether_ntoa(&eth->sourceAddr));
		}
	}
	/* And close the session */
	pcap_close(handle);
	return(0);
}
