#include "./Mian.hpp"

// 判断是否是管理员权限
napi_value fn_isAdmin(napi_env env, napi_callback_info info)
{
    napi_value result = hmc_napi_create_value::Boolean(env, IsUserAnAdmin());
    return result;
}

static napi_value fn_adapterIP(napi_env env, napi_callback_info info)
{
    vector<hmc_net_addr_item> _ipaddress_list;

    if (get_net_ipaddress_list(_ipaddress_list))
    {
        return hmc_napi_create_value::String(env, sock_lib_to_json(_ipaddress_list));
    }
    else
    {
        return hmc_napi_create_value::String(env, "[]");
    }

    return NULL;
}

static napi_value fn_getNetParams(napi_env env, napi_callback_info info)
{
    auto data = getNetParams().to_josn();
    auto ansi_to_utf16 = hmc_string_util::ansi_to_utf16(data);
    return hmc_napi_create_value::String(env, ansi_to_utf16);
}

static napi_value fn_getConnectNetList(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argsLen = 4;
    napi_value args[4];

    $napi_get_cb_info(argsLen, args, "fn_get_connect_net");

    bool tcp, udp, tcp6, udp6 = true;

    switch (argsLen)
    {
    case 1:
        tcp = hmc_napi_get_value::boolean_bool(env, args[0]);
        break;
    case 2:
        tcp = hmc_napi_get_value::boolean_bool(env, args[0]);
        udp = hmc_napi_get_value::boolean_bool(env, args[1]);
        break;
    case 3:
        tcp = hmc_napi_get_value::boolean_bool(env, args[0]);
        udp = hmc_napi_get_value::boolean_bool(env, args[1]);
        tcp6 = hmc_napi_get_value::boolean_bool(env, args[2]);
        break;
    case 4:
        tcp = hmc_napi_get_value::boolean_bool(env, args[0]);
        udp = hmc_napi_get_value::boolean_bool(env, args[1]);
        tcp6 = hmc_napi_get_value::boolean_bool(env, args[2]);
        udp6 = hmc_napi_get_value::boolean_bool(env, args[3]);
        break;
    }

    std::vector<ConnectNet> ConnectNetList;

    enumConnectNet(ConnectNetList, tcp, udp, tcp6, udp6);

    auto ansi_to_utf16 = hmc_string_util::ansi_to_utf16(sock_lib_to_json(ConnectNetList));

    return hmc_napi_create_value::String(env, ansi_to_utf16);
}

static napi_value fn_ipv4(napi_env env, napi_callback_info info)
{
    vector<hmc_v4_addr_item> v4_ipaddress_list;

    if (get_v4_ipaddress_list(v4_ipaddress_list))
    {
        return hmc_napi_create_value::String(env, sock_lib_to_json(v4_ipaddress_list));
    }
    else
    {
        return hmc_napi_create_value::String(env, "[]");
    }

    return NULL;
}

static napi_value fn_sleep(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argsLen = 1;
    napi_value args[1];

    $napi_get_cb_info(argsLen, args, "fn_sleep");

    // 参数最少要求1个
    if (!hmc_napi_type::argsSize(env, argsLen, 0, 1) && hmc_napi_type::isNumber(env, args[0]))
    {
        napi_throw_type_error(env, NULL, string("parameter Is Incorrect fn_sleep(int)").c_str());
        return NULL;
    }

    int Set_time = hmc_napi_get_value::number_int(env, args[0]);
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
    if (!hmc_napi_type::argsSize(env, argsLen, 0, 1) && (hmc_napi_type::isNumber(env, args[0]) || hmc_napi_type::isBigint(env, args[0])))
    {
        napi_throw_type_error(env, NULL, string("parameter Is Incorrect fn_get_port_process_id ( int(Number) or in64(Bigint) )").c_str());
        return NULL;
    }

    unsigned short port = hmc_napi_get_value::number_int64(env, args[0]);

    int64_t result = GetTCPPortProcessID((unsigned short)port);

    return hmc_napi_create_value::Number(env, result);
}

static napi_value fn_getUDPv4PortProcessID(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argsLen = 1;
    napi_value args[1];

    $napi_get_cb_info(argsLen, args, "fn_get_port_tcp_v4_process_id");

    // 参数最少要求1个
    if (!hmc_napi_type::argsSize(env, argsLen, 0, 1) && (hmc_napi_type::isNumber(env, args[0]) || hmc_napi_type::isBigint(env, args[0])))
    {
        napi_throw_type_error(env, NULL, string("parameter Is Incorrect fn_get_port_process_id ( int(Number) or in64(Bigint) )").c_str());
        return NULL;
    }

    unsigned short port = hmc_napi_get_value::number_int64(env, args[0]);

    int64_t result = GetUDPPortProcessID((unsigned short)port);

    return hmc_napi_create_value::Number(env, result);
}

