import path = require("path");
import os = require("os");
import fs = require("fs");
import https = require('https');
import http = require('http');
import dgram = require('dgram');
import net = require("net");


/**
 * @zh-cn 静态调用 hmn.dll (注意如果您不知道这个是什么作用 请勿随意调用 参数错误有可能会导致进程崩溃)
 * @en-us Static call to hmn.dll (Note that if you don't know what this does, don't call it at random.  Parameter errors may cause the process to crash)
 */
const get_native: () => HMN.Native = (binPath?: string) => {
    function _require_bin(): HMN.Native | null {
        try {
            if (binPath) return require(binPath);
            if (process.arch.match(/^x32|ia32$/)) return require("./bin/HMN_x86.node");
            if (process.arch.match(/^x64$/)) return require("./bin/HMN_x64.node");
        } catch (X_X) {

        }
        return null;
    }
    let Native: HMN.Native = (process.platform == "win32" ? _require_bin() : null) || (() => {
        let HMCNotPlatform = "HMC::HMC current method only supports win32 platform";
        function fnBool(...args: any[]) { console.error(HMCNotPlatform); return false }
        function fnVoid(...args: any[]) { console.error(HMCNotPlatform); return undefined }
        function fnNull(...args: any[]) { console.error(HMCNotPlatform); return null }
        function fnNum(...args: any[]) { console.error(HMCNotPlatform); return 0 }
        function fnStrList(...args: any[]) { console.error(HMCNotPlatform); return [] as string[] }
        function fnStr(...args: any[]) { console.error(HMCNotPlatform); return '' }
        function fnAnyArr(...args: any[]) { console.error(HMCNotPlatform); return [] as any[] }
        function fnArrayStr(...args: any[]) { console.error(HMCNotPlatform); return '[]' }
        function fnPromise(...args: any[]) { console.error(HMCNotPlatform); return Promise.reject("HMC::HMC current method only supports win32 platform") }
        return {
            isAdmin: fnBool,
            //? 返回json文本
            ipv4: fnArrayStr,
            //? 返回json文本
            adapterIP: fnArrayStr,
            //? 返回json文本
            getNetParams: fnArrayStr,
            //? 返回json文本
            getConnectNetList: fnArrayStr,
            sleep: () => fnVoid,
            //? 返回json文本
            getTCPv6PortProcessID: fnArrayStr,
            //? 返回json文本
            getUDPv6PortProcessID: fnArrayStr,
            getTCPv4PortProcessID: fnNull,
            getUDPv4PortProcessID: fnNull,
            killProcess: fnBool,
            getProcessidFilePath: fnNull,
            getHostsPath: fnArrayStr,
            getSystemProxyServer: fnNull,
            getSystemProxyPac: fnNull,
            //? 返回json文本
            getDomainIPaddress: fnArrayStr,
            getConnectNetListAsync: fnPromise,
            getProcessidFilePathAsync: fnPromise,
            adapterIPAsync: fnPromise,
            getPortProcessIDAsync: fnPromise,
            getDomainIPaddressAsync: fnPromise,
            ipv4Async: fnPromise,
            getNetParamsAsync:fnPromise,
        }
    })();
    return Native;
};
export const native: HMN.Native = get_native();


// 类型
export module HMN {
    export interface Native {
        isAdmin: () => boolean;
        //? 返回json文本
        ipv4: () => string;
        //? 返回json文本
        adapterIP: () => string;
        //? 返回json文本
        getNetParams: () => string;
        //? 返回json文本
        getConnectNetList: (tcp?: boolean, udp?: boolean, tcp6?: boolean, udp6?: boolean) => string;
        sleep: (awaitTime: number) => void;
        //? 返回json文本
        getTCPv6PortProcessID: (port: number) => string;
        //? 返回json文本
        getUDPv6PortProcessID: (port: number) => string;
        getTCPv4PortProcessID: (port: number) => number | null;
        getUDPv4PortProcessID: (port: number) => number | null;
        killProcess: (ProcessID: number) => boolean;
        getProcessidFilePath: (ProcessID: number) => string | null;
        getHostsPath(): string;
        getSystemProxyServer(): string | null;
        getSystemProxyPac(): string | null;
        //? 返回json文本
        getDomainIPaddress(domain: string): string;
        //? 返回json文本
        getConnectNetListAsync: (tcp?: boolean, udp?: boolean, tcp6?: boolean, udp6?: boolean) => Promise<string>;
        getPortProcessIDAsync: (PortType: 0 | 1 | 2 | 3, port: number) => Promise<string>;
        getProcessidFilePathAsync: (pid: number) => Promise<string>;
        adapterIPAsync: () => Promise<string>;
        ipv4Async: () => Promise<string>;
        getDomainIPaddressAsync: (domain: string) => Promise<string>;
        getNetParamsAsync:()=> Promise<string>;
    }

