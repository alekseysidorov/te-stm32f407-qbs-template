#include "lwip.h"
#include <lwip/tcp.h>
#include <lwip/ip_frag.h>
#include <lwip/netif.h>
#include <lwip/memp.h>
#include <netif/etharp.h>
#include <netif/ethernetif.h>
#include "stm32f4x7_eth.h"
#include "stm32f2x7_eth_bsp.h"
#include "tcp_impl.h"
#include <system/generic.h>


#define TCP_TIMER_INTERVAL      (TCP_TMR_INTERVAL * 1000)
#define ARP_TIMER_INTERVAL      (ARP_TMR_INTERVAL * 1000)
#define IP_TIMER_INTERVAL       (IP_TMR_INTERVAL  * 1000)



struct netif netif_stm32;

static uint lastTcpTime = 0;
static uint lastArpTime = 0;
static uint lastIpReassTime = 0;



void lwip_task(void)
{
    while (ETH_CheckFrameReceived() != 0)
        ethernetif_input(&netif_stm32);
    if (time_expired(&lastTcpTime, TCP_TMR_INTERVAL))
        tcp_tmr();

    if (time_expired(&lastArpTime, ARP_TIMER_INTERVAL))
        etharp_tmr();

    if (time_expired(&lastIpReassTime, IP_TIMER_INTERVAL))
        ip_reass_tmr();
}



void lwip_initialize(void)
{
    struct ip_addr ipaddr;
    struct ip_addr netmask;
    struct ip_addr gw;

    mem_init();
    memp_init();

    IP4_ADDR(&ipaddr, 192, 168, 1, 10);
    IP4_ADDR(&netmask, 255, 255, 255, 0);
    IP4_ADDR(&gw, 192, 168, 1, 1);

    netif_add(&netif_stm32, &ipaddr, &netmask, &gw, NULL, &ethernetif_init, &ethernet_input);
    netif_set_default(&netif_stm32);
    netif_set_up(&netif_stm32);
}



void ETH_IRQHandler(void)
{
    ETH_DMAClearITPendingBit(ETH_DMA_IT_R | ETH_DMA_IT_NIS);
}


