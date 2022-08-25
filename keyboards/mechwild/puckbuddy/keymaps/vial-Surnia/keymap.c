// Copyright 2022 Kyle McCreery (@kylemccreery)
// Copyright 2022 Surnia/nobiliana
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
//#include "cirque_kinetic.h"
extern float xVal, yVal;
extern int8_t LIFTOFF; 
extern int8_t frictionMultiplier;
extern void kineticCirque(report_mouse_t *mouse_report);

//debug sector
#include "print.h"

#define friction 0.35

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
    kineticGlide
};

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  debug_keyboard=true;
  debug_mouse=true;
}


bool process_record_user(uint16_t keycode, keyrecord_t* record) {
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
        default: 
            return true;
    }
}

/*
#ifdef POINTING_DEVICE_ENABLE
    static void pointing_device_task_Surnia(report_mouse_t* mouse_report) {
        pinnacle_data_t cirqueData = cirque_pinnacle_read_data();
            if (cirqueData.zValue){//records last mouse input prior to liftoff. 
                xVal = mouse_report->x;
                yVal = mouse_report->y;
                LIFTOFF = 0;
            } else if (!cirqueData.zValue) {
                LIFTOFF = 1;
            }
            uprintf("xVal: %f, yVal: %f, Liftoff: %f\n", xVal, yVal, LIFTOFF);
            kineticCirque(mouse_report->x, mouse_report->y);
    }
#endif
*/

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    /*
    if (is_keyboard_master()) {
        pointing_device_task_Surnia(&mouse_report);
        //mouse_report = pointing_device_task_user(mouse_report);
    }
    */
        pinnacle_data_t cirqueData = cirque_pinnacle_read_data();
            if (cirqueData.zValue){//records last mouse input prior to liftoff. 
                if (cirqueData.xValue !=0){
                    xVal = cirqueData.xValue;
                }
                if (cirqueData.yValue !=0){
                    yVal = cirqueData.yValue;
                }
                LIFTOFF = 0;
                uprintf("xVal: %i, yVal: %i, Liftoff: %i || mouse x: %i, mouse: y %i\n", xVal, yVal, LIFTOFF, mouse_report.x, mouse_report.y);
            } else if (!cirqueData.zValue) {
                LIFTOFF = 1;
                uprintf("lift detected!: %i, xVal: %i, yVal %i\n", LIFTOFF, xVal, yVal);
            }
            

            kineticCirque(&mouse_report);
    return mouse_report;
}

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (index) {
    case 0:
        if (clockwise) {
            tap_code(KC_DOWN);
        } else {
            tap_code(KC_UP);
        }
        break;
    case 1:
        if (clockwise) {
            tap_code(KC_WH_D);
        } else {
            tap_code(KC_WH_U);
        }
    break;
    }
    return false;
}
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
    KC_MUTE,  MO(_FN3), MO(_FN2), MO(_FN1),      MO(_FN1),
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