    export interface ipv4Item {
        // 广播
        broadcast: string;
        // 掩码
        netmask: string;
        // ip
        ipaddress: string;
    }

    export enum network_type {
        AF_UNSPEC = 0,              // unspecified
        AF_UNIX = 1,              // local to host (pipes, portals)
        AF_INET = 2,              // internetwork: UDP, TCP, etc.
        AF_IMPLINK = 3,              // arpanet imp addresses
        AF_PUP = 4,              // pup protocols: e.g. BSP
        AF_CHAOS = 5,              // mit CHAOS protocols
        AF_NS = 6,              // XEROX NS protocols
        AF_IPX = 6,          // IPX protocols: IPX, SPX, etc.
        AF_ISO = 7,              // ISO protocols
        AF_OSI = 7,         // OSI is ISO
        AF_ECMA = 8,              // european computer manufacturers
        AF_DATAKIT = 9,              // datakit protocols
        AF_CCITT = 10,             // CCITT protocols, X.25 etc
        AF_SNA = 11,             // IBM SNA
        AF_DECnet = 12,             // DECnet
        AF_DLI = 13,             // Direct data link interface
        AF_LAT = 14,             // LAT
        AF_HYLINK = 15,             // NSC Hyperchannel
        AF_APPLETALK = 16,             // AppleTalk
        AF_NETBIOS = 17,             // NetBios-style addresses
        AF_VOICEVIEW = 18,             // VoiceView
        AF_FIREFOX = 19,             // Protocols from Firefox
        AF_UNKNOWN1 = 20,             // Somebody is using this!
        AF_BAN = 21,             // Banyan
        AF_ATM = 22,             // Native ATM Services
        AF_INET6 = 23,             // Internetwork Version 6
        AF_CLUSTER = 24,             // Microsoft Wolfpack
        AF_12844 = 25,             // IEEE 1284.4 WG AF
        AF_IRDA = 26,             // IrDA
        AF_NETDES = 28,             // Network Designers OSI & gateway
    }

    export interface hmc_addr_item {
        // ip
        ipaddress: string;
        // ip类型名称  ipv4 or ipv6
        typeName: "IPv4" | "IPv6";
        // ip类型 2(AF_INET) 23(AF_INET6)
        type: network_type;
    }

    export interface hmc_net_addr_item {
        // 网络适配器名称
        name: string;
        // ip 列表
        addr_item: hmc_addr_item;
    }

    export interface ConnectNet {
        typeName: "UDP" | "TCP" | "TCP6" | "UDP6";
        // 6 tcp / tcp6   17 udp / udp6
        type: network_type;
        // dwLocalAddr
        ipAddr: number;
        // 解析出来的实际ip
        ip: string;
        // 占用的端口
        port: number;
        // 占用此端口的进程
        pid: number;
        // 远程的端口 (仅TCP)
        remotePort: number;
        // 远程的ip (LocalAddr)  (仅TCP)
        remoteIPAddr: number;
        // 解析出来的实际远程ip  (仅TCP)
        remoteIP: string;
        // 状态码 (仅TCP) "CLOSED"|"LISTEN"|"SYN-SENT"|"SYN-RECEIVED"|"ESTABLISHED"|"FIN-WAIT-1"|"FIN-WAIT-2"|"CLOSE-WAIT"|"CLOSING"|"LAST-ACK"|"TIME-WAIT"|"DELETE-TCB"|"UNKNOWN"
        state: "CLOSED" | "LISTEN" | "SYN-SENT" | "SYN-RECEIVED" | "ESTABLISHED" | "FIN-WAIT-1" | "FIN-WAIT-2" | "CLOSE-WAIT" | "CLOSING" | "LAST-ACK" | "TIME-WAIT" | "DELETE-TCB" | "UNKNOWN";
    }

