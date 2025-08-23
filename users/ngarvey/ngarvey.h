#pragma once
#include "quantum.h"

// OS modes for cross-platform compatibility
typedef enum {
    OS_LINUX = 0,
    OS_MAC = 1
} os_mode_t;

// Custom keycodes shared across all your keyboards
enum userspace_custom_keycodes {
    US_SAFE_RANGE = SAFE_RANGE,
    US_COPY,        // cross-platform copy (adapts based on OS mode)
    US_PASTE,       // cross-platform paste (adapts based on OS mode)
    US_CUT,         // cross-platform cut (adapts based on OS mode)
    US_OS_TOGGLE,   // toggle between Linux and Mac mode
};

// Userspace implementations (provided by ngarvey.c)
bool          process_record_user(uint16_t keycode, keyrecord_t *record);
layer_state_t layer_state_set_user(layer_state_t state);
void          matrix_scan_user(void);
void          keyboard_post_init_user(void);
void          send_cross_platform_copy(void);
void          send_cross_platform_paste(void);
void          send_cross_platform_cut(void);
os_mode_t     get_os_mode(void);
void          set_os_mode(os_mode_t mode);

// Optional per-keymap hooks you *may* define in keymap.c
bool          process_record_keymap(uint16_t keycode, keyrecord_t *record);
layer_state_t layer_state_set_keymap(layer_state_t state);
void          matrix_scan_keymap(void);
void          keyboard_post_init_keymap(void);
