#pragma once
#include "quantum.h"

// Custom keycodes shared across all your keyboards
enum userspace_custom_keycodes {
    US_SAFE_RANGE = SAFE_RANGE,
    US_HELLO,       // types a test string
    US_NEXT_LAYER,  // cycles default base layer (0..7)
};

// Userspace implementations (provided by ngarvey.c)
bool          process_record_user(uint16_t keycode, keyrecord_t *record);
layer_state_t layer_state_set_user(layer_state_t state);
void          matrix_scan_user(void);
void          keyboard_post_init_user(void);

// Optional per-keymap hooks you *may* define in keymap.c
bool          process_record_keymap(uint16_t keycode, keyrecord_t *record);
layer_state_t layer_state_set_keymap(layer_state_t state);
void          matrix_scan_keymap(void);
void          keyboard_post_init_keymap(void);