    export interface hmc_NetParams {
        // 主机名称
        hostName: string;
        // 域名名称
        domainName: string;
        // dns服务器列表
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
        // dhcp 范围名称
        dhcpScopeName: string;
        // 是否启用路由选择
        enableRouting: boolean;
        // 是否ARP代理
        enableArpProxy: boolean;
        // 是否启用dns
        enableDns: boolean;
    }
}

export const ref = {
    /**
    * 将内容格式化为文本路径
    * @param Str
    * @returns
    */
    path(Str: any) {
        return path.resolve(String(Str || "")).replace(/([\0\n\r]+)?$/, '\0');
    },
    /**
     * 格式化为bool
     * @param bool
     * @returns
     */
    bool(bool: any) {
        return bool ? true : false;
    },
    /**
     * 将内容格式化为文本
     * @param Str
     * @returns
     */
    string(Str: any) {
        return String(Str || "");
    },
    /**
     * 格式化数字为int(强制)
     * @param Num
     * @returns
     */
    int(Num: any): number {
        if (!Num) return 0;
        if (typeof Num == "object" && Num instanceof Number) {
            Num = Num?.valueOf();
        }
        // 取整
        Num = Math.trunc(Num + 0);
        if (typeof Num == "number" && !isNaN(Num)) return Num;
        // true == 1
        if (Num && typeof Num == "boolean") Num = 1;
        // false = 0;
        if (!Num && typeof Num == "boolean") Num = 0;
        if (Num >= Infinity) {
            Num = 999999999999999;
        }
        if (Num <= -Infinity) {
            Num = -999999999999999;
        }
        return Num;
    },
    /**
     * 文本数组
     * @param array 
     * @returns 
     */
    stringArray(array: Set<any> | Array<any>) {
        let dataList: string[] = [];
        if (Array.isArray(array)) {
            for (let index = 0; index < array.length; index++) {
                const cout = array[index];
                dataList.push(this.string(cout));
            }
        }
        if (array instanceof Set) {
            for (const cout of array) {
                dataList.push(this.string(cout));
            }
        }
        return dataList;
    },
    /**
     * 文本数组
     * @param array 
     * @returns 
     */
    intArray(array: Set<any> | Array<any>) {
        let dataList: number[] = [];
        if (Array.isArray(array)) {
            for (let index = 0; index < array.length; index++) {
                const cout = array[index];
                dataList.push(this.int(cout));
            }
        }
        if (array instanceof Set) {
            for (const cout of array) {
                dataList.push(this.int(cout));
            }
        }
        return dataList;
    },
    /**
     * 拼合buff片段
     * @param buffList 
     * @returns 
     */
    concatBuff(buffList: Buffer[]): Buffer {
        let buffSize = 0;
        for (let index = 0; index < buffList.length; index++) {
            const buff = buffList[index];
            buffSize = buffSize + buff.byteLength;
        }
        let ResponseData = Buffer.concat([...buffList], buffSize);
        return ResponseData;
    },
};

/**
 * 判断当前进程是否有管理员权限
 * @returns 
 */
export function isAdmin(): boolean {
    return native.isAdmin();
}

/**
 * 枚举本机局域网中的ipv4地址
 * @returns 
 */
export function ipv4(): Array<HMN.ipv4Item> {
    return JSON.parse(native.ipv4() || "[]");
}

/**
 * 获取本机局域网的所以ip (并区分适配器,v4,v6)
 * @returns 
 */

export function ip(): Array<HMN.hmc_net_addr_item> {
    return JSON.parse(native.adapterIP() || "[]");
}

/**
 * 获取本机局域网的所以ip (并区分适配器,v4,v6)
 * @returns 
 */
