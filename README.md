# **HMN-win32: Package for Windows Net API **

![系统环境](https://cos.kiic.top/assets/used/202204112301972.svg)      ![系统环境](https://cos.kiic.top/assets/used/202204112301969.svg)      ![系统环境](https://img.shields.io/badge/Node6.14.2+-Node-97c40f.svg?longCache=true)       ![系统环境](https://img.shields.io/badge/Node8.0+-electron-97c40f.svg?longCache=true)    

## help

`ddffsd Parts of this document were translated by machine (Gpt3.5)`

`Backwards compatible to node6.14.2 but the precompiled version is only supported to node8 and above (because node6 has no asynchronous syntactic sugar), for node6 please compile to node6.14.2 with esbuld yourself`

HMN 是 [HMC-WIN32](https://github.com/kihlh/hmc-win32)  的子分支，与HMC不同的是 HMN 仅处理网络相关的api 

####  [编程帮助(中文)](https://kihlh.gitbook.io/hmc/)               [help (English) ](https://kihlh.gitbook.io/hmc_en/)      [CPP (source)](https://github.com/kihlh/hmc-win32/tree/master/source/CPP_Reconfig) 

## installation

```
npm i hmn-win32
```

### How to call

```javascript
let HMN = require("hmn-win32");
console.log("net:ping=>",HMN.ping(8.8.8.8))
//ping 8.8.8.8 => [25n,200n,8n] (ns)

console.log("net:ip=>",HMN.ip())
//ip=> [192.168.0.5,196.128.8.255,8.8.8.8]

console.log("net:public_ip=>",HMN.public_ip())
//public_ip=> 8.8.8.8

```

###  In TypeScript using the

```typescript
import  HMC = require("hmn-win32");
```

# 功能概览

### API中间层

- **ref**  转换
  - **bool**  将布尔内容转为安全的 bool 类型布尔
  - **string** 将文本/伪文本内容转为安全的文本
  - **int** 将数字/伪数字内容转为安全的int数字
  - **HKEY** 所有注册表的 HKEY 对象
- **Sleep** 异步的阻塞
- **native** 直接连接HMN.node的原生方法 (不建议使用)

### API(正在构建中。。。)

- **ipv4** 获取本机局域网的ip(v4)

- **ip**获取本机局域网的ip(适配器,v4,v6)

- **adapterIP **获取本机局域网的ip(适配器,v4,v6)

- **public_ip** 获取本机公网ip

- **getNetParams** 获取主机网络信息

- **freePort** 获取一个tcp空闲端口 (服务)

- **freePortTCP** 获取一个空闲的tcp端口

- **freePortUDP** 获取一个空闲的udp端口

- **hasPortUDP** 判断此udp端口是否空闲

- **hasPortTCP**判断此TCP端口是否空闲

- **getSystemProxyServer** 获取系统代理链接（仅在启用系统代理时）

- **getSystemProxyPac**  获取系统代理pac脚本链接

- **getDomainIPaddress**  从默认dns(联网)解析域名主机ip

- **getHostsPath** 获取hosts文件的路径

- **getTCPv6PortProcessID** 获取此端口被哪个进程占用了

- **getUDPv6PortProcessID** 获取此端口被哪个进程占用了

- **getUDPv4PortProcessID** 获取此端口被哪个进程占用了

- **getTCPv4PortProcessID** 获取此端口被哪个进程占用了

- **getConnectNetList**  枚举此电脑中的 端口 ipv4 and ipv6 的 TCP，UDP 端口信息

- **killProcess** 结束该pid进程（低权利 如果需要高权限的kill请使用hmc-win32）

- **sleep** 同步阻塞(进程)

- **Sleep** 异步阻塞(进程)

- **PortWatchdog** 检测端口变化如果关闭或者启用时发起回调

- **getProcessidFilePath** 获取进程可执行文件位置

- **isAdmin** 判断当前软件是否拥有管理员权限

-   **ping** 
- 对运行速度提升影响不大，已移除
  
- ping使用  https://www.npmjs.com/package/ping
  
- 服务器有效性判断用 https://github.com/qawemlilo/ping-monitor

### 重新构建

HMC所有API采用 winapi + nodeapi实现，因此无需重新编译（允许运行在node8以上环境 node6.14.2 需要自行使用esbuld编译），如果您需要对源代码进行修改请使用``node-gyp rebuild`` 进行编译，这需要有一定的C/C++基础，编译工具使用node-gyp即可，需要使用到的工具如下：

- node-gyp
- Visual Studio 2019（or other versions)


### 风险告知

- 每个功能模块都会经过千次以上循环调用 无出现进程崩溃

- API已经通过js严格转码 只有调用native才需要 ~~但是由于C++和C语言都是严格类型，必须严格使用typeScript严格传递类型~~
- 虽然经过疲劳测试，但是还是有可能会有无法预期的进程奔溃，所以建议在子进程下运行
- C++ 的野指针和空指针和内存溢出 引用错误 类型错误 等 对于进程都是致命的，所以在编写新功能时候需要不断地进行模拟疲劳测试