static napi_value fn_getUDPv6PortProcessID(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argsLen = 1;
    napi_value args[1];

    $napi_get_cb_info(argsLen, args, "fn_get_port_tcp_v4_process_id");

    // 参数最少要求1个
    if (!hmc_napi_type::argsSize(env, argsLen, 0, 1) && (hmc_napi_type::isNumber(env, args[0]) || hmc_napi_type::isBigint(env, args[0])))
    {
        napi_throw_type_error(env, NULL, string("parameter Is Incorrect fn_get_port_process_id ( int(Number) or in64(Bigint) )").c_str());
        return NULL;
    }

    unsigned short port = hmc_napi_get_value::number_int64(env, args[0]);

    vector<DWORD> result = GetUDP6PortProcessID((unsigned short)port);

    return hmc_napi_create_value::String(env, hmc_string_util::vec_to_array_json(result));
}

static napi_value fn_getTCPv6PortProcessID(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argsLen = 1;
    napi_value args[1];

    $napi_get_cb_info(argsLen, args, "fn_get_port_tcp_v4_process_id");

    // 参数最少要求1个
    if (!hmc_napi_type::argsSize(env, argsLen, 0, 1) && (hmc_napi_type::isNumber(env, args[0]) || hmc_napi_type::isBigint(env, args[0])))
    {
        napi_throw_type_error(env, NULL, string("parameter Is Incorrect fn_get_port_process_id ( int(Number) or in64(Bigint) )").c_str());
        return NULL;
    }

    unsigned short port = hmc_napi_get_value::number_int64(env, args[0]);

    vector<DWORD> result = GetTCP6PortProcessID((unsigned short)port);

    return hmc_napi_create_value::String(env, hmc_string_util::vec_to_array_json(result));
}

static napi_value fn_getHostsPath(napi_env env, napi_callback_info info)
{
    return hmc_napi_create_value::String(env, getHostsPath());
}

static napi_value fn_getSystemProxyServer(napi_env env, napi_callback_info info)
{
    std::wstring proxy_server_url;

    if (get_system_proxy_server(proxy_server_url))
    {
        return hmc_napi_create_value::String(env, proxy_server_url);
    }

    return hmc_napi_create_value::Null(env);
}

static napi_value fn_getSystemProxyPac(napi_env env, napi_callback_info info)
{
    std::wstring proxy_server_url;

    if (get_system_proxy_pac(proxy_server_url))
    {
        return hmc_napi_create_value::String(env, proxy_server_url);
    }

    return hmc_napi_create_value::Null(env);
}

static napi_value fn_getDomainIPaddress(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argsLen = 1;
    napi_value args[1];

    $napi_get_cb_info(argsLen, args, "fn_getDomainIPaddress");

    // 参数最少要求1个
    if (!hmc_napi_type::argsSize(env, argsLen, 0, 1) && hmc_napi_type::isString(env, args[0]))
    {
        napi_throw_type_error(env, NULL, string("parameter Is Incorrect fn_getDomainIPaddress (string )").c_str());
        return NULL;
    }

    wstring Domain = hmc_napi_get_value::string_utf16(env, args[0]);

    std::vector<std::wstring> ip_list;

    if (getDomainIPaddress(Domain, ip_list))
    {
        return hmc_napi_create_value::String(env, hmc_string_util::vec_to_array_json(ip_list));
    }

    return hmc_napi_create_value::String(env, "[]");
}

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

    FilePath = hmc_napi_create_value::String(env, wstring(lpFilename));

    CloseHandle(hProcess);

    return FilePath;
}

namespace PromiseConnectNetList
{

    typedef struct
    {
        // 工作环境
        napi_async_work work;
        // napi处理延迟的内联
        napi_deferred deferred;
        // 数据体的内存
        // vector<string> data;
    } PromiseData;

    typedef struct
    {
        bool tcp;
        bool udp;
        bool tcp6;
        bool udp6;
    } PromiseArgs;

    wstring _result_ConnectNetList = L"";
    PromiseArgs _PromiseArgs = {false, false, false, false};

    /**
     * @brief 处理数据更新 这里是异步的
     *
     * @param env
     * @param data
     */
    void asyncWorkFun(napi_env env, void *data)
    {
        PromiseData *addon_data = (PromiseData *)data;
        std::vector<ConnectNet> ConnectNetList;
        _result_ConnectNetList.clear();

        enumConnectNet(ConnectNetList, _PromiseArgs.tcp, _PromiseArgs.udp, _PromiseArgs.tcp6, _PromiseArgs.udp6);

        wstring ansi_to_utf16 = hmc_string_util::ansi_to_utf16(sock_lib_to_json(ConnectNetList));

        _result_ConnectNetList.append(ansi_to_utf16);
    }

    /**
     * @brief 运行结束的时候会执行此 这里是同步的
     *
     * @param env
     * @param status
     * @param data
     */
    void completeWork(napi_env env, napi_status status, void *data)
    {
        if (status != napi_ok)
        {
            return;
        }

        PromiseData *addon_data = (PromiseData *)data;

        napi_resolve_deferred(env, addon_data->deferred, hmc_napi_create_value::String(env, _result_ConnectNetList));

        // 清理与此运行关联的工作环境
        napi_delete_async_work(env, addon_data->work);

        // 将这两个值都设置为NULL，这样JavaScript可以启动新的线程运行。
        addon_data->work = NULL;
        addon_data->deferred = NULL;
        _result_ConnectNetList.clear();
    }