export function adapterIP(): Array<HMN.hmc_net_addr_item> {
    return JSON.parse(native.adapterIP() || "[]");
}




/**
 * 枚举本机局域网中的ipv4地址
 * @returns 
 */
export function ipv4Async(): Promise<Array<HMN.ipv4Item>> {
    return new Promise((resolve, reject) => {
        try {
            native.ipv4Async().then(data => {
                resolve(JSON.parse(data || "[]") as Array<HMN.ipv4Item>)
            }).catch(reject);;
        } catch (error) {
            reject(error);
        }
    });
}

/**
 * 获取本机局域网的所以ip (并区分适配器,v4,v6)
 * @returns 
 */

export function ipAsync(): Promise<Array<HMN.hmc_net_addr_item>> {
    return new Promise((resolve, reject) => {
        try {
            native.adapterIPAsync().then(data => {
                resolve(JSON.parse(data || "[]") as Array<HMN.hmc_net_addr_item>)
            }).catch(reject);;
        } catch (error) {
            reject(error);
        }
    });
}

/**
 * 获取本机局域网的所以ip (并区分适配器,v4,v6)
 * @returns 
 */
export function adapterIPAsync(): Promise<Array<HMN.hmc_net_addr_item>> {
    return new Promise((resolve, reject) => {
        try {
            native.adapterIPAsync().then(data => {
                resolve(JSON.parse(data || "[]") as Array<HMN.hmc_net_addr_item>)
            }).catch(reject);;
        } catch (error) {
            reject(error);
        }
    });
}



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
export function getConnectNetList(tcp?: boolean, udp?: boolean, tcp6?: boolean, udp6?: boolean): Array<HMN.ConnectNet> {
    return JSON.parse(native.getConnectNetList(
        ref.bool(typeof tcp == "undefined" ? true : tcp),
        ref.bool(typeof udp == "undefined" ? true : udp),
        ref.bool(typeof tcp6 == "undefined" ? true : tcp6),
        ref.bool(typeof udp6 == "undefined" ? true : udp6)
    ) || "[]");
}


/**
 *  枚举此电脑中的 端口 ipv4 and ipv6 的 TCP，UDP 端口信息 异步
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
export async function getConnectNetListAsync(tcp?: boolean, udp?: boolean, tcp6?: boolean, udp6?: boolean): Promise<Array<HMN.ConnectNet>> {
    return new Promise<Array<HMN.ConnectNet>>((resolve, reject) => {
        try {
            native.getConnectNetListAsync(
                ref.bool(typeof tcp == "undefined" ? true : tcp),
                ref.bool(typeof udp == "undefined" ? true : udp),
                ref.bool(typeof tcp6 == "undefined" ? true : tcp6),
                ref.bool(typeof udp6 == "undefined" ? true : udp6)
            ).then(data => {
                resolve(JSON.parse(data || "[]"))
            });
        } catch (error) {
            reject(error);
        }
    });

}


/**
 * `Sync` 同步阻塞(进程)
 * @param awaitTime
 * @returns
 */
export function sleep(awaitTime: number) {
    return native.sleep(ref.int(awaitTime));
}

/**
 * `async` 异步阻塞(进程)
 * @param awaitTime
 * @returns
 */
export async function Sleep(awaitTime: number, Sync?: boolean) {
    if (Sync) {
        return sleep(ref.int(awaitTime));
    }
    return new Promise((resolve) =>
        setTimeout(resolve, ref.int(awaitTime))
    );
}

/**
 * 获取一个tcp空闲端口 (服务)
 * @returns 
 */
export function freePort(): Promise<number> {
    return new Promise((resolve, reject) => {
        let sock = net.createServer(function () { });
        sock.listen(0, () => {
            // @ts-expect-error
            resolve(Number(sock?.address()?.port as string));
            sock.close();
        });
    });
}

/**
 * 获取一个tcp空闲端口 (服务)
 * @returns 
 */
export function freePortTCP(): Promise<number> {
    return freePort();
}

/**
 * 获取一个UDP空闲端口
 * @returns 
 */
