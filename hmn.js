"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.public_ip = exports.getNetParamsAsync = exports.getNetParams = exports.getSystemProxyServer = exports.getSystemProxyPac = exports.getDomainIPaddressAsync = exports.getDomainIPaddress = exports.getHostsPath = exports.getTCPv6PortProcessIDAsync = exports.getUDPv6PortProcessIDAsync = exports.getUDPv4PortProcessIDAsync = exports.getTCPv4PortProcessIDAsync = exports.getTCPv6PortProcessID = exports.getUDPv6PortProcessID = exports.getUDPv4PortProcessID = exports.getTCPv4PortProcessID = exports.killProcess = exports.getProcessidFilePathAsync = exports.getProcessidFilePath = exports.hasPortUDP = exports.hasPortTCP = exports.freePortUDP = exports.freePortTCP = exports.freePort = exports.Sleep = exports.sleep = exports.getConnectNetListAsync = exports.getConnectNetList = exports.adapterIPAsync = exports.ipAsync = exports.ipv4Async = exports.adapterIP = exports.ip = exports.ipv4 = exports.isAdmin = exports.ref = exports.HMN = exports.native = void 0;
const path = require("path");
const https = require("https");
const http = require("http");
const dgram = require("dgram");
const net = require("net");
/**
 * @zh-cn 静态调用 hmn.dll (注意如果您不知道这个是什么作用 请勿随意调用 参数错误有可能会导致进程崩溃)
 * @en-us Static call to hmn.dll (Note that if you don't know what this does, don't call it at random.  Parameter errors may cause the process to crash)
 */