    /**
     * @brief 创建一个 promise对象
     *
     * @param env
     * @param info
     * @return napi_value
     */
    napi_value startWork(napi_env env, napi_callback_info info)
    {
        napi_value work_name, promise;
        PromiseData *addon_data;

        string work_message = string(__FUNCTION__).append("  work_message ->  ");

        // 获取插件的工作数据。
        napi_get_cb_info(env, info, NULL, NULL, NULL, (void **)(&addon_data));

        // 添加一个工作线程的 结构体

        if (addon_data->work != NULL)
        {
            work_message.append("error < Promise workspace has not been released. > ");
            napi_throw_error(env, "TASK_CONFLICT", work_message.c_str());
            return NULL;
        }

        // 创建一个字符串来描述这个异步操作。

        work_message.append("Node-API Deferred Promise from Async Work Item");
        napi_create_string_utf8(
            env, work_message.c_str(), work_message.length(), &work_name);

        napi_status status;
        size_t argsLen = 4;
        napi_value args[4];

        $napi_get_cb_info(argsLen, args, "fn_get_connect_net");

        bool tcp, udp, tcp6, udp6 = true;

        switch (argsLen)
        {
        case 1:
            tcp = hmc_napi_get_value::boolean_bool(env, args[0]);
            break;
        case 2:
            tcp = hmc_napi_get_value::boolean_bool(env, args[0]);
            udp = hmc_napi_get_value::boolean_bool(env, args[1]);
            break;
        case 3:
            tcp = hmc_napi_get_value::boolean_bool(env, args[0]);
            udp = hmc_napi_get_value::boolean_bool(env, args[1]);
            tcp6 = hmc_napi_get_value::boolean_bool(env, args[2]);
            break;
        case 4:
            tcp = hmc_napi_get_value::boolean_bool(env, args[0]);
            udp = hmc_napi_get_value::boolean_bool(env, args[1]);
            tcp6 = hmc_napi_get_value::boolean_bool(env, args[2]);
            udp6 = hmc_napi_get_value::boolean_bool(env, args[3]);
            break;
        }

        _PromiseArgs = PromiseArgs{tcp, udp, tcp6, udp6};

        // 创建一个延迟的promise对象，在完成时我们将解决它
        napi_create_promise(env, &(addon_data->deferred), &promise);

        // 创建一个异步工作项，传递插件数据，这将使
        // 工作线程访问上述创建的延迟的 promise对象
        napi_create_async_work(env,
                               NULL,
                               work_name,
                               asyncWorkFun,
                               completeWork,
                               addon_data,
                               &(addon_data->work));

        // 添加进node的异步队列
        napi_queue_async_work(env, addon_data->work);

        return promise;
    }

    /**
     * @brief 释放内存
     *
     * @param env
     * @param data
     * @param hint
     */
    void gcWork(napi_env env, void *data, void *hint)
    {
        PromiseData *addon_data = (PromiseData *)data;

        free(addon_data);
    }

    /**
     * @brief 导出这个异步函数
     *
     * @param env
     * @param exports
     * @param name
     */
    void exports(napi_env env, napi_value exports, string name)
    {
        PromiseData *addon_data = (PromiseData *)malloc(sizeof(*addon_data));

        addon_data->work = NULL;

        napi_value exported_function;

        napi_create_function(env,
                             name.c_str(),
                             NAPI_AUTO_LENGTH,
                             startWork,
                             addon_data,
                             &exported_function);

        napi_set_named_property(env, exports, name.c_str(), exported_function);

        // 回收
        napi_wrap(env, exports, addon_data, gcWork, NULL, NULL);
    }

}

namespace PromiseDomainIPaddress
{

    typedef struct
    {
        // 工作环境
        napi_async_work work;
        // napi处理延迟的内联
        napi_deferred deferred;
        // 数据体的内存
        //   vector<string> data;
    } PromiseData;

    std::wstring _PromiseDomainIPaddress_Domain = L"";
    std::vector<std::wstring> _PromiseDomainIPaddress_ip_list;

    /**
     * @brief 处理数据更新 这里是异步的
     *
     * @param env
     * @param data
     */
    void asyncWorkFun(napi_env env, void *data)
    {
        PromiseData *addon_data = (PromiseData *)data;
        _PromiseDomainIPaddress_ip_list.clear();

        getDomainIPaddress(_PromiseDomainIPaddress_Domain, _PromiseDomainIPaddress_ip_list);
    }

    /**
     * @brief 运行结束的时候会执行此 这里是同步的
     *
     * @param env
     * @param status
     * @param data
     */
    void completeWork(napi_env env, napi_status status, void *data)
    {
        if (status != napi_ok)
        {
            return;
        }

        PromiseData *addon_data = (PromiseData *)data;
        napi_value result = hmc_napi_create_value::String(env, hmc_string_util::vec_to_array_json(_PromiseDomainIPaddress_ip_list));
        napi_resolve_deferred(env, addon_data->deferred, result);

        // 清理与此运行关联的工作环境
        napi_delete_async_work(env, addon_data->work);

        // 将这两个值都设置为NULL，这样JavaScript可以启动新的线程运行。
        addon_data->work = NULL;
        addon_data->deferred = NULL;
    }

