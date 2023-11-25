export declare const native: HMN.Native;
export declare module HMN {
    interface Native {
        isAdmin: () => boolean;
        ipv4: () => string;
        adapterIP: () => string;
        getNetParams: () => string;
        getConnectNetList: (tcp?: boolean, udp?: boolean, tcp6?: boolean, udp6?: boolean) => string;
        sleep: (awaitTime: number) => void;
        getTCPv6PortProcessID: (port: number) => string;
        getUDPv6PortProcessID: (port: number) => string;
        getTCPv4PortProcessID: (port: number) => number | null;
        getUDPv4PortProcessID: (port: number) => number | null;
        killProcess: (ProcessID: number) => boolean;
        getProcessidFilePath: (ProcessID: number) => string | null;
        getHostsPath(): string;
        getSystemProxyServer(): string | null;
        getSystemProxyPac(): string | null;
        getDomainIPaddress(domain: string): string;
    }
    interface ipv4Item {
        broadcast: string;
        netmask: string;
        ipaddress: string;
    }
    enum network_type {
        AF_UNSPEC = 0,
        AF_UNIX = 1,
        AF_INET = 2,
        AF_IMPLINK = 3,
        AF_PUP = 4,
        AF_CHAOS = 5,
        AF_NS = 6,
        AF_IPX = 6,
        AF_ISO = 7,
        AF_OSI = 7,
        AF_ECMA = 8,
        AF_DATAKIT = 9,
        AF_CCITT = 10,
        AF_SNA = 11,
        AF_DECnet = 12,
        AF_DLI = 13,
        AF_LAT = 14,
        AF_HYLINK = 15,
        AF_APPLETALK = 16,
        AF_NETBIOS = 17,
        AF_VOICEVIEW = 18,
        AF_FIREFOX = 19,
        AF_UNKNOWN1 = 20,
        AF_BAN = 21,
        AF_ATM = 22,
        AF_INET6 = 23,
        AF_CLUSTER = 24,
        AF_12844 = 25,
        AF_IRDA = 26,
        AF_NETDES = 28
    }
    interface hmc_addr_item {
        ipaddress: string;
        typeName: "IPv4" | "IPv6";
        type: network_type;
    }
    interface hmc_net_addr_item {
        name: string;
        addr_item: hmc_addr_item;
    }
    interface ConnectNet {
        typeName: "UDP" | "TCP" | "TCP6" | "UDP6";
        type: network_type;
        ipAddr: number;
        ip: string;
        port: number;
        pid: number;
        remotePort: number;
        remoteIPAddr: number;
        remoteIP: string;
        state: "CLOSED" | "LISTEN" | "SYN-SENT" | "SYN-RECEIVED" | "ESTABLISHED" | "FIN-WAIT-1" | "FIN-WAIT-2" | "CLOSE-WAIT" | "CLOSING" | "LAST-ACK" | "TIME-WAIT" | "DELETE-TCB" | "UNKNOWN";
    }
    interface hmc_NetParams {
        hostName: string;
        domainName: string;
        dnsServers: string;
        /**
         * @brief 节点类型
         * - BROADCAST_NODETYPE;
         * - HYBRID_NODETYPE
         * - MIXED_NODETYPE
         * - PEER_TO_PEER_NODETYPE
         * - UNKNOWN:<UINT>
         */
        nodeType: `UNKNOWN:<${number}>` | "BROADCAST_NODETYPE" | "HYBRID_NODETYPE" | "MIXED_NODETYPE" | "PEER_TO_PEER_NODETYPE";
        dhcpScopeName: string;
        enableRouting: boolean;
        enableArpProxy: boolean;
        enableDns: boolean;
    }
}
export declare const ref: {
    /**
    * 将内容格式化为文本路径
    * @param Str
    * @returns
    */
    path(Str: any): string;
    /**
     * 格式化为bool
     * @param bool
     * @returns
     */
    bool(bool: any): boolean;
    /**
     * 将内容格式化为文本
     * @param Str
     * @returns
     */
    string(Str: any): string;
    /**
     * 格式化数字为int(强制)
     * @param Num
     * @returns
     */
    int(Num: any): number;
    /**
     * 文本数组
     * @param array
     * @returns
     */
    stringArray(array: Set<any> | Array<any>): string[];
    /**
     * 文本数组
     * @param array
     * @returns
     */
    intArray(array: Set<any> | Array<any>): number[];
    /**
     * 拼合buff片段
     * @param buffList
     * @returns
     */
    concatBuff(buffList: Buffer[]): Buffer;
};
/**
 * 判断当前进程是否有管理员权限
 * @returns
 */