const get_native = (binPath) => {
    function _require_bin() {
        try {
            if (binPath)
                return require(binPath);
            if (process.arch.match(/^x32|ia32$/))
                return require("./bin/HMN_x86.node");
            if (process.arch.match(/^x64$/))
                return require("./bin/HMN_x64.node");
        }
        catch (X_X) {
        }
        return null;
    }
    let Native = (process.platform == "win32" ? _require_bin() : null) || (() => {
        let HMCNotPlatform = "HMC::HMC current method only supports win32 platform";
        function fnBool(...args) { console.error(HMCNotPlatform); return false; }
        function fnVoid(...args) { console.error(HMCNotPlatform); return undefined; }
        function fnNull(...args) { console.error(HMCNotPlatform); return null; }
        function fnNum(...args) { console.error(HMCNotPlatform); return 0; }
        function fnStrList(...args) { console.error(HMCNotPlatform); return []; }
        function fnStr(...args) { console.error(HMCNotPlatform); return ''; }
        function fnAnyArr(...args) { console.error(HMCNotPlatform); return []; }
        function fnArrayStr(...args) { console.error(HMCNotPlatform); return '[]'; }
        function fnPromise(...args) { console.error(HMCNotPlatform); return Promise.reject("HMC::HMC current method only supports win32 platform"); }
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
            getNetParamsAsync: fnPromise,
        };
    })();
    return Native;
};
exports.native = get_native();
// 类型
var HMN;
(function (HMN) {
    let network_type;
    (function (network_type) {
        network_type[network_type["AF_UNSPEC"] = 0] = "AF_UNSPEC";
        network_type[network_type["AF_UNIX"] = 1] = "AF_UNIX";
        network_type[network_type["AF_INET"] = 2] = "AF_INET";
        network_type[network_type["AF_IMPLINK"] = 3] = "AF_IMPLINK";
        network_type[network_type["AF_PUP"] = 4] = "AF_PUP";
        network_type[network_type["AF_CHAOS"] = 5] = "AF_CHAOS";
        network_type[network_type["AF_NS"] = 6] = "AF_NS";
        network_type[network_type["AF_IPX"] = 6] = "AF_IPX";
        network_type[network_type["AF_ISO"] = 7] = "AF_ISO";
        network_type[network_type["AF_OSI"] = 7] = "AF_OSI";
        network_type[network_type["AF_ECMA"] = 8] = "AF_ECMA";
        network_type[network_type["AF_DATAKIT"] = 9] = "AF_DATAKIT";
        network_type[network_type["AF_CCITT"] = 10] = "AF_CCITT";
        network_type[network_type["AF_SNA"] = 11] = "AF_SNA";
        network_type[network_type["AF_DECnet"] = 12] = "AF_DECnet";
        network_type[network_type["AF_DLI"] = 13] = "AF_DLI";
        network_type[network_type["AF_LAT"] = 14] = "AF_LAT";
        network_type[network_type["AF_HYLINK"] = 15] = "AF_HYLINK";
        network_type[network_type["AF_APPLETALK"] = 16] = "AF_APPLETALK";
        network_type[network_type["AF_NETBIOS"] = 17] = "AF_NETBIOS";
        network_type[network_type["AF_VOICEVIEW"] = 18] = "AF_VOICEVIEW";
        network_type[network_type["AF_FIREFOX"] = 19] = "AF_FIREFOX";
        network_type[network_type["AF_UNKNOWN1"] = 20] = "AF_UNKNOWN1";
        network_type[network_type["AF_BAN"] = 21] = "AF_BAN";
        network_type[network_type["AF_ATM"] = 22] = "AF_ATM";
        network_type[network_type["AF_INET6"] = 23] = "AF_INET6";
        network_type[network_type["AF_CLUSTER"] = 24] = "AF_CLUSTER";
        network_type[network_type["AF_12844"] = 25] = "AF_12844";
        network_type[network_type["AF_IRDA"] = 26] = "AF_IRDA";
        network_type[network_type["AF_NETDES"] = 28] = "AF_NETDES";
    })(network_type = HMN.network_type || (HMN.network_type = {}));
})(HMN = exports.HMN || (exports.HMN = {}));
exports.ref = {
    /**
    * 将内容格式化为文本路径
    * @param Str
    * @returns
    */
    path(Str) {
        return path.resolve(String(Str || "")).replace(/([\0\n\r]+)?$/, '\0');
    },
    /**
     * 格式化为bool
     * @param bool
     * @returns
     */
    bool(bool) {
        return bool ? true : false;
    },
    /**
     * 将内容格式化为文本
     * @param Str
     * @returns
     */
    string(Str) {
        return String(Str || "");
    },
    /**
     * 格式化数字为int(强制)
     * @param Num
     * @returns
     */
    int(Num) {
        if (!Num)
            return 0;
        if (typeof Num == "object" && Num instanceof Number) {
            Num = Num === null || Num === void 0 ? void 0 : Num.valueOf();
        }
        // 取整
        Num = Math.trunc(Num + 0);
        if (typeof Num == "number" && !isNaN(Num))
            return Num;
        // true == 1
        if (Num && typeof Num == "boolean")
            Num = 1;
        // false = 0;
        if (!Num && typeof Num == "boolean")
            Num = 0;
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
    stringArray(array) {
        let dataList = [];
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
    intArray(array) {
        let dataList = [];
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
    concatBuff(buffList) {
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
function isAdmin() {
    return exports.native.isAdmin();
}
exports.isAdmin = isAdmin;
/**
 * 枚举本机局域网中的ipv4地址
 * @returns
 */
function ipv4() {
    return JSON.parse(exports.native.ipv4() || "[]");
}
exports.ipv4 = ipv4;
/**
 * 获取本机局域网的所以ip (并区分适配器,v4,v6)
 * @returns
 */
function ip() {
    return JSON.parse(exports.native.adapterIP() || "[]");
}
exports.ip = ip;
/**
 * 获取本机局域网的所以ip (并区分适配器,v4,v6)
 * @returns
 */
function adapterIP() {
    return JSON.parse(exports.native.adapterIP() || "[]");
}
exports.adapterIP = adapterIP;
/**
 * 枚举本机局域网中的ipv4地址
 * @returns
 */
function ipv4Async() {
    return new Promise((resolve, reject) => {
        try {
            exports.native.ipv4Async().then(data => {
                resolve(JSON.parse(data || "[]"));
            }).catch(reject);
            ;
        }
        catch (error) {
            reject(error);
        }
    });
}
exports.ipv4Async = ipv4Async;
/**
 * 获取本机局域网的所以ip (并区分适配器,v4,v6)
 * @returns
 */
function ipAsync() {
    return new Promise((resolve, reject) => {
        try {
            exports.native.adapterIPAsync().then(data => {
                resolve(JSON.parse(data || "[]"));
            }).catch(reject);
            ;
        }
        catch (error) {
            reject(error);
        }
    });
}
exports.ipAsync = ipAsync;
/**
 * 获取本机局域网的所以ip (并区分适配器,v4,v6)
 * @returns
 */
function adapterIPAsync() {
    return new Promise((resolve, reject) => {
        try {
            exports.native.adapterIPAsync().then(data => {
                resolve(JSON.parse(data || "[]"));
            }).catch(reject);
            ;
        }
        catch (error) {
            reject(error);
        }
    });
}
exports.adapterIPAsync = adapterIPAsync;
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
function getConnectNetList(tcp, udp, tcp6, udp6) {
    return JSON.parse(exports.native.getConnectNetList(exports.ref.bool(typeof tcp == "undefined" ? true : tcp), exports.ref.bool(typeof udp == "undefined" ? true : udp), exports.ref.bool(typeof tcp6 == "undefined" ? true : tcp6), exports.ref.bool(typeof udp6 == "undefined" ? true : udp6)) || "[]");
}
exports.getConnectNetList = getConnectNetList;
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
async function getConnectNetListAsync(tcp, udp, tcp6, udp6) {
    return new Promise((resolve, reject) => {
        try {
            exports.native.getConnectNetListAsync(exports.ref.bool(typeof tcp == "undefined" ? true : tcp), exports.ref.bool(typeof udp == "undefined" ? true : udp), exports.ref.bool(typeof tcp6 == "undefined" ? true : tcp6), exports.ref.bool(typeof udp6 == "undefined" ? true : udp6)).then(data => {
                resolve(JSON.parse(data || "[]"));
            });
        }
        catch (error) {
            reject(error);
        }
    });
}
exports.getConnectNetListAsync = getConnectNetListAsync;
/**
 * `Sync` 同步阻塞(进程)
 * @param awaitTime
 * @returns
 */
function sleep(awaitTime) {
    return exports.native.sleep(exports.ref.int(awaitTime));
}
exports.sleep = sleep;
/**
 * `async` 异步阻塞(进程)
 * @param awaitTime
 * @returns
 */
async function Sleep(awaitTime, Sync) {
    if (Sync) {
        return sleep(exports.ref.int(awaitTime));
    }
    return new Promise((resolve) => setTimeout(resolve, exports.ref.int(awaitTime)));
}
exports.Sleep = Sleep;
/**
 * 获取一个tcp空闲端口 (服务)
 * @returns
 */
function freePort() {
    return new Promise((resolve, reject) => {
        let sock = net.createServer(function () { });
        sock.listen(0, () => {
            var _a;
            // @ts-expect-error
            resolve(Number((_a = sock === null || sock === void 0 ? void 0 : sock.address()) === null || _a === void 0 ? void 0 : _a.port));
            sock.close();
        });
    });
}
exports.freePort = freePort;
/**
 * 获取一个tcp空闲端口 (服务)
 * @returns
 */
function freePortTCP() {
    return freePort();
}
exports.freePortTCP = freePortTCP;
/**
 * 获取一个UDP空闲端口
 * @returns
 */
function freePortUDP() {
    return new Promise((resolve, reject) => {
        let udp4 = dgram.createSocket('udp4');
        udp4.bind(0);
        udp4.on("listening", function () {
            resolve && resolve(udp4.address().port);
            udp4.close();
        });
    });
}
exports.freePortUDP = freePortUDP;
/**
 * 判断TCP(服务)端口号正在使用/系统占用
 * @param port TCP端口
 * @returns
 */
function hasPortTCP(port, callBack) {
    let resolve = null;
    let prom;
    let sock = net.createServer(function () { });
    sock.listen(port);
    if (typeof callBack == 'function') {
        resolve = callBack;
    }
    else {
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
exports.hasPortTCP = hasPortTCP;
/**
 * 判断UDP端口号正在使用/系统占用
 * @param port TCP端口
 * @returns
 */
function hasPortUDP(port, callBack) {
    let resolve = null;
    let prom;
    let udp4 = dgram.createSocket('udp4');
    udp4.bind(port);
    if (typeof callBack == 'function') {
        resolve = callBack;
    }
    else {
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
exports.hasPortUDP = hasPortUDP;
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
function getProcessidFilePath(ProcessID) {
    return exports.native.getProcessidFilePath(exports.ref.int(ProcessID));
}
exports.getProcessidFilePath = getProcessidFilePath;
/**
 * 获取进程可执行文件位置
 * @param ProcessName 进程名
 * @returns 进程id
 */
function getProcessidFilePathAsync(ProcessID) {
    return new Promise((resolve, reject) => {
        try {
            exports.native.getProcessidFilePathAsync(exports.ref.int(ProcessID)).then(data => {
                resolve(data);
            }).catch(reject);
        }
        catch (error) {
            reject(error);
        }
    });
}
exports.getProcessidFilePathAsync = getProcessidFilePathAsync;
function killProcess(ProcessID) {
    return exports.native.killProcess(exports.ref.int(ProcessID));
}
exports.killProcess = killProcess;
/**
 * 获取此端口被哪个进程占用了
 * @param port
 * @returns
 */
function getTCPv4PortProcessID(port) {
    return exports.native.getTCPv4PortProcessID(exports.ref.int(port));
}
exports.getTCPv4PortProcessID = getTCPv4PortProcessID;
/**
 * 获取此端口被哪个进程占用了
 * @param port
 * @returns
 */
function getUDPv4PortProcessID(port) {
    return exports.native.getUDPv4PortProcessID(exports.ref.int(port));
}
exports.getUDPv4PortProcessID = getUDPv4PortProcessID;
/**
 * 获取此端口被哪个进程占用了
 * @param port
 * @returns
 */
function getUDPv6PortProcessID(port) {
    return JSON.parse(exports.native.getUDPv6PortProcessID(exports.ref.int(port)));
}
exports.getUDPv6PortProcessID = getUDPv6PortProcessID;
/**
 * 获取此端口被哪个进程占用了
 * @param port
 * @returns
 */
function getTCPv6PortProcessID(port) {
    return JSON.parse(exports.native.getTCPv6PortProcessID(exports.ref.int(port)));
}
exports.getTCPv6PortProcessID = getTCPv6PortProcessID;
/**
 * 获取此端口被哪个进程占用了
 * @param port
 * @returns
 */
function getTCPv4PortProcessIDAsync(port) {
    return new Promise((resolve, reject) => {
        try {
            exports.native.getPortProcessIDAsync(0, exports.ref.int(port)).then(data => {
                const portList = JSON.parse(data || "[]");
                if (!portList.length) {
                    resolve(null);
                }
                else {
                    resolve(portList[0]);
                }
            }).catch(reject);
        }
        catch (error) {
            reject(error);
        }
    });
}
exports.getTCPv4PortProcessIDAsync = getTCPv4PortProcessIDAsync;
/**
 * 获取此端口被哪个进程占用了
 * @param port
 * @returns
 */
function getUDPv4PortProcessIDAsync(port) {
    return new Promise((resolve, reject) => {
        try {
            exports.native.getPortProcessIDAsync(1, exports.ref.int(port)).then(data => {
                const portList = JSON.parse(data || "[]");
                if (!portList.length) {
                    resolve(null);
                }
                else {
                    resolve(portList[0]);
                }
            }).catch(reject);
        }
        catch (error) {
            reject(error);
        }
    });
}
exports.getUDPv4PortProcessIDAsync = getUDPv4PortProcessIDAsync;
/**
 * 获取此端口被哪个进程占用了
 * @param port
 * @returns
 */
function getUDPv6PortProcessIDAsync(port) {
    return new Promise((resolve, reject) => {
        try {
            exports.native.getPortProcessIDAsync(3, exports.ref.int(port)).then(data => {
                resolve(JSON.parse(data || "[]"));
            }).catch(reject);
        }
        catch (error) {
            reject(error);
        }
    });
}
exports.getUDPv6PortProcessIDAsync = getUDPv6PortProcessIDAsync;
/**
 * 获取此端口被哪个进程占用了
 * @param port
 * @returns
 */
function getTCPv6PortProcessIDAsync(port) {
    return new Promise((resolve, reject) => {
        try {
            exports.native.getPortProcessIDAsync(2, exports.ref.int(port)).then(data => {
                resolve(JSON.parse(data || "[]"));
            }).catch(reject);
        }
        catch (error) {
            reject(error);
        }
    });
}
exports.getTCPv6PortProcessIDAsync = getTCPv6PortProcessIDAsync;
/**
 * 获取hosts文件的路径
 * @returns
 */
function getHostsPath() {
    return exports.native.getHostsPath();
}
exports.getHostsPath = getHostsPath;
/**
 * 从默认dns(联网)解析域名主机ip
 * - √ goole.com
 * - √ api.goole.com
 * - × api.goole.com/services
 * - × https://goole.com
 * @param url
 * @returns ip列表
 */
function getDomainIPaddress(url) {
    return JSON.parse(exports.native.getDomainIPaddress(exports.ref.string(url)));
}
exports.getDomainIPaddress = getDomainIPaddress;
/**
 * 从默认dns(联网)解析域名主机ip
 * - √ goole.com
 * - √ api.goole.com
 * - × api.goole.com/services
 * - × https://goole.com
 * @param url
 * @returns ip列表
 */
function getDomainIPaddressAsync(url) {
    return new Promise((resolve, reject) => {
        try {
            exports.native.getDomainIPaddressAsync(exports.ref.string(url)).then((data) => {
                resolve(JSON.parse(data || "[]"));
            }).catch(reject);
        }
        catch (error) {
            reject(error);
        }
    });
}
exports.getDomainIPaddressAsync = getDomainIPaddressAsync;
/**
 * 获取系统代理pac脚本链接
 * @returns
 */
function getSystemProxyPac() {
    return exports.native.getSystemProxyPac();
}
exports.getSystemProxyPac = getSystemProxyPac;
/**
 *  获取系统代理链接（仅在启用系统代理时）
 * @returns
 */
function getSystemProxyServer() {
    return exports.native.getSystemProxyServer();
}
exports.getSystemProxyServer = getSystemProxyServer;
/**
 * 获取主机网络信息
 * @returns
 */
function getNetParams() {
    return JSON.parse(exports.native.getNetParams());
}
exports.getNetParams = getNetParams;
/**
 * 获取主机网络信息
 * @returns
 */
function getNetParamsAsync() {
    return new Promise((resolve, reject) => {
        try {
            exports.native.getNetParamsAsync().then((data) => {
                resolve(JSON.parse(data || "{}"));
            }).catch(reject);
        }
        catch (error) {
            reject(error);
        }
    });
}
exports.getNetParamsAsync = getNetParamsAsync;
function https_get_data(url) {
    return new Promise((resolve, reject) => {
        const buffList = [];
        (() => {
            if (url.match("https://")) {
                return https;
            }
            else {
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
                const buff = exports.ref.concatBuff(buffList);
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
function public_ip() {
    return new Promise(async (resolve, reject) => {
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
                    }
                    catch (e) { }
                });
                if (result_ok) {
                    return;
                }
            }
            catch (e) { }
        }
        reject();
    });
}
exports.public_ip = public_ip;
process.on('exit', function () {
});
