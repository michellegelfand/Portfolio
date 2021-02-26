/*******************************************************************************
* Project           : Data Structures
*
* Program name      : dhcp.c
*
* Author            : Michelle Gelfand
*
* Date created      : 14.08.19
*
* Date Approved       Author	 	             Reviewer 
* 15/08/2019       	  Michelle Gelfand           Katy C. *														  
*******************************************************************************/

#include <assert.h> /* assert */
#include <string.h> /* memset */
#include <stdlib.h> /* malloc, free */
#include <math.h>/*pow*/

#include "bit_array.h"
#include "trie.h"
#include "dhcp.h" 

#define FREE(str) memset(str, 0, sizeof(*str)); free(str);
#define IP_SIZE 32

static bit_array_t IpToBitArray(ipv4_t ip, size_t ip_mask);
static bit_array_t BuildAllocatedIp(bit_array_t allocated_ip,
                                    bit_array_t host_ip,
                                    size_t mask);
struct dhcp
{
	trie_t *trie;
	size_t ip_mask;
    bit_array_t network_ip;
};


dhcp_t *DHCPCreate (const ipv4_t ip, size_t prefix_mask)
{
    ipv4_t orig_ip =  {0};
    dhcp_t *new_dhcp = NULL; 
    bit_array_t recieved_address = 0;
    int status;

    assert(ip);

    new_dhcp = (dhcp_t*)calloc(1, sizeof(dhcp_t));

    if(!new_dhcp)
    {
        return NULL;
    }
    
    new_dhcp->trie = TrieCreate(IP_SIZE - prefix_mask);

    if(!(new_dhcp->trie))
    {
        DHCPDestroy(new_dhcp);
        return NULL;
    }

    new_dhcp->ip_mask = prefix_mask;

    orig_ip[0] = ip[0];
    orig_ip[1] = ip[1];
    orig_ip[2] = ip[2];
    orig_ip[3] = ip[3];

    new_dhcp->network_ip   =  IpToBitArray(orig_ip, prefix_mask);
    new_dhcp->network_ip >>= (IP_SIZE - prefix_mask);
    new_dhcp->network_ip <<= (IP_SIZE -prefix_mask);

    TrieInsert(new_dhcp->trie, 0lu, &recieved_address, &status);
    TrieInsert(new_dhcp->trie, 254, &recieved_address, &status);
    TrieInsert(new_dhcp->trie, 255 , &recieved_address, &status);

    return new_dhcp;
}


static bit_array_t IpToBitArray(ipv4_t ip, size_t ip_mask)
{
    bit_array_t result = 0;
    size_t i = 1;

    if( NULL == ip)
    {
        return (size_t)0;
    }


    for (i = 0;  i < 4;  ++i)
    {
        result <<= 8;
        memcpy(&result, (char*)ip+i, 1);
    }

    (void)ip_mask;
    return result;
}


static bit_array_t BuildAllocatedIp(bit_array_t allocated_ip,
                             bit_array_t host_ip,
                             size_t mask)
{
    allocated_ip |= host_ip;

    (void)mask;
    return allocated_ip; 
}


size_t DHCPCountFree(const dhcp_t *dhcp)
{
    assert(dhcp);
    
    return ( pow(2, IP_SIZE - dhcp->ip_mask) - (TrieCount(((dhcp_t*)dhcp)->trie)));
}


void DHCPDestroy(dhcp_t *dhcp)
{
    TrieDestroy(dhcp->trie);
    FREE(dhcp);
}


void DHCPFree(dhcp_t *dhcp, const ipv4_t ip_to_free)
{
	size_t reserved_host[3] = {0};
    bit_array_t path_to_free = IpToBitArray((unsigned char*)ip_to_free, dhcp->ip_mask);
    size_t host_to_free = path_to_free & 255;

	reserved_host[0] = 0;
	reserved_host[1] = pow(2, (IP_SIZE - dhcp->ip_mask)) - 1;   /* 111...11 */
	reserved_host[2] = reserved_host[1] - 1;                    /* 111...10 */

    if( (host_to_free != reserved_host[0]) &&
		(host_to_free != reserved_host[1]) &&
		(host_to_free != reserved_host[2]) )
	{
        TrieRemove(dhcp->trie, path_to_free);
    }
}


int DHCPAllocate(dhcp_t *dhcp, const ipv4_t requested_ip, ipv4_t allocated_ip)
{
    bit_array_t path_to_alloc = 0;
    size_t host = 0;
    int result =0;
    int i = 0;

    if( 0 == DHCPCountFree(dhcp))
    {
        return 1;
    }

    if(!requested_ip)
    {
        requested_ip = 0;
    }
    
    path_to_alloc = IpToBitArray((unsigned char*)requested_ip, dhcp->ip_mask);

    TrieInsert(dhcp->trie, path_to_alloc, &host, &result);

    host = BuildAllocatedIp(dhcp->network_ip, host, dhcp->ip_mask);

    for (i = 4;  i > 0;  -- i)
    {
        memcpy(&allocated_ip[i-1], &host, 1);
        host >>= 8;
    }

    return result;
}
