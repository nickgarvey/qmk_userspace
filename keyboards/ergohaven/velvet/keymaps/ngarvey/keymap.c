#include QMK_KEYBOARD_H
#include "ngarvey.h"

// Adapted Voyager keymap based on Moonlander logic
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                              KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
        KC_BSPC,  MT(MOD_LALT, KC_A), MT(MOD_LCTL, KC_S), MT(MOD_LGUI, KC_D), MT(MOD_LSFT, KC_F), KC_G,   KC_H,    MT(MOD_RSFT, KC_J), MT(MOD_LGUI, KC_K), MT(MOD_LCTL, KC_L), MT(MOD_LALT, KC_SCLN), KC_QUOT,
        KC_TRNS,  KC_Z,    KC_X,    KC_C,    LT(3, KC_V), KC_B,                                           KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, CW_TOGG,
                          US_COPY, US_PASTE, KC_SPC, LT(2, KC_TAB),MO(3),                 QK_REP, LT(1, KC_BSPC), KC_ENT, KC_WH_U, KC_WH_D
    ),
    [1] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_BSLS, KC_CIRC, KC_PIPE, KC_TRNS,                                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_AT,   KC_EXLM, KC_DLR,  KC_HASH, KC_PLUS,                                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_AMPR, KC_PERC, KC_TRNS,                                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [2] = LAYOUT(
        KC_TRNS, LGUI(LCTL(KC_4)),LGUI(LCTL(KC_5)),LGUI(LCTL(KC_S)), LGUI(LCTL(KC_G)), KC_TRNS,       KC_HOME, KC_PGDN, KC_PAGE_UP, KC_END, KC_INSERT, KC_TRNS,
        KC_TRNS, OSM(MOD_LALT), OSM(MOD_LCTL), OSM(MOD_LGUI), OSM(MOD_LSFT), KC_TRNS,                 KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_DELETE, KC_TRNS,
        KC_TRNS, LSFT(KC_F16), LSFT(KC_F17), LSFT(KC_F18), LSFT(KC_F19), LSFT(KC_F20),                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [3] = LAYOUT(
        QK_BOOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                          KC_TRNS, KC_7, KC_8, KC_9, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                          KC_NO, KC_4, KC_5, KC_6, KC_0, KC_TRNS,
        US_OS_TOGGLE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                     KC_TRNS, KC_1, KC_2, KC_3, KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLD, KC_VOLU
    ),
};

tap_dance_action_t tap_dance_actions[] = {};
const key_override_t *key_overrides[] = { NULL };

// Combos and custom logic from Moonlander keymap
const uint16_t PROGMEM combo0[] = { KC_E, KC_R, KC_W, COMBO_END};
const uint16_t PROGMEM combo1[] = { KC_M, KC_COMMA, COMBO_END};
const uint16_t PROGMEM combo2[] = { KC_U, MT(MOD_RSFT, KC_J), COMBO_END};
const uint16_t PROGMEM combo3[] = { KC_R, MT(MOD_LSFT, KC_F), COMBO_END};
const uint16_t PROGMEM combo4[] = { KC_DOT, KC_COMMA, COMBO_END};
const uint16_t PROGMEM combo5[] = { KC_I, MT(MOD_LGUI, KC_K), COMBO_END};
const uint16_t PROGMEM combo6[] = { MT(MOD_LSFT, KC_F), KC_G, COMBO_END};
const uint16_t PROGMEM combo7[] = { KC_R, KC_T, COMBO_END};
const uint16_t PROGMEM combo8[] = { LT(3, KC_V), KC_B, COMBO_END};
const uint16_t PROGMEM combo9[] = { KC_H, MT(MOD_RSFT, KC_J), COMBO_END};
const uint16_t PROGMEM combo10[] = { KC_Y, KC_U, COMBO_END};
const uint16_t PROGMEM combo11[] = { KC_N, KC_M, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(combo0, KC_ESCAPE),
    COMBO(combo1, KC_MINUS),
    COMBO(combo2, KC_ASTR),
    COMBO(combo3, KC_EQUAL),
    COMBO(combo4, KC_GRAVE),
    COMBO(combo5, KC_QUOTE),
    COMBO(combo6, KC_LPRN),
    COMBO(combo7, KC_LBRC),
    COMBO(combo8, KC_LCBR),
    COMBO(combo9, KC_RPRN),
    COMBO(combo10, KC_RBRC),
    COMBO(combo11, KC_RCBR),
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MT(MOD_LSFT, KC_F):
            return TAPPING_TERM -50;
        case MT(MOD_RSFT, KC_J):
            return TAPPING_TERM -50;
        default:
            return TAPPING_TERM;
    }
}
