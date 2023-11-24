#include "./Mian.hpp"

using namespace hmc_napi_util;

// 判断是否是管理员权限
napi_value fn_isAdmin(napi_env env, napi_callback_info info)
{
    __HMC_debug("fn_isAdmin","","CALL"); 
    napi_value result =  create_value::Boolean(env, IsUserAnAdmin());
    __HMC_debug("fn_isAdmin", "", "end");
    return result;
}

napi_value fn_ip(napi_env env, napi_callback_info info)
{
    __HMC_debug("fn_isAdmin", "", "CALL");
    napi_value result = create_value::Boolean(env, IsUserAnAdmin());
    __HMC_debug("fn_isAdmin", "", "end");
    return result;
}

napi_value fn_ipv4(napi_env env, napi_callback_info info)
{
    __HMC_debug("fn_ipv4", "", "CALL");

    vector<hmc_v4_addr_item> v4_ipaddress_list;

    if (get_v4_ipaddress_list(v4_ipaddress_list))
    {
        __HMC_debug("fn_ipv4", "get_v4_ipaddress_list not data size " + to_string(v4_ipaddress_list.size()) , "end");
        // for (size_t i = 0; i < v4_ipaddress_list.size(); i++)
        // {
        //     auto data = v4_ipaddress_list[i];
        //     cout << "data->" << __hmc_to_string(data) << "\n";
        // }
        // cout << "data->" << __hmc_to_string(v4_ipaddress_list) << "\n";
        return create_value::String(env, __hmc_to_string(v4_ipaddress_list));
    }
    else{
        __HMC_debug("fn_ipv4", "get_v4_ipaddress_list not data ", "end");
        return create_value::String(env,"[]");
    }

    __HMC_debug("fn_ipv4", "", "end");
    return NULL;
}

static napi_value Init(napi_env env, napi_value exports)
{

    napi_property_descriptor BIND_NAPI_METHOD[] = {
        // 2023-11-23 add support
        DECLARE_NAPI_METHOD("isAdmin", fn_isAdmin),
        // 2023-11-23 add support
        DECLARE_NAPI_METHODRM("hmc_debug", fn_hmc_debug),
        // 2023-11-23 add support
        DECLARE_NAPI_METHODRM("hmc_debug_end", fn_hmc_debug_end),
        // 2023-11-24 add support
        DECLARE_NAPI_METHODRM("ipv4", fn_ipv4),
        // 2023-11-24 add support
        DECLARE_NAPI_METHODRM("ip", fn_ip),
    };

    napi_define_properties(env, exports, sizeof(BIND_NAPI_METHOD) / sizeof(BIND_NAPI_METHOD[0]), BIND_NAPI_METHOD);
    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init);