export function freePortUDP(): Promise<number> {
    return new Promise((resolve, reject) => {
        let udp4 = dgram.createSocket('udp4');
        udp4.bind(0);

        udp4.on("listening", function () {
            resolve && resolve(udp4.address().port);
            udp4.close();
        });

    });
}

/**
 * 判断TCP(服务)端口号正在使用/系统占用
 * @param port TCP端口
 * @returns 
 */
export function hasPortTCP(port: number): Promise<boolean>;
export function hasPortTCP(port: number, callBack: (hasPort: boolean) => unknown): void;
/**
 * 判断TCP(服务)端口号正在使用/系统占用
 * @param port TCP端口
 * @returns 
 */
export function hasPortTCP(port: number, callBack?: (hasPort: boolean) => unknown): unknown {
    let resolve: ((hasPort: boolean) => unknown) | null = null;
    let prom;
    let sock = net.createServer(function () { });
    sock.listen(port);
    if (typeof callBack == 'function') {
        resolve = callBack;
    } else {
        prom = new Promise((Prom_resolve) => {
            resolve = Prom_resolve;
        });
    }
    sock.on("error", function (err) {
        resolve && resolve(true);
        sock.close();
    });
    sock.on("listening", function () {
        resolve && resolve(false);
        sock.close();
    });
    if (typeof callBack !== 'function') {
        return prom;
    }
}


/**
 * 判断UDP端口号正在使用/系统占用
 * @param port TCP端口
 * @returns 
 */
export function hasPortUDP(port: number): Promise<boolean>;
export function hasPortUDP(port: number, callBack: (hasPort: boolean) => unknown): void;
/**
 * 判断UDP端口号正在使用/系统占用
 * @param port TCP端口
 * @returns 
 */
export function hasPortUDP(port: number, callBack?: (hasPort: boolean) => unknown): unknown {
    let resolve: ((hasPort: boolean) => unknown) | null = null;
    let prom;
    let udp4 = dgram.createSocket('udp4');
    udp4.bind(port);
    if (typeof callBack == 'function') {
        resolve = callBack;
    } else {
        prom = new Promise((Prom_resolve) => {
            resolve = Prom_resolve;
        });
    }
    udp4.on("error", function (err) {
        resolve && resolve(true);
        udp4.close();
    });
    udp4.on("listening", function () {
        resolve && resolve(false);
        udp4.close();
    });
    if (typeof callBack !== 'function') {
        return prom;
    }
}


// /**
//  * 当端口变更后发生回调
//  * - 占用进程变更
//  * - 端口释放
//  * - 端口启用
//  * @param CallBack 回调函数
//  * @param nextAwaitMs 每次判断内容变化用时 默认 `150` ms
//  * @returns 
//  */
// export function PortWatchdog(CallBack: (connect?: HMN.ConnectNet, oid_connect?: HMN.ConnectNet, all_connect_list?: Array<HMN.ConnectNet>) => void, nextAwaitMs?: number, tcp = false, udp = false, tcp6 = false, udp6 = false) {
//     let NextAwaitMs = nextAwaitMs || 150;
//     let Next = true;
//     let oidConnectNetList = getConnectNetList();
//     let oidData = {
//         tcp: new Map() as Map<number, number>,
//         udp: new Map() as Map<number, number>,
//         tcp6: new Map() as Map<number, Set<number>>,
//         udp6: new Map() as Map<number, Set<number>>
//     };

//     (async function () {
//         while (Next) {
//             await Sleep(NextAwaitMs);
//             let newConnectNetList = getConnectNetList();

//             if (0 !== 0) {
//                 if (CallBack) CallBack();
//             }

//             oidConnectNetList = newConnectNetList;
//         }
//     })();
//     return {
//         /**
//          * 取消继续监听
//          */
//         unwatcher() {
//             Next = false;
//         },
//         /**
//          * 每次判断内容变化用时 默认 `150` ms
//          * @param nextAwaitMs 
//          */
//         setNextAwaitMs(nextAwaitMs: number) {
//             NextAwaitMs = ref.int(nextAwaitMs) || 150;
//         }
//     }
// }

