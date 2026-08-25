#ifndef HEALTHLOCK_TEF_API_H
#define HEALTHLOCK_TEF_API_H

#include <stdint.h>

#if defined(_WIN32)
#define TEF_EXPORT __declspec(dllexport)
#else
#define TEF_EXPORT __attribute__((visibility("default")))
#endif

typedef void *patch_handle_t;
typedef int64_t patch_hook_id_t;
typedef struct patch_method_signature_t patch_method_signature_t;

#define PATCH_NULL ((patch_handle_t)0)
#define PATCH_HOOK_INVALID_ID ((patch_hook_id_t)-1)

typedef enum mod_log_level_t {
    MOD_LOG_LEVEL_TRACE,
    MOD_LOG_LEVEL_DEBUG,
    MOD_LOG_LEVEL_INFO,
    MOD_LOG_LEVEL_WARNING,
    MOD_LOG_LEVEL_ERROR,
    MOD_LOG_LEVEL_CRITICAL,
    MOD_LOG_LEVEL_FATAL
} mod_log_level_t;

typedef void (*patch_prepost_callback_t)(patch_handle_t, void **, void *,
                                         const patch_method_signature_t *);

extern TEF_EXPORT void (*mod_logger_write)(mod_log_level_t, const char *, const char *, ...);
extern TEF_EXPORT patch_handle_t (*patchlib_type_get_type)(const char *, const char *);
extern TEF_EXPORT patch_handle_t (*patchlib_type_get_field)(patch_handle_t, const char *);
extern TEF_EXPORT patch_handle_t (*patchlib_type_get_method_by_param_count)(patch_handle_t, const char *, int);
extern TEF_EXPORT void (*patchlib_field_get_value)(patch_handle_t, patch_handle_t, void *);
extern TEF_EXPORT void (*patchlib_field_set_value)(patch_handle_t, patch_handle_t, void *);
extern TEF_EXPORT patch_hook_id_t (*patchlib_install_prepost_hook)(patch_handle_t, patch_prepost_callback_t, patch_prepost_callback_t);
extern TEF_EXPORT int (*patchlib_uninstall_hook)(patch_hook_id_t);
extern TEF_EXPORT void (*patchlib_free)(patch_handle_t);

#endif
