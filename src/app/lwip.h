
#ifndef _APP_LWIP_H_
#define _APP_LWIP_H_


#define NO_SYS         1

#define LWIP_SOCKET         (0)
#define LWIP_NETCONN        (0)
#define LWIP_ICMP  	        (1)

#define MEM_ALIGNMENT       (4)
#define MEM_SIZE            (24 * 1024)

#define TCP_MSS             (640)
#define TCP_SND_BUFF        (TCP_MSS)
#define TCP_WND             (4*TCP_MSS)
#define TCP_SND_QUEUELEN    (16)

#define ETHARP_DEBUG        LWIP_DBG_ON
#define ICMP_DEBUG          LWIP_DBG_ON
     
#define MAC_ADDR0   0
#define MAC_ADDR1   0
#define MAC_ADDR2   0
#define MAC_ADDR3   0
#define MAC_ADDR4   0
#define MAC_ADDR5   1



void lwip_initialize(void);
    
void ETH_IRQHandler(void);

void lwip_task(void);



#endif // _APP_LWIP_H_