    /**
     * @brief 创建一个 promise对象
     *
     * @param env
     * @param info
     * @return napi_value
     */
    napi_value startWork(napi_env env, napi_callback_info info)
    {
        napi_value work_name, promise;
        PromiseData *addon_data;

        string work_message = string(__FUNCTION__).append("  work_message ->  ");

        // 获取插件的工作数据。
        napi_get_cb_info(env, info, NULL, NULL, NULL, (void **)(&addon_data));

        // 添加一个工作线程的 结构体

        if (addon_data->work != NULL)
        {
            work_message.append("error < Promise workspace has not been released. > ");
            napi_throw_error(env, "TASK_CONFLICT", work_message.c_str());
            return NULL;
        }

        // 创建一个字符串来描述这个异步操作。

        work_message.append("Node-API Deferred Promise from Async Work Item");
        napi_create_string_utf8(
            env, work_message.c_str(), work_message.length(), &work_name);

        napi_status status;
        size_t argsLen = 1;
        napi_value args[1];

        $napi_get_cb_info(argsLen, args, "fn_getDomainIPaddress");

        // 参数最少要求1个
        if (!hmc_napi_type::argsSize(env, argsLen, 0, 1) && hmc_napi_type::isString(env, args[0]))
        {
            napi_throw_type_error(env, NULL, string("parameter Is Incorrect fn_getDomainIPaddress (string )").c_str());
            return NULL;
        }
        _PromiseDomainIPaddress_Domain.clear();
        _PromiseDomainIPaddress_Domain.append(hmc_napi_get_value::string_utf16(env, args[0]));

        // 创建一个延迟的promise对象，在完成时我们将解决它
        napi_create_promise(env, &(addon_data->deferred), &promise);

        // 创建一个异步工作项，传递插件数据，这将使
        // 工作线程访问上述创建的延迟的 promise对象
        napi_create_async_work(env,
                               NULL,
                               work_name,
                               asyncWorkFun,
                               completeWork,
                               addon_data,
                               &(addon_data->work));

        // 添加进node的异步队列
        napi_queue_async_work(env, addon_data->work);

        return promise;
    }

    /**
     * @brief 释放内存
     *
     * @param env
     * @param data
     * @param hint
     */
    void gcWork(napi_env env, void *data, void *hint)
    {
        PromiseData *addon_data = (PromiseData *)data;
        _PromiseDomainIPaddress_Domain.clear();
        _PromiseDomainIPaddress_ip_list.clear();

        free(addon_data);
    }

    /**
     * @brief 导出这个异步函数
     *
     * @param env
     * @param exports
     * @param name
     */
    void exports(napi_env env, napi_value exports, string name)
    {
        PromiseData *addon_data = (PromiseData *)malloc(sizeof(*addon_data));

        addon_data->work = NULL;

        napi_value exported_function;

        napi_create_function(env,
                             name.c_str(),
                             NAPI_AUTO_LENGTH,
                             startWork,
                             addon_data,
                             &exported_function);

        napi_set_named_property(env, exports, name.c_str(), exported_function);

        // 回收
        napi_wrap(env, exports, addon_data, gcWork, NULL, NULL);
    }

} // namespace PromiseFun

namespace PromiseAdapterIP
{

    typedef struct
    {
        // 工作环境
        napi_async_work work;
        // napi处理延迟的内联
        napi_deferred deferred;
        // 数据体的内存
        //   vector<string> data;
    } PromiseData;

    wstring _PromiseAdapterIP_ipaddress_list;

    /**
     * @brief 处理数据更新 这里是异步的
     *
     * @param env
     * @param data
     */
    void asyncWorkFun(napi_env env, void *data)
    {
        PromiseData *addon_data = (PromiseData *)data;
        vector<hmc_net_addr_item> ipaddress_list;

        get_net_ipaddress_list(ipaddress_list);
        _PromiseAdapterIP_ipaddress_list.clear();
        _PromiseAdapterIP_ipaddress_list.append(sock_lib_to_json(ipaddress_list));
    }

    /**
     * @brief 运行结束的时候会执行此 这里是同步的
     *
     * @param env
     * @param status
     * @param data
     */
    void completeWork(napi_env env, napi_status status, void *data)
    {
        if (status != napi_ok)
        {
            return;
        }

        PromiseData *addon_data = (PromiseData *)data;
        napi_value result = hmc_napi_create_value::String(env, _PromiseAdapterIP_ipaddress_list);

        napi_resolve_deferred(env, addon_data->deferred, result);

        // 清理与此运行关联的工作环境
        napi_delete_async_work(env, addon_data->work);

        // 将这两个值都设置为NULL，这样JavaScript可以启动新的线程运行。
        addon_data->work = NULL;
        addon_data->deferred = NULL;
        _PromiseAdapterIP_ipaddress_list.clear();
    }

