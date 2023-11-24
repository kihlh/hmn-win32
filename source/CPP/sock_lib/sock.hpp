
// 防止重复导入
#ifndef MODE_INTERNAL_INCLUDE_SOCK_LIB_SOCK_HPP
#define MODE_INTERNAL_INCLUDE_SOCK_LIB_SOCK_HPP

// WINSOCKAPI 会和winsock2.h 冲突 难以避免 索性提前禁用 WINSOCKAPI
// !  windows.h 会默认把<winsock.h> 放进来 如果在之前引用了需要把这句放进前面 但是 winsock.h 会和 winsock2.h 冲突导致无法使用ipv6
#define _WINSOCKAPI_

#include <iostream>
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <string>
#include <windows.h>
#include <vector>
#include <set>

#include <winsock2.h>
#include <ws2ipdef.h>
#include <ws2tcpip.h>
#include <ip2string.h>
#include <iphlpapi.h>

// #include <winsock2.h>
// #include <ws2ipdef.h>
// #include <iphlpapi.h>
// #include <ip2string.h>
// #include <ws2tcpip.h >

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "Ntdll.lib")

using namespace std;

#define __HMC_CHECK_CATCH catch (char *err){};
#define __HMC_THREAD (code) std::thread([]() -> void { code }).detach();
#define __HMC_VirtualAlloc(Type, leng) (Type) VirtualAlloc((LPVOID)NULL, (DWORD)(leng), MEM_COMMIT, PAGE_READWRITE);
#define __HMC_VirtualFree(Virtua) \
    if (Virtua != NULL)           \
        VirtualFree(Virtua, 0, MEM_RELEASE);

#define MALLOC(variable) HeapAlloc(GetProcessHeap(), 0, (variable))
#define FREE(variable) HeapFree(GetProcessHeap(), 0, (variable))



//?ip.hpp ------------------------------------------------------------------------------------------------

string formatIP(UCHAR ucLocalAddr[16]);
string formatIP(IN6_ADDR dwLocalAddr);
string formatIP(DWORD dwLocalAddr);

// 主机信息
struct hmc_v4_addr_item
{
    // 广播
    string broadcast;
    // 掩码
    string netmask;
    // ip
    string ipaddress;

    string to_josn()
    {

        string result = string("{");
        result.append("\"ipaddress\":\"").append(ipaddress.c_str()).append("\",");
        result.append("\"netmask\":\"").append(netmask.c_str()).append("\",");
        result.append("\"broadcast\":\"").append(broadcast.c_str()).append("\"");
        result.append("}");
        return result;
    }
};

struct hmc_addr_item
{
    // ip
    string ipaddress;
    // ip类型名称  ipv4 or ipv6
    string typeName;
    // ip类型 2(AF_INET) 23(AF_INET6)
    DWORD type = 0;

    string to_josn()
    {
        string result = string("{");
        result.append("\"ipaddress\":\"").append(ipaddress.c_str()).append("\",");
        result.append("\"typeName\":\"").append(typeName.c_str()).append("\",");
        result.append("\"type\":").append(to_string(type));
        result.append("}");
        return result;
    }

};

struct hmc_net_addr_item
{
    // 网络适配器名称
    string name;
    // ip 列表
    vector<hmc_addr_item> addr_item;
};

bool get_v4_ipaddress_list(vector<hmc_v4_addr_item> &addrList);

//?ip.hpp ------------------------------------------------------------------------------------------------

//?connect_net.hpp ------------------------------------------------------------------------------------------------

// https://en.wikipedia.org/wiki/Transmission_Control_Protocol
// https://learn.microsoft.com/zh-cn/windows/win32/api/iphlpapi/nf-iphlpapi-gettcp6table
struct ConnectNet
{
    string typeName; // "UDP" / "TCP" / "TCP6" / "UDP6"
    DWORD type = 0;  // 6 tcp / tcp6   17 udp / udp6
    DWORD ipAddr;    // dwLocalAddr
    string ip;       // 解析出来的实际ip
    DWORD port;      // 占用的端口
    DWORD pid;       // 占用此端口的进程
    // 以下参数仅支持TCP
    DWORD remotePort;   // 远程的端口
    DWORD remoteIPAddr; // 远程的ip (LocalAddr)
    string remoteIP;    // 解析出来的实际远程ip
    string state;       // 状态码 "CLOSED"|"LISTEN"|"SYN-SENT"|"SYN-RECEIVED"|"ESTABLISHED"|"FIN-WAIT-1"|"FIN-WAIT-2"|"CLOSE-WAIT"|"CLOSING"|"LAST-ACK"|"TIME-WAIT"|"DELETE-TCB"|"UNKNOWN"
    string to_josn()
    {

        string result = string("{");
        result.append("\"typeName\":\"").append(typeName.c_str()).append("\",");
        result.append("\"type\":").append(to_string(type)).append(",");
        // __PUSH_JSON_VALUE_STRING_NEXT(result , "ip" , ip);

        // result.append("\"broadcast\":\"".).append(broadcast.c_str()).append("\"");
        result.append("}");
        return result;
    }
};

// 主机信息
struct hmc_NetParams
{
    string hostName;           // 主机名称
    string domainName;         // 域名名称
    vector<string> dnsServers; // dns服务器列表
    /**
     * @brief 节点类型
     * - BROADCAST_NODETYPE;
     * - HYBRID_NODETYPE
     * - MIXED_NODETYPE
     * - PEER_TO_PEER_NODETYPE
     * - UNKNOWN:<UINT>
     */
    string nodeType;
    string dhcpScopeName; // dhcp 范围名称
    bool enableRouting;   // 是否启用路由选择
    bool enableArpProxy;  // 是否ARP代理
    bool enableDns;       // 是否启用dns
    
};

hmc_NetParams getNetParams();
BOOL hmc_EnableShutDownPriv();
DWORD GetTCPPortProcessID(unsigned short port);
vector<DWORD> GetTCP6PortProcessID(unsigned short port);
string GetStateName(DWORD dwState);
void enumConnectNet(vector<ConnectNet> &ConnectNetList, bool tcp, bool udp, bool tcp6, bool udp6);

//?connect_net.hpp ------------------------------------------------------------------------------------------------

#endif // MODE_INTERNAL_INCLUDE_SOCK_LIB_SOCK_HPP