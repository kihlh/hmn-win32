#include "./Mian.hpp"

using namespace hmc_napi_util;

// 判断是否是管理员权限
napi_value fn_isAdmin(napi_env env, napi_callback_info info)
{
    napi_value result = create_value::Boolean(env, IsUserAnAdmin());
    return result;
}

static napi_value fn_adapterIP (napi_env env, napi_callback_info info)
{
    vector<hmc_net_addr_item> _ipaddress_list;

    if (get_net_ipaddress_list(_ipaddress_list))
    {
        return create_value::String(env, sock_lib_to_json(_ipaddress_list));
    }
    else
    {
        return create_value::String(env, "[]");
    }

    return NULL;
}

static napi_value fn_getNetParams(napi_env env, napi_callback_info info)
{
    auto data = getNetParams().to_josn();
    auto ansi_to_utf16 = hmc_string_util::ansi_to_utf16(data);
    return create_value::String(env, ansi_to_utf16);
    
}

static napi_value fn_getConnectNetList(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argsLen = 4;
    napi_value args[4];

    $napi_get_cb_info(argsLen, args, "fn_get_connect_net");

    bool tcp,udp,tcp6,udp6 = true;

    switch (argsLen)
    {
    case 1:
        tcp = hmc_napi_util::get_value::boolean_bool(env, args[0]);
        break;
    case 2:
        tcp = hmc_napi_util::get_value::boolean_bool(env, args[0]);
        udp = hmc_napi_util::get_value::boolean_bool(env, args[1]);
        break;
    case 3:
        tcp = hmc_napi_util::get_value::boolean_bool(env, args[0]);
        udp = hmc_napi_util::get_value::boolean_bool(env, args[1]);
        tcp6 = hmc_napi_util::get_value::boolean_bool(env, args[2]);
        break;
    case 4:
        tcp = hmc_napi_util::get_value::boolean_bool(env, args[0]);
        udp = hmc_napi_util::get_value::boolean_bool(env, args[1]);
        tcp6 = hmc_napi_util::get_value::boolean_bool(env, args[2]);
        udp6 = hmc_napi_util::get_value::boolean_bool(env, args[3]);
        break;
    }

    std::vector<ConnectNet> ConnectNetList;

    enumConnectNet(ConnectNetList, tcp, udp, tcp6, udp6);

    auto ansi_to_utf16 = hmc_string_util::ansi_to_utf16(sock_lib_to_json(ConnectNetList));

    return create_value::String(env, ansi_to_utf16);
}


static napi_value fn_ipv4(napi_env env, napi_callback_info info)
{
    vector<hmc_v4_addr_item> v4_ipaddress_list;

    if (get_v4_ipaddress_list(v4_ipaddress_list))
    {
        return create_value::String(env, sock_lib_to_json(v4_ipaddress_list));
    }
    else
    {
        return create_value::String(env, "[]");
    }

    return NULL;
}

// 进程阻塞
static napi_value fn_sleep(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argsLen = 1;
    napi_value args[1];

    $napi_get_cb_info(argsLen, args, "fn_sleep");

    // 参数最少要求1个
    if (!hmc_napi_util::assert::argsSize(env, argsLen, 0, 1) && hmc_napi_util::assert::isNumber(env,args[0]))
    {
        napi_throw_type_error(env, NULL, string("parameter Is Incorrect fn_sleep(int)").c_str());
        return NULL;
    }

    int Set_time = hmc_napi_util::get_value::number_int(env, args[0]);
    Sleep(Set_time);

    return NULL;
}

static napi_value fn_getTCPv4PortProcessID(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argsLen = 1;
    napi_value args[1];

    $napi_get_cb_info(argsLen, args, "fn_get_port_tcp_v4_process_id");

    // 参数最少要求1个
    if (!hmc_napi_util::assert::argsSize(env, argsLen, 0, 1) && (hmc_napi_util::assert::isNumber(env, args[0]) || hmc_napi_util::assert::isBigint(env, args[0])))
    {
        napi_throw_type_error(env, NULL, string("parameter Is Incorrect fn_get_port_process_id ( int(Number) or in64(Bigint) )").c_str());
        return NULL;
    }

    unsigned short port = hmc_napi_util::get_value::number_int64(env, args[0]);

    int64_t result = GetTCPPortProcessID((unsigned short)port);

    return hmc_napi_util::create_value::Number(env, result);
}

