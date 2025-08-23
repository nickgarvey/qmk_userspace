#include "ngarvey.h"

// --- Weak defaults for per-keymap hooks (safe no-ops) ---
__attribute__((weak)) bool          process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }
__attribute__((weak)) layer_state_t layer_state_set_keymap(layer_state_t state) { return state; }
__attribute__((weak)) void          matrix_scan_keymap(void) {}
__attribute__((weak)) void          keyboard_post_init_keymap(void) {}

// OS mode state (defaults to Linux)
static os_mode_t current_os_mode = OS_LINUX;

// OS mode functions
os_mode_t get_os_mode(void) {
    return current_os_mode;
}

void set_os_mode(os_mode_t mode) {
    current_os_mode = mode;
}

// Cross-platform copy function
void send_cross_platform_copy(void) {
    switch (current_os_mode) {
        case OS_MAC:
            // macOS uses Cmd+C
            tap_code16(LGUI(KC_C));
            break;
        case OS_LINUX:
        default:
            // Linux and Windows use Ctrl+C
            tap_code16(LCTL(KC_C));
            break;
    }
}

// Cross-platform paste function
void send_cross_platform_paste(void) {
    switch (current_os_mode) {
        case OS_MAC:
            // macOS uses Cmd+V
            tap_code16(LGUI(KC_V));
            break;
        case OS_LINUX:
        default:
            // Linux and Windows use Ctrl+V
            tap_code16(LCTL(KC_V));
            break;
    }
}

// Cross-platform cut function
void send_cross_platform_cut(void) {
    switch (current_os_mode) {
        case OS_MAC:
            // macOS uses Cmd+X
            tap_code16(LGUI(KC_X));
            break;
        case OS_LINUX:
        default:
            // Linux and Windows use Ctrl+X
            tap_code16(LCTL(KC_X));
            break;
    }
}

// --- Userspace: runs for all your keyboards/keymaps named "ngarvey" ---
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case US_COPY:
            if (record->event.pressed) {
                send_cross_platform_copy();
            }
            return false; // handled
        case US_PASTE:
            if (record->event.pressed) {
                send_cross_platform_paste();
            }
            return false; // handled
        case US_CUT:
            if (record->event.pressed) {
                send_cross_platform_cut();
            }
            return false; // handled
        case US_OS_TOGGLE:
            if (record->event.pressed) {
                // Toggle between Linux and Mac mode
                if (current_os_mode == OS_LINUX) {
                    set_os_mode(OS_MAC);
                    SEND_STRING("Mac mode");
                } else {
                    set_os_mode(OS_LINUX);
                    SEND_STRING("Linux mode");
                }
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