export declare function isAdmin(): boolean;
/**
 * 枚举本机局域网中的ipv4地址
 * @returns
 */
export declare function ipv4(): Array<HMN.ipv4Item>;
/**
 * 获取本机局域网的所以ip (并区分适配器,v4,v6)
 * @returns
 */
export declare function ip(): Array<HMN.hmc_net_addr_item>;
/**
 * 获取本机局域网的所以ip (并区分适配器,v4,v6)
 * @returns
 */
export declare function adapterIP(): Array<HMN.hmc_net_addr_item>;
/**
 *  枚举此电脑中的 端口 ipv4 and ipv6 的 TCP，UDP 端口信息
 * @param tcp 是否遍历 tcp ipv4端口
 * @default true
 * @param udp  是否遍历 udp ipv4端口
 * @default true
 * @param tcp6  是否遍历 tcp ipv6端口
 * @default true
 * @param udp6  是否遍历 udp ipv6端口
 * @default true
 * @returns
 */
export declare function getConnectNetList(tcp?: boolean, udp?: boolean, tcp6?: boolean, udp6?: boolean): Array<HMN.ConnectNet>;
/**
 * `Sync` 同步阻塞(进程)
 * @param awaitTime
 * @returns
 */
export declare function sleep(awaitTime: number): void;
/**
 * `async` 异步阻塞(进程)
 * @param awaitTime
 * @returns
 */
export declare function Sleep(awaitTime: number, Sync?: boolean): Promise<unknown>;
/**
 * 获取一个tcp空闲端口 (服务)
 * @returns
 */
export declare function freePort(): Promise<number>;
/**
 * 获取一个tcp空闲端口 (服务)
 * @returns
 */
export declare function freePortTCP(): Promise<number>;
/**
 * 获取一个UDP空闲端口
 * @returns
 */
export declare function freePortUDP(): Promise<number>;
/**
 * 判断TCP(服务)端口号正在使用/系统占用
 * @param port TCP端口
 * @returns
 */
export declare function hasPortTCP(port: number): Promise<boolean>;
export declare function hasPortTCP(port: number, callBack: (hasPort: boolean) => unknown): void;
/**
 * 判断UDP端口号正在使用/系统占用
 * @param port TCP端口
 * @returns
 */
export declare function hasPortUDP(port: number): Promise<boolean>;
export declare function hasPortUDP(port: number, callBack: (hasPort: boolean) => unknown): void;
/**
 * 获取进程可执行文件位置
 * @param ProcessName 进程名
 * @returns 进程id
 */
export declare function getProcessidFilePath(ProcessID: number): string | null;
/**
 * 结束该进程
 * @param ProcessID
 * @returns
 */
export declare function killProcess(ProcessID: number): boolean;
/**
 * 获取此端口被哪个进程占用了
 * @param port
 * @returns
 */
export declare function getTCPv4PortProcessID(port: number): number | null;
/**
 * 获取此端口被哪个进程占用了
 * @param port
 * @returns
 */
export declare function getUDPv4PortProcessID(port: number): number | null;
/**
 * 获取此端口被哪个进程占用了
 * @param port
 * @returns
 */
export declare function getUDPv6PortProcessID(port: number): string;
/**
 * 获取此端口被哪个进程占用了
 * @param port
 * @returns
 */
export declare function getTCPv6PortProcessID(port: number): string;
/**
 * 获取hosts文件的路径
 * @returns
 */
export declare function getHostsPath(): string;
/**
 * 从默认dns(联网)解析域名主机ip
 * - √ goole.com
 * - √ api.goole.com
 * - × api.goole.com/services
 * - × https://goole.com
 * @param url
 * @returns ip列表
 */
export declare function getDomainIPaddress(url: string): Array<string>;
/**
 * 获取系统代理pac脚本链接
 * @returns
 */
export declare function getSystemProxyPac(): string | null;
/**
 *  获取系统代理链接（仅在启用系统代理时）
 * @returns
 */
export declare function getSystemProxyServer(): string | null;
/**
 * 获取主机网络信息
 * @returns
 */
export declare function getNetParams(): HMN.hmc_NetParams | null;
export declare function public_ip(): Promise<string>;
