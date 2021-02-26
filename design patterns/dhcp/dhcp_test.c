#include "stdio.h"/*printf */

#include "test_tools.h"
#include "dhcp.h"

void Test();

int main()
{
    Test();
    return 0;
}

void Test()
{
    dhcp_t *dhcp = DHCPCreate("9",0);
    char alocd = '0';
    char req = '7';
    printf(YELLOW"\n\n%lu"WHITE, DHCPCountFree(dhcp));
    
    DHCPAllocate(dhcp, &req, &alocd );
    printf(GREEN"\n\n%lu"WHITE, DHCPCountFree(dhcp));
    DHCPAllocate(dhcp, &req, &alocd );

    DHCPDestroy(dhcp);
}