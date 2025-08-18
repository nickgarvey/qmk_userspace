#include "ngarvey.h"

// --- Weak defaults for per-keymap hooks (safe no-ops) ---
__attribute__((weak)) bool          process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }
__attribute__((weak)) layer_state_t layer_state_set_keymap(layer_state_t state) { return state; }
__attribute__((weak)) void          matrix_scan_keymap(void) {}
__attribute__((weak)) void          keyboard_post_init_keymap(void) {}

// --- Userspace: runs for all your keyboards/keymaps named "ngarvey" ---
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case US_HELLO:
            if (record->event.pressed) {
                SEND_STRING("Hello from userspace!" SS_TAP(X_ENTER));
            }
            return false; // handled
        case US_NEXT_LAYER:
            if (record->event.pressed) {
                // Cycle base layers 0..7 (adjust to your needs)
                uint8_t next = get_highest_layer(default_layer_state) + 1;
                if (next >= 8) next = 0;
                default_layer_set((layer_state_t)(1U << next));
            }
            return false; // handled
    }
    // Chain to per-keymap logic (if any)
    return process_record_keymap(keycode, record);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    state = layer_state_set_keymap(state);
#ifdef RGBLIGHT_ENABLE
    // Simple visual layer cue (compiles out if no RGB)
    switch (get_highest_layer(state)) {
        case 0: rgblight_sethsv_noeeprom(HSV_WHITE);  break;
        case 1: rgblight_sethsv_noeeprom(HSV_CYAN);   break;
        case 2: rgblight_sethsv_noeeprom(HSV_PURPLE); break;
        default: rgblight_sethsv_noeeprom(HSV_RED);   break;
    }
#endif
    return state;
}

void matrix_scan_user(void) { matrix_scan_keymap(); }

void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_ENABLE
    rgblight_enable_noeeprom();
#endif
    keyboard_post_init_keymap();
}