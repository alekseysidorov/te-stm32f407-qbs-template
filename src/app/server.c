#include "server.h"
#include <lwip/err.h>
#include <lwip/tcp.h>


struct tcp_pcb *server = NULL;
struct tcp_pcb *output = NULL;


static void server_error(void *arg, err_t err)
{
}



static err_t server_receive(void *arg, struct tcp_pcb *pcb, struct pbuf *p, err_t err)
{
    if (err == ERR_OK && p != NULL)
    {
        tcp_recved(pcb, p->tot_len);

        ///send echo
        tcp_write(output, p->payload, p->len, 1);
    }
    pbuf_free(p);
    
    if (err == ERR_OK && p == NULL)
    {
        tcp_arg(pcb, NULL);
        tcp_sent(pcb, NULL);
        tcp_recv(pcb, NULL);
        tcp_close(pcb);
    }

    return ERR_OK;
}


static err_t server_accept(void *arg, struct tcp_pcb *pcb, err_t err)
{
    tcp_err(pcb, server_error);
    tcp_recv(pcb, server_receive);
    tcp_poll(pcb, NULL, 4 );

    output = pcb;
        
    return ERR_OK;
}



void server_initialize(void)
{    
    server = tcp_new();

    if (server == NULL)
        return;
    
    if (tcp_bind(server, IP_ADDR_ANY, 7000) != ERR_OK)
    {
        return;
    }
    
    server = tcp_listen(server);
    tcp_accept(server, server_accept);
}