static napi_value fn_getUDPv4PortProcessID(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argsLen = 1;
    napi_value args[1];

    $napi_get_cb_info(argsLen, args, "fn_get_port_tcp_v4_process_id");

    // 参数最少要求1个
    if (!hmc_napi_util::assert::argsSize(env, argsLen, 0, 1) && (hmc_napi_util::assert::isNumber(env, args[0]) || hmc_napi_util::assert::isBigint(env, args[0])))
    {
        napi_throw_type_error(env, NULL, string("parameter Is Incorrect fn_get_port_process_id ( int(Number) or in64(Bigint) )").c_str());
        return NULL;
    }

    unsigned short port = hmc_napi_util::get_value::number_int64(env, args[0]);

    int64_t result = GetUDPPortProcessID((unsigned short)port);

    return hmc_napi_util::create_value::Number(env, result);
}

static napi_value fn_getUDPv6PortProcessID(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argsLen = 1;
    napi_value args[1];

    $napi_get_cb_info(argsLen, args, "fn_get_port_tcp_v4_process_id");

    // 参数最少要求1个
    if (!hmc_napi_util::assert::argsSize(env, argsLen, 0, 1) && (hmc_napi_util::assert::isNumber(env, args[0]) || hmc_napi_util::assert::isBigint(env, args[0])))
    {
        napi_throw_type_error(env, NULL, string("parameter Is Incorrect fn_get_port_process_id ( int(Number) or in64(Bigint) )").c_str());
        return NULL;
    }

    unsigned short port = hmc_napi_util::get_value::number_int64(env, args[0]);

    vector<DWORD> result = GetUDP6PortProcessID((unsigned short)port);

    return hmc_napi_util::create_value::String(env, hmc_string_util::vec2json(result));
}

static napi_value fn_getTCPv6PortProcessID(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argsLen = 1;
    napi_value args[1];

    $napi_get_cb_info(argsLen, args, "fn_get_port_tcp_v4_process_id");

    // 参数最少要求1个
    if (!hmc_napi_util::assert::argsSize(env, argsLen, 0, 1) && (hmc_napi_util::assert::isNumber(env, args[0]) || hmc_napi_util::assert::isBigint(env, args[0])))
    {
        napi_throw_type_error(env, NULL, string("parameter Is Incorrect fn_get_port_process_id ( int(Number) or in64(Bigint) )").c_str());
        return NULL;
    }

    unsigned short port = hmc_napi_util::get_value::number_int64(env, args[0]);

    vector<DWORD> result = GetTCP6PortProcessID((unsigned short)port);

    return hmc_napi_util::create_value::String(env, hmc_string_util::vec2json(result));
}

static napi_value fn_getHostsPath(napi_env env, napi_callback_info info)
{
    return hmc_napi_util::create_value::String(env, getHostsPath());
}

static napi_value fn_getSystemProxyServer(napi_env env, napi_callback_info info)
{
    std::wstring proxy_server_url;
    
    if (get_system_proxy_server(proxy_server_url)){
        return hmc_napi_util::create_value::String(env, proxy_server_url);
    }

    return hmc_napi_util::create_value::Null(env);
}

static napi_value fn_getSystemProxyPac(napi_env env, napi_callback_info info)
{
    std::wstring proxy_server_url;

    if (get_system_proxy_pac(proxy_server_url))
    {
        return hmc_napi_util::create_value::String(env, proxy_server_url);
    }

    return hmc_napi_util::create_value::Null(env);
}

static napi_value fn_getDomainIPaddress(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argsLen = 1;
    napi_value args[1];

    $napi_get_cb_info(argsLen, args, "fn_getDomainIPaddress");

    // 参数最少要求1个
    if (!hmc_napi_util::assert::argsSize(env, argsLen, 0, 1) && hmc_napi_util::assert::isString(env, args[0]))
    {
        napi_throw_type_error(env, NULL, string("parameter Is Incorrect fn_getDomainIPaddress (string )").c_str());
        return NULL;
    }

    wstring Domain = hmc_napi_util::get_value::string_utf16(env, args[0]);

    std::vector<std::wstring> ip_list;

    if (getDomainIPaddress(Domain, ip_list))
    {
        return hmc_napi_util::create_value::String(env, hmc_string_util::vec2json(ip_list));
    }

    return hmc_napi_util::create_value::String(env, "[]");
}

