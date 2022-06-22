// Copyright 2022 Kyle McCreery (@kylemccreery)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "cirque_kinetic.h"

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN1,
    _FN2,
    _FN3
};

/*   Physical Layout:
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
 *
 *   Keymap Layout:
 *   ENC, 1, 2, 3,    ENC,
 *   4,               5,
 *   6,               7,
 *   8,   A, B, C, D, 9,
 *   
 */

enum Surnia_keycodes {
    kineticBrake = SAFE_RANGE,
    kineticGlide,
    NEW_SAFE_RANGE
};

bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    switch(keycode) {
        #ifdef POINTING_DEVICE_ENABLE
            case kineticBrake:
                if (record->event.pressed) {
                    frictionMultiplier = 5;
                } else {
                    frictionMultiplier = 1;
                }
            return false;
            case kineticGlide:
                if (record->event.pressed) {
                    frictionMultiplier = 0.2;
                } else {
                    frictionMultiplier = 1;
                }
            return false;
        #endif
    }
}

#ifdef POINTING_DEVICE_ENABLE
    if (touchData.zValue){//records last mouse input prior to liftoff. 
        xVal = mouse_report->x;
        yVal = mouse_report_>y;
        LIFTOFF = FALSE;
    } else if (!touchData.zValue) {
        LIFTOFF = TRUE;
    }

#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
    KC_MUTE,  MO(_FN3), MO(_FN2), FINE,           MO(_FN1),
    KC_WFWD,                                     KC_BTN3,
    KC_WBAK,                                     KC_BTN2,
    KC_ENTER, KC_BTN1, KC_BTN2, KC_BTN2, KC_BTN1, DPI_FINE
    ),
    [_FN1] = LAYOUT(
    RGB_TOG, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
    kineticBrake,                                DPI_UP,
    kineticGlide,                                DPI_DN,
    KC_TRNS, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  KC_TRNS
    ),
    [_FN2] = LAYOUT(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          RGB_TOG,
    KC_TRNS,                                     RGB_MOD,
    KC_TRNS,                                     RGB_RMOD,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_FN3] = LAYOUT(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          RESET,
    KC_TRNS,                                     KC_TRNS,
    KC_TRNS,                                     KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
};
