#include "./sock.hpp"

string formatIP(DWORD dwLocalAddr)
{
    size_t a = dwLocalAddr >> 24 & 0xFF;
    size_t b = dwLocalAddr >> 16 & 0xFF;
    size_t c = dwLocalAddr >> 8 & 0xFF;
    size_t d = dwLocalAddr & 0xFF;

    return string(to_string((long)d) + "." + to_string((long)c) + "." + to_string((long)b) + "." + to_string((long)a));
}

string formatIP(IN6_ADDR dwLocalAddr)
{
    char ipv6String[INET6_ADDRSTRLEN];
    if (RtlIpv6AddressToStringA(reinterpret_cast<IN6_ADDR *>(&dwLocalAddr), ipv6String) == NULL)
    {
        return "";
    }
    return string(ipv6String);
}

string formatIP(UCHAR ucLocalAddr[16])
{
    char ipv6String[INET6_ADDRSTRLEN];
    if (RtlIpv6AddressToStringA(reinterpret_cast<IN6_ADDR *>(ucLocalAddr), ipv6String) == NULL)
    {
        return "";
    }
    return string(ipv6String);
}

hmc_v4_addr_item get_v4_addr(MIB_IPADDRROW addr)
{
    char addr_str[BUFSIZ];
    char mask_str[BUFSIZ];

    DWORD broadcast;
    char broadcast_str[BUFSIZ];

    broadcast = (addr.dwAddr & addr.dwMask) | (addr.dwMask ^ (DWORD)0xffffffff);

    inet_ntop(AF_INET, (void *)&addr.dwAddr, addr_str, BUFSIZ);
    inet_ntop(AF_INET, (void *)&addr.dwMask, mask_str, BUFSIZ);
    inet_ntop(AF_INET, (void *)&broadcast, broadcast_str, BUFSIZ);

    hmc_v4_addr_item result;
    result.broadcast = string(broadcast_str);
    result.ipaddress = string(addr_str);
    result.netmask = string(mask_str);

    return result;
}

bool get_v4_ipaddress_list(vector<hmc_v4_addr_item> &addrList)
{
    WSAData d;
    if (WSAStartup(MAKEWORD(2, 2), &d) != 0)
    {
        return false;
    }

    DWORD rv, size;
    PMIB_IPADDRTABLE ipaddrtable;

    rv = GetIpAddrTable(NULL, &size, 0);
    if (rv != ERROR_INSUFFICIENT_BUFFER)
    {
        // fprintf(stderr, "GetIpAddrTable() failed...");
        return false;
    }
    ipaddrtable = (PMIB_IPADDRTABLE)malloc(size);

    rv = GetIpAddrTable(ipaddrtable, &size, 0);
    if (rv != NO_ERROR)
    {
        // fprintf(stderr, "GetIpAddrTable() failed...");
        free(ipaddrtable);
        return false;
    }

    for (DWORD i = 0; i < ipaddrtable->dwNumEntries; ++i)
    {
        addrList.push_back(
            get_v4_addr(ipaddrtable->table[i]));
    }

    free(ipaddrtable);

    WSACleanup();
    return true;
}