    /**
     * @brief 创建一个 promise对象
     *
     * @param env
     * @param info
     * @return napi_value
     */
    napi_value startWork(napi_env env, napi_callback_info info)
    {
        napi_value work_name, promise;
        PromiseData *addon_data;

        string work_message = string(__FUNCTION__).append("  work_message ->  ");

        // 获取插件的工作数据。
        napi_get_cb_info(env, info, NULL, NULL, NULL, (void **)(&addon_data));

        // 添加一个工作线程的 结构体

        if (addon_data->work != NULL)
        {
            work_message.append("error < Promise workspace has not been released. > ");
            napi_throw_error(env, "TASK_CONFLICT", work_message.c_str());
            return NULL;
        }

        // 创建一个字符串来描述这个异步操作。

        work_message.append("Node-API Deferred Promise from Async Work Item");
        napi_create_string_utf8(
            env, work_message.c_str(), work_message.length(), &work_name);

        // 创建一个延迟的promise对象，在完成时我们将解决它
        napi_create_promise(env, &(addon_data->deferred), &promise);

        // 创建一个异步工作项，传递插件数据，这将使
        // 工作线程访问上述创建的延迟的 promise对象
        napi_create_async_work(env,
                               NULL,
                               work_name,
                               asyncWorkFun,
                               completeWork,
                               addon_data,
                               &(addon_data->work));

        // 添加进node的异步队列
        napi_queue_async_work(env, addon_data->work);

        return promise;
    }

    /**
     * @brief 释放内存
     *
     * @param env
     * @param data
     * @param hint
     */
    void gcWork(napi_env env, void *data, void *hint)
    {
        PromiseData *addon_data = (PromiseData *)data;
        _PromiseAdapterIP_ipaddress_list.clear();
        free(addon_data);
    }

    /**
     * @brief 导出这个异步函数
     *
     * @param env
     * @param exports
     * @param name
     */
    void exports(napi_env env, napi_value exports, string name)
    {
        PromiseData *addon_data = (PromiseData *)malloc(sizeof(*addon_data));

        addon_data->work = NULL;

        napi_value exported_function;

        napi_create_function(env,
                             name.c_str(),
                             NAPI_AUTO_LENGTH,
                             startWork,
                             addon_data,
                             &exported_function);

        napi_set_named_property(env, exports, name.c_str(), exported_function);

        // 回收
        napi_wrap(env, exports, addon_data, gcWork, NULL, NULL);
    }

} // namespace PromiseFun

namespace PromiseGetProcessidFilePath
{

    typedef struct
    {
        // 工作环境
        napi_async_work work;
        // napi处理延迟的内联
        napi_deferred deferred;
        // 数据体的内存
        //   vector<string> data;
    } PromiseData;

    int __PromiseGetProcessidFilePath_PID;
    wstring __PromiseGetProcessidFilePath_data;

    /**
     * @brief 处理数据更新 这里是异步的
     *
     * @param env
     * @param data
     */
    void asyncWorkFun(napi_env env, void *data)
    {
        PromiseData *addon_data = (PromiseData *)data;

        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, (DWORD)__PromiseGetProcessidFilePath_PID);
        wchar_t lpFilename[1024];
        if (hProcess == nullptr)
        {
            return;
        }
        GetModuleFileNameExW(hProcess, NULL, (LPWSTR)lpFilename, 1024);

        CloseHandle(hProcess);

        __PromiseGetProcessidFilePath_data.clear();
        __PromiseGetProcessidFilePath_data.append(wstring(lpFilename));
    }

    /**
     * @brief 运行结束的时候会执行此 这里是同步的
     *
     * @param env
     * @param status
     * @param data
     */
    void completeWork(napi_env env, napi_status status, void *data)
    {
        if (status != napi_ok)
        {
            return;
        }

        PromiseData *addon_data = (PromiseData *)data;
        napi_value result = hmc_napi_create_value::String(env, __PromiseGetProcessidFilePath_data);

        napi_resolve_deferred(env, addon_data->deferred, result);

        // 清理与此运行关联的工作环境
        napi_delete_async_work(env, addon_data->work);

        // 将这两个值都设置为NULL，这样JavaScript可以启动新的线程运行。
        addon_data->work = NULL;
        addon_data->deferred = NULL;
        __PromiseGetProcessidFilePath_PID = NULL;
        __PromiseGetProcessidFilePath_data.clear();
    }

    /**
     * @brief 创建一个 promise对象
     *
     * @param env
     * @param info
     * @return napi_value
     */
    napi_value startWork(napi_env env, napi_callback_info info)
    {
        napi_value work_name, promise;
        PromiseData *addon_data;

        string work_message = string(__FUNCTION__).append("  work_message ->  ");

        // 获取插件的工作数据。
        napi_get_cb_info(env, info, NULL, NULL, NULL, (void **)(&addon_data));

        // 添加一个工作线程的 结构体

        if (addon_data->work != NULL)
        {
            work_message.append("error < Promise workspace has not been released. > ");
            napi_throw_error(env, "TASK_CONFLICT", work_message.c_str());
            return NULL;
        }

        __PromiseGetProcessidFilePath_PID = NULL;
        __PromiseGetProcessidFilePath_data.clear();

        // 创建一个字符串来描述这个异步操作。

        work_message.append("Node-API Deferred Promise from Async Work Item");
        napi_create_string_utf8(
            env, work_message.c_str(), work_message.length(), &work_name);

        napi_value FilePath;
        size_t argc = 1;
        napi_value args[1];

        $napi_get_cb_info(argc, args, "getProcessidFilePath");

        napi_get_value_int32(env, args[0], &__PromiseGetProcessidFilePath_PID);

        // 创建一个延迟的promise对象，在完成时我们将解决它
        napi_create_promise(env, &(addon_data->deferred), &promise);

        // 创建一个异步工作项，传递插件数据，这将使
        // 工作线程访问上述创建的延迟的 promise对象
        napi_create_async_work(env,
                               NULL,
                               work_name,
                               asyncWorkFun,
                               completeWork,
                               addon_data,
                               &(addon_data->work));

        // 添加进node的异步队列
        napi_queue_async_work(env, addon_data->work);

        return promise;
    }

    /**
     * @brief 释放内存
     *
     * @param env
     * @param data
     * @param hint
     */
    void gcWork(napi_env env, void *data, void *hint)
    {
        PromiseData *addon_data = (PromiseData *)data;
        __PromiseGetProcessidFilePath_PID = NULL;
        __PromiseGetProcessidFilePath_data.clear();
        free(addon_data);
    }

    /**
     * @brief 导出这个异步函数
     *
     * @param env
     * @param exports
     * @param name
     */
    void exports(napi_env env, napi_value exports, string name)
    {
        PromiseData *addon_data = (PromiseData *)malloc(sizeof(*addon_data));

        addon_data->work = NULL;

        napi_value exported_function;

        napi_create_function(env,
                             name.c_str(),
                             NAPI_AUTO_LENGTH,
                             startWork,
                             addon_data,
                             &exported_function);

        napi_set_named_property(env, exports, name.c_str(), exported_function);

        // 回收
        napi_wrap(env, exports, addon_data, gcWork, NULL, NULL);
    }

} // namespace PromiseFun

