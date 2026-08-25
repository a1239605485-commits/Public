#include "mod_core.h"
#include "tef_api.h"

static patch_handle_t g_stat_life = PATCH_NULL;
static patch_handle_t g_stat_life_max2 = PATCH_NULL;
static patch_hook_id_t g_update_hook = PATCH_HOOK_INVALID_ID;

static void update_postfix(patch_handle_t player, void **args, void *result,
                           const patch_method_signature_t *signature) {
    (void)args;
    (void)result;
    (void)signature;
    if (!player || !g_stat_life || !g_stat_life_max2) return;

    int current_life = 0;
    int maximum_life = 0;
    patchlib_field_get_value(g_stat_life, player, &current_life);
    patchlib_field_get_value(g_stat_life_max2, player, &maximum_life);

    if (maximum_life > 0 && current_life > 0 && current_life != maximum_life) {
        patchlib_field_set_value(g_stat_life, player, &maximum_life);
    }
}

static void init_mod(kernel_mod_handle_t *handle) {
    (void)handle;
    if (!patchlib_type_get_type || !patchlib_type_get_field ||
        !patchlib_type_get_method_by_param_count || !patchlib_install_prepost_hook ||
        !patchlib_field_get_value || !patchlib_field_set_value) return;

    patch_handle_t player_type = patchlib_type_get_type("Terraria", "Player");
    if (!player_type) return;

    g_stat_life = patchlib_type_get_field(player_type, "statLife");
    g_stat_life_max2 = patchlib_type_get_field(player_type, "statLifeMax2");
    patch_handle_t update = patchlib_type_get_method_by_param_count(player_type, "Update", 1);

    if (g_stat_life && g_stat_life_max2 && update) {
        g_update_hook = patchlib_install_prepost_hook(update, 0, update_postfix);
    }

    if (update && patchlib_free) patchlib_free(update);
    if (patchlib_free) patchlib_free(player_type);
    if (mod_logger_write) {
        mod_logger_write(g_update_hook == PATCH_HOOK_INVALID_ID ? MOD_LOG_LEVEL_ERROR : MOD_LOG_LEVEL_INFO,
                         "HealthLock", g_update_hook == PATCH_HOOK_INVALID_ID ?
                         "Player.Update hook failed" : "Player.Update hook installed");
    }
}

static void cleanup_mod(kernel_mod_handle_t *handle) {
    (void)handle;
    if (g_update_hook != PATCH_HOOK_INVALID_ID && patchlib_uninstall_hook) {
        patchlib_uninstall_hook(g_update_hook);
        g_update_hook = PATCH_HOOK_INVALID_ID;
    }
    if (patchlib_free) {
        if (g_stat_life) patchlib_free(g_stat_life);
        if (g_stat_life_max2) patchlib_free(g_stat_life_max2);
    }
    g_stat_life = PATCH_NULL;
    g_stat_life_max2 = PATCH_NULL;
}

static kernel_mod_info_t g_info = {
    .pkg_id = "lzup.test.healthlock",
    .version_code = 2026082501,
    .api_version = 1,
    .version = "1.0.0-test"
};

static kernel_mod_info_t *get_info(void) { return &g_info; }

static kernel_mod_ops_t g_ops = {
    .init_mod = init_mod,
    .cleanup_mod = cleanup_mod,
    .get_info = get_info
};

MOD_API_EXPORT kernel_mod_ops_t *MOD_CALL_CONV create_kernel_mod(void) {
    return &g_ops;
}
