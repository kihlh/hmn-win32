
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif

#include <stdio.h>
#include <winsock2.h>
#include <iphlpapi.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "iphlpapi.lib")

void print_addr(MIB_IPADDRROW addr)
{
	char addr_str[BUFSIZ];
	char mask_str[BUFSIZ];

	DWORD broadcast;
	char broadcast_str[BUFSIZ];

	broadcast = (addr.dwAddr & addr.dwMask) 
		| (addr.dwMask ^ (DWORD)0xffffffff);

	inet_ntop(AF_INET, (void *)&addr.dwAddr, addr_str, BUFSIZ);
	inet_ntop(AF_INET, (void *)&addr.dwMask, mask_str, BUFSIZ);
	inet_ntop(AF_INET, (void *)&broadcast, broadcast_str, BUFSIZ);

	printf("ipaddress=%s, netmask=%s, broadcast=%s\n", 
		addr_str,
		mask_str,
		broadcast_str
		);	
}

bool print_ipaddress()
{
	DWORD rv, size;
	PMIB_IPADDRTABLE ipaddrtable;

	rv = GetIpAddrTable(NULL, &size, 0);
	if (rv != ERROR_INSUFFICIENT_BUFFER) {
		fprintf(stderr, "GetIpAddrTable() failed...");
		return false;
	}
	ipaddrtable = (PMIB_IPADDRTABLE)malloc(size);

	rv = GetIpAddrTable(ipaddrtable, &size, 0);
	if (rv != NO_ERROR) {
		fprintf(stderr, "GetIpAddrTable() failed...");
		free(ipaddrtable);
		return false;
	}

	for (DWORD i = 0; i < ipaddrtable->dwNumEntries; ++i) {
		print_addr(ipaddrtable->table[i]);
	}

	free(ipaddrtable);

	return true;
}

int main(int argc, char *argv[])
{
	WSAData d;
	if (WSAStartup(MAKEWORD(2, 2), &d) != 0) {
		return -1;
	}

	print_ipaddress();

	WSACleanup();

	return 0;
}
