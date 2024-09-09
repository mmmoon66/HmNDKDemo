#include "napi/native_api.h"
#include <unordered_map>

static napi_value Add(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value args[2] = {nullptr};

    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    napi_valuetype valuetype0;
    napi_typeof(env, args[0], &valuetype0);

    napi_valuetype valuetype1;
    napi_typeof(env, args[1], &valuetype1);

    double value0;
    napi_get_value_double(env, args[0], &value0);

    double value1;
    napi_get_value_double(env, args[1], &value1);

    napi_value sum;
    napi_create_double(env, value0 + value1, &sum);

    return sum;
}

static napi_value Subtract(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value args[2] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    napi_valuetype valuetype0;
    napi_typeof(env, args[0], &valuetype0);

    napi_valuetype valuetype1;
    napi_typeof(env, args[1], &valuetype1);

    double value0;
    napi_get_value_double(env, args[0], &value0);

    double value1;
    napi_get_value_double(env, args[1], &value1);

    napi_value ret;
    napi_create_double(env, value0 - value1, &ret);

    return ret;
}

static napi_value Multiply(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value args[2] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    napi_valuetype valuetype0;
    napi_typeof(env, args[0], &valuetype0);

    napi_valuetype valuetype1;
    napi_typeof(env, args[1], &valuetype1);

    double value0;
    napi_get_value_double(env, args[0], &value0);

    double value1;
    napi_get_value_double(env, args[1], &value1);

    napi_value ret;
    napi_create_double(env, value0 * value1, &ret);
    return ret;
}

static napi_value Divide(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value args[2] = {nullptr};

    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    napi_valuetype valuetype0;
    napi_typeof(env, args[0], &valuetype0);

    napi_valuetype valuetype1;
    napi_typeof(env, args[1], &valuetype1);

    double value0;
    napi_get_value_double(env, args[0], &value0);

    double value1;
    napi_get_value_double(env, args[1], &value1);

    napi_value ret;
    napi_create_double(env, value0 / value1, &ret);
    return ret;
}

// double FactorialRecursive(double n) {
//     if (n <= 1) {
//         return 1;
//     }
//     return n * FactorialRecursive(n - 1);
// }

static napi_value Factorial(napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value args[1] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    napi_valuetype valuetype;
    napi_typeof(env, args[0], &valuetype);

    double value;
    napi_get_value_double(env, args[0], &value);

    if (value < 0 || value != static_cast<int>(value)) {
        napi_throw_error(env, nullptr, "Argument must be non-negative integer");
        return nullptr;
    }

    double fact = 1;
    while (value > 1) {
        fact *= value;
        value -= 1;
    }
    napi_value ret;
    napi_create_double(env, fact, &ret);
    return ret;
}

static napi_value TwoSum(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value args[2] = {nullptr, nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    if (argc != 2) {
        napi_throw_error(env, nullptr, "Expected two arguments");
        return nullptr;
    }

    double target;
    napi_get_value_double(env, args[1], &target);

    napi_valuetype valuetype;
    napi_typeof(env, args[0], &valuetype);

    if (valuetype != napi_object) {
        napi_throw_error(env, nullptr, "First argument must be an array");
        return nullptr;
    }

    uint32_t length;
    napi_get_array_length(env, args[0], &length);

    std::unordered_map<double, uint32_t> map;
    napi_value ret_arr;
    napi_create_array(env, &ret_arr);

    for (uint32_t i = 0; i < length; i++) {
        napi_value element;
        napi_get_element(env, args[0], i, &element);

        double value;
        napi_get_value_double(env, element, &value);

        double complement = target - value;
        if (map.find(complement) != map.end()) {
            napi_value index1, index2;
            napi_create_uint32(env, map[complement], &index1);
            napi_create_uint32(env, i, &index2);

            napi_set_element(env, ret_arr, 0, index1);
            napi_set_element(env, ret_arr, 1, index2);
            return ret_arr;
        }
        map[value] = i;
    }
    return ret_arr;
}

EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports) {
    napi_property_descriptor desc[] = {
        {"add", nullptr, Add, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"subtract", nullptr, Subtract, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"multiply", nullptr, Multiply, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"divide", nullptr, Divide, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"factorial", nullptr, Factorial, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"twoSum", nullptr, TwoSum, nullptr, nullptr, nullptr, napi_default, nullptr},
    };
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    return exports;
}
EXTERN_C_END

static napi_module demoModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "entry",
    .nm_priv = ((void *)0),
    .reserved = {0},
};

extern "C" __attribute__((constructor)) void RegisterEntryModule(void) { napi_module_register(&demoModule); }
