// Copyright 2022 Kyle McCreery (@kylemccreery)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

//void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  //debug_enable=true;
  //debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
//}

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN1,
    _FN2,
    _FN3
};
/*
 *   /-------------------\
 *   |ENC| 1 | 2 | 3 |ENC|
 *   |---+---'---'---+---|
 *   | 4 |           | 5 |
 *   |---|           |---|
 *   | 6 |           | 7 |
 *   |---|           |---|
 *   | 8 |           | 9 |
 *   \-----,---,---,-----/
 *     | A | B | C | D |
 *     \---'---'---'---/
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
    KC_MUTE,  MO(_FN3), MO(_FN2), MO(_FN1),       LGUI(KC_D),
    KC_HOME,                                      MO(_FN2),
    KC_END,                                       MO(_FN3),
    KC_BTN3,  KC_BTN1, KC_BTN2, KC_BTN2, KC_BTN1, DPI_FINE
    ),
    [_FN1] = LAYOUT(
    RGB_TOG, KC_TRNS, KC_TRNS, KC_TRNS,          TAP_TOG,
    RGB_MOD,                                     TAP_ON,
    RGB_RMOD,                                    TAP_OFF,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_FN2] = LAYOUT(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
    KC_PGUP,                                     KC_TRNS,
    KC_PGDN,                                     KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_FN3] = LAYOUT(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          RESET,
    KC_TRNS,                                     KC_TRNS,
    KC_TRNS,                                     KC_TRNS,
    KC_TRNS, DPI_DN,  DPI_UP,  TAP_DN,  TAP_UP,  KC_TRNS
    )
};
