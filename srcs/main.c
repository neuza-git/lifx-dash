/*
 **  LIFX C Library
 **  Copyright 2016 Linard Arquint
 */

#include "../includes/lifx.h"

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

void	toggle(void)
{
	int res;

	res = init_lifx_lib();
	bulb_service_t **bulbs;
	res = discoverBulbs(&bulbs);
	//printBulbs(bulbs);
	toggleBulbs(bulbs);
	close_lifx_lib();

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

	int	i;
	char	**bts;

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
	bts = NULL;
	if (BUTTONS)
		bts = ft_strsplit(BUTTONS, ',');
	while (bts)
	{
		packet = pcap_next(handle, &header);
		if (packet)
		{
			i = 0;
			while (bts[i]) {
				eth = (EtherHeader *)packet;
				//printf("%d\n", strcmp(bts[i], ether_ntoa(&eth->sourceAddr)));
				//printf("%s-%s\n", bts[i], ether_ntoa(&eth->sourceAddr));
				if (strcmp(bts[i], ether_ntoa(&eth->sourceAddr)) == 0)
					toggle();
				i++;
			}
			//printf("%s\n", ether_ntoa(&eth->sourceAddr));
		}
	}
	i = 0;
	while (bts && bts[i])
		free(bts[i++]);
	free(bts);
	/* And close the session */
	pcap_close(handle);
	return(0);
}
