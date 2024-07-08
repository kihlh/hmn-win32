"use strict";
var __defProp = Object.defineProperty;
var __getOwnPropDesc = Object.getOwnPropertyDescriptor;
var __getOwnPropNames = Object.getOwnPropertyNames;
var __hasOwnProp = Object.prototype.hasOwnProperty;
var __export = (target, all) => {
  for (var name in all)
    __defProp(target, name, { get: all[name], enumerable: true });
};
var __copyProps = (to, from, except, desc) => {
  if (from && typeof from === "object" || typeof from === "function") {
    for (let key of __getOwnPropNames(from))
      if (!__hasOwnProp.call(to, key) && key !== except)
        __defProp(to, key, { get: () => from[key], enumerable: !(desc = __getOwnPropDesc(from, key)) || desc.enumerable });
  }
  return to;
};
var __toCommonJS = (mod) => __copyProps(__defProp({}, "__esModule", { value: true }), mod);

// source/mian/hmn.ts
var hmn_exports = {};
__export(hmn_exports, {
  HMN: () => HMN,
  Sleep: () => Sleep,
  adapterIP: () => adapterIP,
  adapterIPAsync: () => adapterIPAsync,
  asyncTaskQueue: () => asyncTaskQueue,
  freePort: () => freePort,
  freePortTCP: () => freePortTCP,
  freePortUDP: () => freePortUDP,
  getConnectNetList: () => getConnectNetList,
  getConnectNetListAsync: () => getConnectNetListAsync,
  getDomainIPaddress: () => getDomainIPaddress,
  getDomainIPaddressAsync: () => getDomainIPaddressAsync,
  getHostsPath: () => getHostsPath,
  getNetParams: () => getNetParams,
  getNetParamsAsync: () => getNetParamsAsync,
  getProcessidFilePath: () => getProcessidFilePath,
  getProcessidFilePathAsync: () => getProcessidFilePathAsync,
  getSystemProxyPac: () => getSystemProxyPac,
  getSystemProxyServer: () => getSystemProxyServer,
  getTCPv4PortProcessID: () => getTCPv4PortProcessID,
  getTCPv4PortProcessIDAsync: () => getTCPv4PortProcessIDAsync,
  getTCPv6PortProcessID: () => getTCPv6PortProcessID,
  getTCPv6PortProcessIDAsync: () => getTCPv6PortProcessIDAsync,
  getUDPv4PortProcessID: () => getUDPv4PortProcessID,
  getUDPv4PortProcessIDAsync: () => getUDPv4PortProcessIDAsync,
  getUDPv6PortProcessID: () => getUDPv6PortProcessID,
  getUDPv6PortProcessIDAsync: () => getUDPv6PortProcessIDAsync,
  hasPortTCP: () => hasPortTCP,
  hasPortUDP: () => hasPortUDP,
  ip: () => ip,
  ipAsync: () => ipAsync,
  ipv4: () => ipv4,
  ipv4Async: () => ipv4Async,
  isAdmin: () => isAdmin,
  killProcess: () => killProcess,
  native: () => native,
  public_ip: () => public_ip,
  ref: () => ref,
  sleep: () => sleep
});
module.exports = __toCommonJS(hmn_exports);
var path = require("path");
var os = require("os");
var fs = require("fs");
var https = require("https");
var http = require("http");
var dgram = require("dgram");
var net = require("net");
var AsyncFunctionTaskQueue = class {
  constructor() {
    this.queues = /* @__PURE__ */ new Map();
  }
  async runTask(fn, ...args) {
    if (!this.queues.has(fn)) {
      this.queues.set(fn, {
        queue: [],
        executing: false
      });
    }
    const queueObj = this.queues.get(fn);
    return new Promise((resolve, reject) => {
      queueObj.queue.push({ args, resolve, reject });
      this.next(fn);
    });
  }
  async next(fn) {
    const queueObj = this.queues.get(fn);
    if (queueObj.executing || queueObj.queue.length === 0) {
      return;
    }
    const { args, resolve, reject } = queueObj.queue.shift();
    queueObj.executing = true;
    try {
      const result = await fn(...args);
      resolve(result);
    } catch (error) {
      reject(error);
    } finally {
      queueObj.executing = false;
      this.next(fn);
    }
  }
};
var asyncTaskQueue = new AsyncFunctionTaskQueue();
var get_native = (binPath) => {
  function _require_bin() {
    try {
      if (binPath)
        return require(binPath);
      if (process.arch.match(/^x32|ia32$/))
        return require("./bin/HMN_x86.node");
      if (process.arch.match(/^x64$/))
        return require("./bin/HMN_x64.node");
    } catch (X_X) {
    }
    return null;
  }
  let Native = (process.platform == "win32" ? _require_bin() : null) || (() => {
    let HMCNotPlatform = "HMC::HMC current method only supports win32 platform";
    function fnBool(...args) {
      console.error(HMCNotPlatform);
      return false;
    }
    function fnVoid(...args) {
      console.error(HMCNotPlatform);
      return void 0;
    }
    function fnNull(...args) {
      console.error(HMCNotPlatform);
      return null;
    }
    function fnNum(...args) {
      console.error(HMCNotPlatform);
      return 0;
    }
    function fnStrList(...args) {
      console.error(HMCNotPlatform);
      return [];
    }
    function fnStr(...args) {
      console.error(HMCNotPlatform);
      return "";
    }
    function fnAnyArr(...args) {
      console.error(HMCNotPlatform);
      return [];
    }
    function fnArrayStr(...args) {
      console.error(HMCNotPlatform);
      return "[]";
    }
    function fnPromise(...args) {
      console.error(HMCNotPlatform);
      return Promise.reject("HMC::HMC current method only supports win32 platform");
    }
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
      getNetParamsAsync: fnPromise
    };
  })();
  return Native;
};
var native = get_native();
var HMN;
((HMN2) => {
  let network_type;
  ((network_type2) => {
    network_type2[network_type2["AF_UNSPEC"] = 0] = "AF_UNSPEC";
    network_type2[network_type2["AF_UNIX"] = 1] = "AF_UNIX";
    network_type2[network_type2["AF_INET"] = 2] = "AF_INET";
    network_type2[network_type2["AF_IMPLINK"] = 3] = "AF_IMPLINK";
    network_type2[network_type2["AF_PUP"] = 4] = "AF_PUP";
    network_type2[network_type2["AF_CHAOS"] = 5] = "AF_CHAOS";
    network_type2[network_type2["AF_NS"] = 6] = "AF_NS";
    network_type2[network_type2["AF_IPX"] = 6] = "AF_IPX";
    network_type2[network_type2["AF_ISO"] = 7] = "AF_ISO";
    network_type2[network_type2["AF_OSI"] = 7] = "AF_OSI";
    network_type2[network_type2["AF_ECMA"] = 8] = "AF_ECMA";
    network_type2[network_type2["AF_DATAKIT"] = 9] = "AF_DATAKIT";
    network_type2[network_type2["AF_CCITT"] = 10] = "AF_CCITT";
    network_type2[network_type2["AF_SNA"] = 11] = "AF_SNA";
    network_type2[network_type2["AF_DECnet"] = 12] = "AF_DECnet";
    network_type2[network_type2["AF_DLI"] = 13] = "AF_DLI";
    network_type2[network_type2["AF_LAT"] = 14] = "AF_LAT";
    network_type2[network_type2["AF_HYLINK"] = 15] = "AF_HYLINK";
    network_type2[network_type2["AF_APPLETALK"] = 16] = "AF_APPLETALK";
    network_type2[network_type2["AF_NETBIOS"] = 17] = "AF_NETBIOS";
    network_type2[network_type2["AF_VOICEVIEW"] = 18] = "AF_VOICEVIEW";
    network_type2[network_type2["AF_FIREFOX"] = 19] = "AF_FIREFOX";
    network_type2[network_type2["AF_UNKNOWN1"] = 20] = "AF_UNKNOWN1";
    network_type2[network_type2["AF_BAN"] = 21] = "AF_BAN";
    network_type2[network_type2["AF_ATM"] = 22] = "AF_ATM";
    network_type2[network_type2["AF_INET6"] = 23] = "AF_INET6";
    network_type2[network_type2["AF_CLUSTER"] = 24] = "AF_CLUSTER";
    network_type2[network_type2["AF_12844"] = 25] = "AF_12844";
    network_type2[network_type2["AF_IRDA"] = 26] = "AF_IRDA";
    network_type2[network_type2["AF_NETDES"] = 28] = "AF_NETDES";
  })(network_type = HMN2.network_type || (HMN2.network_type = {}));
})(HMN || (HMN = {}));
var ref = {
  /**
  * 将内容格式化为文本路径
  * @param Str
  * @returns
  */
  path(Str) {
    return path.resolve(String(Str || "")).replace(/([\0\n\r]+)?$/, "\0");
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
      Num = Num == null ? void 0 : Num.valueOf();
    }
    Num = Math.trunc(Num + 0);
    if (typeof Num == "number" && !isNaN(Num))
      return Num;
    if (Num && typeof Num == "boolean")
      Num = 1;
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
  }
};
function isAdmin() {
  return native.isAdmin();
}
function ipv4() {
  return JSON.parse(native.ipv4() || "[]");
}
function ip() {
  return JSON.parse(native.adapterIP() || "[]");
}
function adapterIP() {
  return JSON.parse(native.adapterIP() || "[]");
}
function ipv4Async() {
  return new Promise((resolve, reject) => {
    try {
      asyncTaskQueue.runTask(native.ipv4Async).then((data) => {
        resolve(JSON.parse(data || "[]"));
      }).catch(reject);
      ;
    } catch (error) {
      reject(error);
    }
  });
}
function ipAsync() {
  return new Promise((resolve, reject) => {
    try {
      asyncTaskQueue.runTask(native.adapterIPAsync).then((data) => {
        resolve(JSON.parse(data || "[]"));
      }).catch(reject);
      ;
    } catch (error) {
      reject(error);
    }
  });
}
function adapterIPAsync() {
  return new Promise((resolve, reject) => {
    try {
      asyncTaskQueue.runTask(native.adapterIPAsync).then((data) => {
        resolve(JSON.parse(data || "[]"));
      }).catch(reject);
      ;
    } catch (error) {
      reject(error);
    }
  });
}
function getConnectNetList(tcp, udp, tcp6, udp6) {
  return JSON.parse(native.getConnectNetList(
    ref.bool(typeof tcp == "undefined" ? true : tcp),
    ref.bool(typeof udp == "undefined" ? true : udp),
    ref.bool(typeof tcp6 == "undefined" ? true : tcp6),
    ref.bool(typeof udp6 == "undefined" ? true : udp6)
  ) || "[]");
}
async function getConnectNetListAsync(tcp, udp, tcp6, udp6) {
  return new Promise((resolve, reject) => {
    try {
      asyncTaskQueue.runTask(
        native.getConnectNetListAsync,
        ref.bool(typeof tcp == "undefined" ? true : tcp),
        ref.bool(typeof udp == "undefined" ? true : udp),
        ref.bool(typeof tcp6 == "undefined" ? true : tcp6),
        ref.bool(typeof udp6 == "undefined" ? true : udp6)
      ).then((data) => {
        resolve(JSON.parse(data || "[]"));
      });
    } catch (error) {
      reject(error);
    }
  });
}
function sleep(awaitTime) {
  return native.sleep(ref.int(awaitTime));
}
async function Sleep(awaitTime, Sync) {
  if (Sync) {
    return sleep(ref.int(awaitTime));
  }
  return new Promise(
    (resolve) => setTimeout(resolve, ref.int(awaitTime))
  );
}
function freePort() {
  return new Promise((resolve, reject) => {
    let sock = net.createServer(function() {
    });
    sock.listen(0, () => {
      var _a;
      resolve(Number((_a = sock == null ? void 0 : sock.address()) == null ? void 0 : _a.port));
      sock.close();
    });
  });
}
function freePortTCP() {
  return freePort();
}
function freePortUDP() {
  return new Promise((resolve, reject) => {
    let udp4 = dgram.createSocket("udp4");
    udp4.bind(0);
    udp4.on("listening", function() {
      resolve && resolve(udp4.address().port);
      udp4.close();
    });
  });
}
function hasPortTCP(port, callBack) {
  let resolve = null;
  let prom;
  let sock = net.createServer(function() {
  });
  sock.listen(port);
  if (typeof callBack == "function") {
    resolve = callBack;
  } else {
    prom = new Promise((Prom_resolve) => {
      resolve = Prom_resolve;
    });
  }
  sock.on("error", function(err) {
    resolve && resolve(true);
    sock.close();
  });
  sock.on("listening", function() {
    resolve && resolve(false);
    sock.close();
  });
  if (typeof callBack !== "function") {
    return prom;
  }
}
function hasPortUDP(port, callBack) {
  let resolve = null;
  let prom;
  let udp4 = dgram.createSocket("udp4");
  udp4.bind(port);
  if (typeof callBack == "function") {
    resolve = callBack;
  } else {
    prom = new Promise((Prom_resolve) => {
      resolve = Prom_resolve;
    });
  }
  udp4.on("error", function(err) {
    resolve && resolve(true);
    udp4.close();
  });
  udp4.on("listening", function() {
    resolve && resolve(false);
    udp4.close();
  });
  if (typeof callBack !== "function") {
    return prom;
  }
}
function getProcessidFilePath(ProcessID) {
  return native.getProcessidFilePath(ref.int(ProcessID));
}
function getProcessidFilePathAsync(ProcessID) {
  return new Promise((resolve, reject) => {
    try {
      asyncTaskQueue.runTask(native.getProcessidFilePathAsync, ref.int(ProcessID)).then((data) => {
        resolve(data);
      }).catch(reject);
    } catch (error) {
      reject(error);
    }
  });
}
function killProcess(ProcessID) {
  return native.killProcess(ref.int(ProcessID));
}
function getTCPv4PortProcessID(port) {
  return native.getTCPv4PortProcessID(ref.int(port));
}
function getUDPv4PortProcessID(port) {
  return native.getUDPv4PortProcessID(ref.int(port));
}
function getUDPv6PortProcessID(port) {
  return JSON.parse(native.getUDPv6PortProcessID(ref.int(port)));
}
function getTCPv6PortProcessID(port) {
  return JSON.parse(native.getTCPv6PortProcessID(ref.int(port)));
}
function getTCPv4PortProcessIDAsync(port) {
  return new Promise((resolve, reject) => {
    try {
      asyncTaskQueue.runTask(native.getPortProcessIDAsync, 0, ref.int(port)).then((data) => {
        const portList = JSON.parse(data || "[]");
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
function getUDPv4PortProcessIDAsync(port) {
  return new Promise((resolve, reject) => {
    try {
      asyncTaskQueue.runTask(native.getPortProcessIDAsync, 1, ref.int(port)).then((data) => {
        const portList = JSON.parse(data || "[]");
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
function getUDPv6PortProcessIDAsync(port) {
  return new Promise((resolve, reject) => {
    try {
      asyncTaskQueue.runTask(native.getPortProcessIDAsync, 3, ref.int(port)).then((data) => {
        resolve(JSON.parse(data || "[]"));
      }).catch(reject);
    } catch (error) {
      reject(error);
    }
  });
}
function getTCPv6PortProcessIDAsync(port) {
  return new Promise((resolve, reject) => {
    try {
      asyncTaskQueue.runTask(native.getPortProcessIDAsync, 2, ref.int(port)).then((data) => {
        resolve(JSON.parse(data || "[]"));
      }).catch(reject);
    } catch (error) {
      reject(error);
    }
  });
}
function getHostsPath() {
  return native.getHostsPath();
}
function getDomainIPaddress(url) {
  return JSON.parse(native.getDomainIPaddress(ref.string(url)));
}
function getDomainIPaddressAsync(url) {
  return new Promise((resolve, reject) => {
    try {
      asyncTaskQueue.runTask(native.getDomainIPaddressAsync, ref.string(url)).then((data) => {
        resolve(JSON.parse(data || "[]"));
      }).catch(reject);
    } catch (error) {
      reject(error);
    }
  });
}
function getSystemProxyPac() {
  return native.getSystemProxyPac();
}
function getSystemProxyServer() {
  return native.getSystemProxyServer();
}
function getNetParams() {
  return JSON.parse(native.getNetParams());
}
function getNetParamsAsync() {
  return new Promise((resolve, reject) => {
    try {
      asyncTaskQueue.runTask(native.getNetParamsAsync).then((data) => {
        resolve(JSON.parse(data || "{}"));
      }).catch(reject);
    } catch (error) {
      reject(error);
    }
  });
}
function https_get_data(url) {
  return new Promise((resolve, reject) => {
    const buffList = [];
    (() => {
      if (url.match("https://")) {
        return https;
      } else {
        return http;
      }
    })().get(url, (res) => {
      if (res.statusCode !== 200) {
        reject(new Error("get failure statusCode: ".concat(res.statusCode || 404)));
        return;
      }
      res.on("data", (data) => {
        buffList.push(data);
      });
      res.once("error", (err) => {
        reject(err);
      });
      res.on("end", () => {
        const buff = ref.concatBuff(buffList);
        resolve(buff);
        buffList.length = 0;
      });
    });
  });
}
function public_ip() {
  return new Promise(async (resolve, reject) => {
    let result_ok = false;
    let ip_server_list = [
      ["http://ipwho.is/", "ip"],
      ["http://httpbin.org/ip", "origin"],
      ["https://ipapi.co/json/", "ip"],
      ["https://api.ipify.org/?format=json", "ip"],
      ["https://freeipapi.com/api/json/", "ipAddress"],
      ["https://api.ip.sb/geoip", "ip"],
      ["https://api.myip.com/", "ip"],
      ["http://ip-api.com/json/?lang=zh-CN", "ip"]
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
          } catch (e) {
          }
        });
        if (result_ok) {
          return;
        }
      } catch (e) {
      }
    }
    reject();
  });
}
process.on("exit", function() {
});
// Annotate the CommonJS export names for ESM import in node:
0 && (module.exports = {
  HMN,
  Sleep,
  adapterIP,
  adapterIPAsync,
  asyncTaskQueue,
  freePort,
  freePortTCP,
  freePortUDP,
  getConnectNetList,
  getConnectNetListAsync,
  getDomainIPaddress,
  getDomainIPaddressAsync,
  getHostsPath,
  getNetParams,
  getNetParamsAsync,
  getProcessidFilePath,
  getProcessidFilePathAsync,
  getSystemProxyPac,
  getSystemProxyServer,
  getTCPv4PortProcessID,
  getTCPv4PortProcessIDAsync,
  getTCPv6PortProcessID,
  getTCPv6PortProcessIDAsync,
  getUDPv4PortProcessID,
  getUDPv4PortProcessIDAsync,
  getUDPv6PortProcessID,
  getUDPv6PortProcessIDAsync,
  hasPortTCP,
  hasPortUDP,
  ip,
  ipAsync,
  ipv4,
  ipv4Async,
  isAdmin,
  killProcess,
  native,
  public_ip,
  ref,
  sleep
});