/**
 * 获取进程可执行文件位置
 * @param ProcessName 进程名
 * @returns 进程id
 */
export function getProcessidFilePath(ProcessID: number) {
    return native.getProcessidFilePath(ref.int(ProcessID));
}

/**
 * 获取进程可执行文件位置
 * @param ProcessName 进程名
 * @returns 进程id
 */
export function getProcessidFilePathAsync(ProcessID: number) {
    return new Promise((resolve, reject) => {
        try {
            native.getProcessidFilePathAsync(ref.int(ProcessID)).then(data => {
                resolve(data)
            }).catch(reject);
        } catch (error) {
            reject(error);
        }
    });
}

/**
 * 结束该进程
 * @param ProcessID 
 * @returns 
 */
export function killProcess(ProcessID: number): boolean;

export function killProcess(ProcessID: number) {
    return native.killProcess(ref.int(ProcessID));
}

/**
 * 获取此端口被哪个进程占用了
 * @param port 
 * @returns 
 */
export function getTCPv4PortProcessID(port: number) {
    return native.getTCPv4PortProcessID(ref.int(port));
}

/**
 * 获取此端口被哪个进程占用了
 * @param port 
 * @returns 
 */
export function getUDPv4PortProcessID(port: number) {
    return native.getUDPv4PortProcessID(ref.int(port));
}

/**
 * 获取此端口被哪个进程占用了
 * @param port 
 * @returns 
 */
export function getUDPv6PortProcessID(port: number) {
    return JSON.parse(native.getUDPv6PortProcessID(ref.int(port))) as number[];
}

/**
 * 获取此端口被哪个进程占用了
 * @param port 
 * @returns 
 */
export function getTCPv6PortProcessID(port: number) {
    return JSON.parse(native.getTCPv6PortProcessID(ref.int(port))) as number[];
}


/**
 * 获取此端口被哪个进程占用了
 * @param port 
 * @returns 
 */
export function getTCPv4PortProcessIDAsync(port: number) {
    return new Promise((resolve, reject) => {
        try {
            native.getPortProcessIDAsync(0, ref.int(port)).then(data => {
                const portList = JSON.parse(data || "[]") as Array<number>;
                if (!portList.length) {
                    resolve(null);
                } else {
                    resolve(portList[0]);
                }
            }).catch(reject);
        } catch (error) {
            reject(error);
        }
    });
}

/**
 * 获取此端口被哪个进程占用了
 * @param port 
 * @returns 
 */
export function getUDPv4PortProcessIDAsync(port: number) {
    return new Promise((resolve, reject) => {
        try {
            native.getPortProcessIDAsync(1, ref.int(port)).then(data => {
                const portList = JSON.parse(data || "[]") as Array<number>;
                if (!portList.length) {
                    resolve(null);
                } else {
                    resolve(portList[0]);
                }
            }).catch(reject);
        } catch (error) {
            reject(error);
        }
    });
}

/**
 * 获取此端口被哪个进程占用了
 * @param port 
 * @returns 
 */
export function getUDPv6PortProcessIDAsync(port: number) {
    return new Promise((resolve, reject) => {
        try {
            native.getPortProcessIDAsync(3, ref.int(port)).then(data => {
                resolve(JSON.parse(data || "[]") as Array<number>)
            }).catch(reject);
        } catch (error) {
            reject(error);
        }
    });
}

/**
 * 获取此端口被哪个进程占用了
 * @param port 
 * @returns 
 */
export function getTCPv6PortProcessIDAsync(port: number) {
    return new Promise((resolve, reject) => {
        try {
            native.getPortProcessIDAsync(2, ref.int(port)).then(data => {
                resolve(JSON.parse(data || "[]") as Array<number>)
            }).catch(reject);
        } catch (error) {
            reject(error);
        }
    });
}



/**
 * 获取hosts文件的路径
 * @returns 
 */
export function getHostsPath() {
    return native.getHostsPath();
}

/**
 * 从默认dns(联网)解析域名主机ip
 * - √ goole.com
 * - √ api.goole.com
 * - × api.goole.com/services
 * - × https://goole.com
 * @param url 
 * @returns ip列表
 */
