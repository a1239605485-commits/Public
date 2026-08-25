#ifndef HEALTHLOCK_MOD_CORE_H
#define HEALTHLOCK_MOD_CORE_H

#if defined(_WIN32)
#define MOD_API_EXPORT __declspec(dllexport)
#define MOD_CALL_CONV __cdecl
#else
#define MOD_API_EXPORT __attribute__((visibility("default")))
#define MOD_CALL_CONV
#endif

typedef struct kernel_mod_ops_t kernel_mod_ops_t;
typedef struct kernel_mod_handle_t kernel_mod_handle_t;
typedef struct kernel_mod_info_t kernel_mod_info_t;

struct kernel_mod_handle_t {
    char *private_dir;
    kernel_mod_ops_t *ops;
    void *lib_handle;
};

struct kernel_mod_ops_t {
    void (*init_mod)(kernel_mod_handle_t *handle);
    void (*cleanup_mod)(kernel_mod_handle_t *handle);
    kernel_mod_info_t *(*get_info)(void);
};

struct kernel_mod_info_t {
    const char *pkg_id;
    int version_code;
    int api_version;
    const char *version;
};

MOD_API_EXPORT kernel_mod_ops_t *MOD_CALL_CONV create_kernel_mod(void);
#endif