namespace PromiseGetPortProcessID
{

    typedef struct
    {
        // 工作环境
        napi_async_work work;
        // napi处理延迟的内联
        napi_deferred deferred;
        // 数据体的内存
        //   vector<string> data;
    } PromiseData;

    typedef enum
    {
        TCPv4 = 0,
        UDPv4 = 1,
        TCPv6 = 2,
        UDPv6 = 3
    } PortType;

    PortType __PromisePortType;
    DWORD __PromisePortByPid = 0;
    string __PromisePortByPidResultList;

    /**
     * @brief 处理数据更新 这里是异步的
     *
     * @param env
     * @param data
     */
    void asyncWorkFun(napi_env env, void *data)
    {
        vector<DWORD> result;
        PromiseData *addon_data = (PromiseData *)data;
        DWORD _pid = 0;

        switch (__PromisePortType)
        {
        case PortType::TCPv4:
            _pid = GetTCPPortProcessID((unsigned short)__PromisePortByPid);
            if (_pid != 0)
            {
                result.push_back(_pid);
            }
            break;
        case PortType::TCPv6:
            result = GetTCP6PortProcessID((unsigned short)__PromisePortByPid);
            break;
        case PortType::UDPv4:
            _pid = GetUDPPortProcessID((unsigned short)__PromisePortByPid);
            if (_pid != 0)
            {
                result.push_back(_pid);
            }
            break;
        case PortType::UDPv6:
            result = GetUDP6PortProcessID((unsigned short)__PromisePortByPid);
            break;
        }

        __PromisePortByPidResultList.clear();
        __PromisePortByPidResultList.append(hmc_string_util::vec_to_array_json(result));
    }

    /**
     * @brief 运行结束的时候会执行此 这里是同步的
     *
     * @param env
     * @param status
     * @param data
     */
    void completeWork(napi_env env, napi_status status, void *data)
    {
        if (status != napi_ok)
        {
            return;
        }

        PromiseData *addon_data = (PromiseData *)data;
        napi_value result = hmc_napi_create_value::String(env, __PromisePortByPidResultList);

        napi_resolve_deferred(env, addon_data->deferred, result);

        // 清理与此运行关联的工作环境
        napi_delete_async_work(env, addon_data->work);

        // 将这两个值都设置为NULL，这样JavaScript可以启动新的线程运行。
        addon_data->work = NULL;
        addon_data->deferred = NULL;

        __PromisePortType = PortType::TCPv4;
        __PromisePortByPid = 0;
        __PromisePortByPidResultList.clear();
    }

    /**
     * @brief 创建一个 promise对象
     *
     * @param env
     * @param info
     * @return napi_value
     */
    napi_value startWork(napi_env env, napi_callback_info info)
    {
        napi_value work_name, promise;
        PromiseData *addon_data;

        string work_message = string(__FUNCTION__).append("  work_message ->  ");

        // 获取插件的工作数据。
        napi_get_cb_info(env, info, NULL, NULL, NULL, (void **)(&addon_data));

        // 添加一个工作线程的 结构体

        if (addon_data->work != NULL)
        {
            work_message.append("error < Promise workspace has not been released. > ");
            napi_throw_error(env, "TASK_CONFLICT", work_message.c_str());
            return NULL;
        }

        __PromisePortType = PortType::TCPv4;
        __PromisePortByPid = 0;
        __PromisePortByPidResultList.clear();

        // 创建一个字符串来描述这个异步操作。

        work_message.append("Node-API Deferred Promise from Async Work Item");
        napi_create_string_utf8(
            env, work_message.c_str(), work_message.length(), &work_name);

        napi_value FilePath;
        size_t argc = 2;
        napi_value args[2];

        $napi_get_cb_info(argc, args, "getProcessidFilePath");

        int PromisePortType = 0;
        napi_get_value_int32(env, args[0], &PromisePortType);

        __PromisePortType = (PortType)PromisePortType;

        int PromisePortByPid = 0;
        napi_get_value_int32(env, args[1], &PromisePortByPid);

        __PromisePortByPid = (DWORD)PromisePortByPid;

        // 创建一个延迟的promise对象，在完成时我们将解决它
        napi_create_promise(env, &(addon_data->deferred), &promise);

        // 创建一个异步工作项，传递插件数据，这将使
        // 工作线程访问上述创建的延迟的 promise对象
        napi_create_async_work(env,
                               NULL,
                               work_name,
                               asyncWorkFun,
                               completeWork,
                               addon_data,
                               &(addon_data->work));

        // 添加进node的异步队列
        napi_queue_async_work(env, addon_data->work);

        return promise;
    }