export function getDomainIPaddress(url: string): Array<string> {
    return JSON.parse(native.getDomainIPaddress(ref.string(url)));
}

/**
 * 从默认dns(联网)解析域名主机ip
 * - √ goole.com
 * - √ api.goole.com
 * - × api.goole.com/services
 * - × https://goole.com
 * @param url 
 * @returns ip列表
 */
export function getDomainIPaddressAsync(url: string): Promise<Array<string>> {
    return new Promise((resolve, reject) => {
        try {
            native.getDomainIPaddressAsync(ref.string(url)).then((data) => {
                resolve(JSON.parse(data || "[]") as Array<string>)
            }).catch(reject);
        } catch (error) {
            reject(error);
        }
    });
}

/**
 * 获取系统代理pac脚本链接
 * @returns 
 */
export function getSystemProxyPac() {
    return native.getSystemProxyPac();
}

/**
 *  获取系统代理链接（仅在启用系统代理时）
 * @returns 
 */
export function getSystemProxyServer() {
    return native.getSystemProxyServer();
}

/**
 * 获取主机网络信息
 * @returns 
 */
export function getNetParams(): HMN.hmc_NetParams | null {
    return JSON.parse(native.getNetParams());
}


/**
 * 获取主机网络信息
 * @returns 
 */
export function getNetParamsAsync():Promise<HMN.hmc_NetParams> {

    return new Promise((resolve, reject) => {
        try {
            native.getNetParamsAsync().then((data) => {
                resolve(JSON.parse(data || "{}") as HMN.hmc_NetParams )
            }).catch(reject);
        } catch (error) {
            reject(error);
        }
    });
}

function https_get_data(url: string) {
    return new Promise<Buffer>((resolve, reject) => {
        const buffList: Buffer[] = [];
        (() => {
            if (url.match("https://")) {
                return https;
            } else {
                return http;
            }
        })().get(url, (res) => {
            if (res.statusCode !== 200) {
                reject(new Error(`get failure statusCode: ${res.statusCode || 404}`));
                return;
            }

            res.on("data", (data) => {
                buffList.push(data);
            });

            res.once("error", (err) => {
                reject(err);
            });

            res.on('end', () => {
                const buff = ref.concatBuff(buffList);
                resolve(buff);
                buffList.length = 0;
            });

        });
    });
}

/**
 * 获取公网ip
 * @returns 
 */
export function public_ip(): Promise<string> {

    return new Promise<string>(async (resolve, reject) => {
        let result_ok = false;

        // http://ipwho.is/: 295.327880859375 ms
        // http://httpbin.org/ip: 540.3720703125 ms
        // https://ipapi.co/json/: 811.548095703125 ms
        // https://api.ipify.org/?format=json: 846.34814453125 ms
        // https://api.ip.sb/geoip: 1026.965087890625 ms
        // https://freeipapi.com/api/json/: 1932.1220703125 ms
        // http://ip-api.com/json/?lang=zh-CN: 5383.945068359375 ms
        // ... 超时

        let ip_server_list = [
            ["http://ipwho.is/", "ip"],
            ["http://httpbin.org/ip", "origin"],
            ["https://ipapi.co/json/", "ip"],
            ["https://api.ipify.org/?format=json", "ip"],
            ["https://freeipapi.com/api/json/", "ipAddress"],
            ["https://api.ip.sb/geoip", "ip"],
            ["https://api.myip.com/", "ip"],
            ["http://ip-api.com/json/?lang=zh-CN", "ip"],

        ];

        for (const iterator of ip_server_list) {
            try {
                await https_get_data(iterator[0]).catch(() => Buffer.alloc(0)).then((response) => {
                    try {
                        let data = JSON.parse(response.toString("utf-8"));
                        if (data[iterator[1]]) {
                            result_ok = true;
                            resolve(data[iterator[1]]);
                        }
                    } catch (e) { }
                });
                if (result_ok) {
                    return;
                }

            } catch (e) { }
        }


        reject();
    });

}

process.on('exit', function () {

});

