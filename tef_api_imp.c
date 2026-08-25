#include "tef_api.h"

TEF_EXPORT void (*mod_logger_write)(mod_log_level_t, const char *, const char *, ...) = 0;
TEF_EXPORT patch_handle_t (*patchlib_type_get_type)(const char *, const char *) = 0;
TEF_EXPORT patch_handle_t (*patchlib_type_get_field)(patch_handle_t, const char *) = 0;
TEF_EXPORT patch_handle_t (*patchlib_type_get_method_by_param_count)(patch_handle_t, const char *, int) = 0;
TEF_EXPORT void (*patchlib_field_get_value)(patch_handle_t, patch_handle_t, void *) = 0;
TEF_EXPORT void (*patchlib_field_set_value)(patch_handle_t, patch_handle_t, void *) = 0;
TEF_EXPORT patch_hook_id_t (*patchlib_install_prepost_hook)(patch_handle_t, patch_prepost_callback_t, patch_prepost_callback_t) = 0;
TEF_EXPORT int (*patchlib_uninstall_hook)(patch_hook_id_t) = 0;
TEF_EXPORT void (*patchlib_free)(patch_handle_t) = 0;
