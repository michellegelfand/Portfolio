/*
*   @File:      hdcp.h
*   @Created:   13.08.19
*   @Version:   1.0
*
*/   

#include <stddef.h> /* size_t */

#ifndef __DHCP_H__
#define __DHCP_H__


typedef unsigned char ipv4_t[4];

typedef struct dhcp dhcp_t;

/* 
struct dhcp
{
	trie_t *trie;
	ipv4_t ip_mask;
}
 */

/*
*	not available ip adresses:
*	0.0.0.0
*	255.255.255.255
*	255.255.255.254
*/

/************************************************************************/

/*   
*   ip - an array of chars                
*	RETURN: pointer to new DHCP
*	
*/
dhcp_t *DHCPCreate (const ipv4_t ip, size_t prefix_mask);

/*
*	RETURN: none.
*	
*/	
void DHCPDestroy(dhcp_t *dhcp);
/*
*	RETURN: 
*			 0 - on success
*			-1 - otherwise
*
* (if requested IP is not available it will return closest higher available IP)
* (if not specified requested IP it will return min available IP address)
*/
int DHCPAllocate(dhcp_t *dhcp, const ipv4_t requested_ip, ipv4_t allocated_ip);
/*
*	RETURN: none.
*	
*/
void DHCPFree(dhcp_t *dhcp, const ipv4_t ip_to_free);
/*
*	RETURN: number of availabel IP addresses
*	
*/
size_t DHCPCountFree(const dhcp_t *dhcp);


#endif /* __DHCP_H__ */