    /**
     * @brief 释放内存
     *
     * @param env
     * @param data
     * @param hint
     */
    void gcWork(napi_env env, void *data, void *hint)
    {
        PromiseData *addon_data = (PromiseData *)data;
        __PromisePortType = PortType::TCPv4;
        __PromisePortByPid = 0;
        __PromisePortByPidResultList.clear();
        free(addon_data);
    }

    /**
     * @brief 导出这个异步函数
     *
     * @param env
     * @param exports
     * @param name
     */
    void exports(napi_env env, napi_value exports, string name)
    {
        PromiseData *addon_data = (PromiseData *)malloc(sizeof(*addon_data));

        addon_data->work = NULL;

        napi_value exported_function;

        napi_create_function(env,
                             name.c_str(),
                             NAPI_AUTO_LENGTH,
                             startWork,
                             addon_data,
                             &exported_function);

        napi_set_named_property(env, exports, name.c_str(), exported_function);

        // 回收
        napi_wrap(env, exports, addon_data, gcWork, NULL, NULL);
    }

} // namespace PromiseFun

namespace PromiseAdapterIPV4
{

    typedef struct
    {
        // 工作环境
        napi_async_work work;
        // napi处理延迟的内联
        napi_deferred deferred;
        // 数据体的内存
        //   vector<string> data;
    } PromiseData;

    string _PromiseAdapterIP_ipaddress_list;

    /**
     * @brief 处理数据更新 这里是异步的
     *
     * @param env
     * @param data
     */
    void asyncWorkFun(napi_env env, void *data)
    {
        PromiseData *addon_data = (PromiseData *)data;
        vector<hmc_v4_addr_item> ipaddress_list;

        get_v4_ipaddress_list(ipaddress_list);
        _PromiseAdapterIP_ipaddress_list.clear();
        _PromiseAdapterIP_ipaddress_list.append(sock_lib_to_json(ipaddress_list));
    }

    /**
     * @brief 运行结束的时候会执行此 这里是同步的
     *
     * @param env
     * @param status
     * @param data
     */
    void completeWork(napi_env env, napi_status status, void *data)
    {
        if (status != napi_ok)
        {
            return;
        }

        PromiseData *addon_data = (PromiseData *)data;
        napi_value result = hmc_napi_create_value::String(env, _PromiseAdapterIP_ipaddress_list);

        napi_resolve_deferred(env, addon_data->deferred, result);

        // 清理与此运行关联的工作环境
        napi_delete_async_work(env, addon_data->work);

        // 将这两个值都设置为NULL，这样JavaScript可以启动新的线程运行。
        addon_data->work = NULL;
        addon_data->deferred = NULL;
        _PromiseAdapterIP_ipaddress_list.clear();
    }

    /**
     * @brief 创建一个 promise对象
     *
     * @param env
     * @param info
     * @return napi_value
     */
    napi_value startWork(napi_env env, napi_callback_info info)
    {
        napi_value work_name, promise;
        PromiseData *addon_data;

        string work_message = string(__FUNCTION__).append("  work_message ->  ");

        // 获取插件的工作数据。
        napi_get_cb_info(env, info, NULL, NULL, NULL, (void **)(&addon_data));

        // 添加一个工作线程的 结构体

        if (addon_data->work != NULL)
        {
            work_message.append("error < Promise workspace has not been released. > ");
            napi_throw_error(env, "TASK_CONFLICT", work_message.c_str());
            return NULL;
        }

        // 创建一个字符串来描述这个异步操作。

        work_message.append("Node-API Deferred Promise from Async Work Item");
        napi_create_string_utf8(
            env, work_message.c_str(), work_message.length(), &work_name);

        // 创建一个延迟的promise对象，在完成时我们将解决它
        napi_create_promise(env, &(addon_data->deferred), &promise);

        // 创建一个异步工作项，传递插件数据，这将使
        // 工作线程访问上述创建的延迟的 promise对象
        napi_create_async_work(env,
                               NULL,
                               work_name,
                               asyncWorkFun,
                               completeWork,
                               addon_data,
                               &(addon_data->work));

        // 添加进node的异步队列
        napi_queue_async_work(env, addon_data->work);

        return promise;
    }

    /**
     * @brief 释放内存
     *
     * @param env
     * @param data
     * @param hint
     */
    void gcWork(napi_env env, void *data, void *hint)
    {
        PromiseData *addon_data = (PromiseData *)data;
        _PromiseAdapterIP_ipaddress_list.clear();
        free(addon_data);
    }