// 结束进程
static napi_value fn_killProcess(napi_env env, napi_callback_info info)
{
    napi_status status;
    napi_value Kill_info;
    size_t argc = 1;
    napi_value args[1];

    $napi_get_cb_info(argc, args, "fn_kill_process");

    if (argc)
    {
        int Process_PID;
        status = napi_get_value_int32(env, args[0], &Process_PID);
        assert(status == napi_ok);
        DWORD ProcessID = (DWORD)Process_PID;
        bool Kill_info_bool = false;
        HANDLE killHandle = OpenProcess(PROCESS_TERMINATE | PROCESS_QUERY_INFORMATION | PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION | PROCESS_VM_WRITE, FALSE, ProcessID);
        if (killHandle == NULL)
        {
            Kill_info_bool = false;
        }
        else
        {
            bool Terminate_Kill_info_bool = TerminateProcess(killHandle, 0);
            Kill_info_bool = Terminate_Kill_info_bool;
        }
        status = napi_get_boolean(env, Kill_info_bool, &Kill_info);
        assert(status == napi_ok);
    }
    return Kill_info;
}

// 获取进程可执行文件位置
static napi_value fn_getProcessidFilePath(napi_env env, napi_callback_info info)
{
    napi_status status;
    napi_value FilePath;
    size_t argc = 1;
    napi_value args[1];

    $napi_get_cb_info(argc, args, "getProcessidFilePath");

    int Process_PID;
    status = napi_get_value_int32(env, args[0], &Process_PID);

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, Process_PID);
    wchar_t lpFilename[1024];
    if (hProcess == nullptr)
    {
        napi_get_null(env, &FilePath);
        return FilePath;
    }
    GetModuleFileNameExW(hProcess, NULL, (LPWSTR)lpFilename, 1024);

    FilePath = hmc_napi_util::create_value::String(env,wstring(lpFilename));

    CloseHandle(hProcess);

    return FilePath;
}


static napi_value Init(napi_env env, napi_value exports)
{

    napi_property_descriptor BIND_NAPI_METHOD[] = {
        // 2023-11-23 add support
        DECLARE_NAPI_METHOD("isAdmin", fn_isAdmin),
        // 2023-11-23 add support
        // DECLARE_NAPI_METHODRM("hmc_debug", fn_hmc_debug),
        // 2023-11-23 add support
        // DECLARE_NAPI_METHODRM("hmc_debug_end", fn_hmc_debug_end),
        // 2023-11-25 add support
        DECLARE_NAPI_METHOD("ipv4", fn_ipv4),
        // 2023-11-25 add support
        DECLARE_NAPI_METHOD("adapterIP", fn_adapterIP),
        // 2023-11-25 add support
        DECLARE_NAPI_METHOD("getNetParams", fn_getNetParams),
        // 2023-11-25 add support
        DECLARE_NAPI_METHOD("getConnectNetList", fn_getConnectNetList),
        // 2023-11-25 add support
        DECLARE_NAPI_METHOD("sleep", fn_sleep),
        // 2023-11-25 add support
        DECLARE_NAPI_METHOD("getTCPv6PortProcessID", fn_getTCPv6PortProcessID),
        // 2023-11-25 add support
        DECLARE_NAPI_METHOD("getUDPv6PortProcessID", fn_getUDPv6PortProcessID),
        // 2023-11-25 add support
        DECLARE_NAPI_METHOD("getUDPv4PortProcessID", fn_getUDPv4PortProcessID),
        // 2023-11-25 add support
        DECLARE_NAPI_METHOD("getTCPv4PortProcessID", fn_getTCPv4PortProcessID),
        // 2023-11-25 add support
        DECLARE_NAPI_METHOD("killProcess", fn_killProcess),
        // 2023-11-25 add support
        DECLARE_NAPI_METHOD("getProcessidFilePath", fn_getProcessidFilePath),
        // 2023-11-25 add support
        DECLARE_NAPI_METHOD("getHostsPath", fn_getHostsPath),
        // 2023-11-25 add support
        DECLARE_NAPI_METHOD("getSystemProxyServer", fn_getSystemProxyServer),
        // 2023-11-25 add support
        DECLARE_NAPI_METHOD("getSystemProxyPac", fn_getSystemProxyPac),
        // 2023-11-25 add support
        DECLARE_NAPI_METHOD("getDomainIPaddress", fn_getDomainIPaddress),

    };

    napi_define_properties(env, exports, sizeof(BIND_NAPI_METHOD) / sizeof(BIND_NAPI_METHOD[0]), BIND_NAPI_METHOD);
    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init);