    /**
     * @brief 导出这个异步函数
     *
     * @param env
     * @param exports
     * @param name
     */
    void exports(napi_env env, napi_value exports, string name)
    {
        PromiseData *addon_data = (PromiseData *)malloc(sizeof(*addon_data));

        addon_data->work = NULL;

        napi_value exported_function;

        napi_create_function(env,
                             name.c_str(),
                             NAPI_AUTO_LENGTH,
                             startWork,
                             addon_data,
                             &exported_function);

        napi_set_named_property(env, exports, name.c_str(), exported_function);

        // 回收
        napi_wrap(env, exports, addon_data, gcWork, NULL, NULL);
    }

} // namespace PromiseFun

namespace PromiseNetParams
{

    typedef struct
    {
        // 工作环境
        napi_async_work work;
        // napi处理延迟的内联
        napi_deferred deferred;
        // 数据体的内存 必须是固定大小的值 不能动态调整内存
        // vector<string> data;
    } PromiseData;

    wstring __NetParams_data = L"";
    /**
     * @brief 处理数据更新 这里是异步的
     *
     * @param env
     * @param data
     */
    void asyncWorkFun(napi_env env, void *data)
    {
        PromiseData *addon_data = (PromiseData *)data;
        string data_to_josn = getNetParams().to_josn();
        wstring ansi_to_utf16 = hmc_string_util::ansi_to_utf16(data_to_josn);
        __NetParams_data.append(ansi_to_utf16);
    }

    /**
     * @brief 运行结束的时候会执行此 这里是同步的
     *
     * @param env
     * @param status
     * @param data
     */
    void completeWork(napi_env env, napi_status status, void *data)
    {
        if (status != napi_ok)
        {
            return;
        }

        PromiseData *addon_data = (PromiseData *)data;
        napi_value result = hmc_napi_create_value::String(env,__NetParams_data);

        napi_resolve_deferred(env, addon_data->deferred, result);

        __NetParams_data.clear();
        // 清理与此运行关联的工作环境
        napi_delete_async_work(env, addon_data->work);

        // 将这两个值都设置为NULL，这样JavaScript可以启动新的线程运行。
        addon_data->work = NULL;
        addon_data->deferred = NULL;
    }

    /**
     * @brief 创建一个 promise对象
     *
     * @param env
     * @param info
     * @return napi_value
     */
    napi_value startWork(napi_env env, napi_callback_info info)
    {
        napi_value work_name, promise;
        PromiseData *addon_data;

        string work_message = string(__FUNCTION__).append("  work_message ->  ");

        // 获取插件的工作数据。
        napi_get_cb_info(env, info, NULL, NULL, NULL, (void **)(&addon_data));

        // 添加一个工作线程的 结构体

        if (addon_data->work != NULL)
        {
            work_message.append("error < Promise workspace has not been released. > ");
            napi_throw_error(env, "TASK_CONFLICT", work_message.c_str());
            return NULL;
        }

        // 创建一个字符串来描述这个异步操作。

        work_message.append("Node-API Deferred Promise from Async Work Item");
        napi_create_string_utf8(
            env, work_message.c_str(), work_message.length(), &work_name);

        // 创建一个延迟的promise对象，在完成时我们将解决它
        napi_create_promise(env, &(addon_data->deferred), &promise);

        // 创建一个异步工作项，传递插件数据，这将使
        // 工作线程访问上述创建的延迟的 promise对象
        napi_create_async_work(env,
                               NULL,
                               work_name,
                               asyncWorkFun,
                               completeWork,
                               addon_data,
                               &(addon_data->work));

        // 添加进node的异步队列
        napi_queue_async_work(env, addon_data->work);

        return promise;
    }

    /**
     * @brief 释放内存 请注意这里是模块卸载时候才执行
     *
     * @param env
     * @param data
     * @param hint
     */
    void gcWork(napi_env env, void *data, void *hint)
    {
        PromiseData *addon_data = (PromiseData *)data;

        free(addon_data);
    }

    /**
     * @brief 导出这个异步函数
     *
     * @param env
     * @param exports
     * @param name
     */
    void exports(napi_env env, napi_value exports, string name)
    {
        PromiseData *addon_data = (PromiseData *)malloc(sizeof(*addon_data));

        addon_data->work = NULL;

        napi_value exported_function;

        napi_create_function(env,
                             name.c_str(),
                             NAPI_AUTO_LENGTH,
                             startWork,
                             addon_data,
                             &exported_function);

        napi_set_named_property(env, exports, name.c_str(), exported_function);

        // 回收
        napi_wrap(env, exports, addon_data, gcWork, NULL, NULL);
    }

} // namespace PromiseFun

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

    PromiseConnectNetList::exports(env, exports, "getConnectNetListAsync");
    PromiseGetProcessidFilePath::exports(env, exports, "getProcessidFilePathAsync");
    PromiseAdapterIP::exports(env, exports, "adapterIPAsync");
    PromiseDomainIPaddress::exports(env, exports, "getDomainIPaddressAsync");
    PromiseGetPortProcessID::exports(env, exports, "getPortProcessIDAsync");
    PromiseAdapterIPV4::exports(env, exports, "ipv4Async");
    PromiseNetParams::exports(env, exports, "getNetParamsAsync");
    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init);
