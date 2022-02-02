/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "paw3204.h"
#include "pointing_device.h"
bool isScrollMode;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum layer_number {
    _QWERTY = 0,
    _RAISE,
    _LOWER,
    _ADJUST,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  SCRL
};

#define KC_L_SPC LT(_LOWER, KC_SPC)  // lower
#define KC_R_ENT LT(_RAISE, KC_ENT)  // raise
#define KC_G_JA LGUI_T(KC_LANG1)     // cmd or win
#define KC_G_EN LGUI_T(KC_LANG2)     // cmd or win
#define KC_C_BS LCTL_T(KC_BSPC)      // ctrl
#define KC_A_DEL ALT_T(KC_DEL)       // alt

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
    //,--------+--------+--------+--------+--------+--------.                 ,--------+---------+--------+---------+--------+--------.
       KC_ESC , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                   KC_Y   , KC_U    , KC_I   , KC_O    , KC_P   , KC_MINS,
    //|--------+--------+--------+--------+--------+--------|                 |--------+---------+--------+---------+--------+--------|
       KC_TAB , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_MS_BTN1,KC_NO, KC_H   , KC_J    , KC_K   , KC_L    , KC_SCLN, KC_QUOT,
    //|--------+--------+--------+--------+--------+--------|                 |--------+---------+--------+---------+--------+--------|
       KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_MS_BTN2,KC_NO, KC_N   , KC_M    , KC_COMM, KC_DOT  , KC_SLSH, KC_RSFT,
    //`--------+--------+--------+--------+--------+--------/                 \--------+---------+--------+---------+--------+--------'
                        KC_A_DEL, KC_G_EN, KC_L_SPC,KC_C_BS,                   KC_C_BS, KC_R_ENT, KC_G_JA, KC_A_DEL
    //                `----------+--------+--------+--------'                 `--------+---------+--------+---------'
    ),

    [_RAISE] = LAYOUT(
    //,--------+--------+--------+--------+--------+--------.                 ,--------+--------+--------+--------+--------+--------.
       _______, KC_BSLS, KC_CIRC, KC_EXLM, KC_AMPR, KC_PIPE,                   KC_AT  , KC_EQL , KC_PLUS, KC_ASTR, KC_PERC, KC_MINS,
    //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
       KC_LPRN, KC_HASH, KC_DLR , KC_DQT , KC_QUOT, KC_TILD, _______, _______, KC_LEFT, KC_DOWN,  KC_UP , KC_RGHT, KC_GRV , KC_RPRN,
    //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
       _______, _______, _______, _______, KC_LCBR, KC_LBRC, _______, _______, KC_RBRC, KC_RCBR, _______, _______, _______, _______,
    //`--------+--------+--------+--------+--------+--------/                 \--------+--------+--------+--------+--------+--------'
                         _______, _______, _______, _______,                   _______, _______, _______, RESET
    //                  `--------+--------+--------+--------'                 `--------+--------+--------+--------'
    ),

    [_LOWER] = LAYOUT(
    //,--------+--------+--------+--------+--------+--------.                 ,--------+--------+--------+--------+--------+--------.
       KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  ,                   _______, KC_EQL , KC_PLUS, KC_ASTR, KC_PERC, KC_MINS,
    //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
       _______, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , _______, _______, KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , _______,
    //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
       KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , _______, _______, _______, _______, KC_COMM, KC_DOT , KC_SLSH, _______,
    //`--------+--------+--------+--------+--------+--------/                 \--------+--------+--------+--------+--------+--------'
                         RESET  , _______, _______, _______,                   _______, _______, _______, _______
    //                  `--------+--------+--------+--------'                 `--------+--------+--------+--------'
    ),

    [_ADJUST] = LAYOUT(
    //,--------+--------+--------+--------+--------+--------.                     ,--------+--------+--------+--------+--------+--------.
        _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______,
    //|--------+--------+--------+--------+--------+--------|                     |--------+--------+--------+--------+--------+--------|
        _______, _______, _______, _______, _______, _______,  _______, _______,    _______, _______, _______, _______, _______, _______,
    //|--------+--------+--------+--------+--------+--------|                     |--------+--------+--------+--------+--------+--------|
        _______, _______, _______, _______, _______, _______,  _______, _______,    _______, _______, _______, _______, _______, _______,
    //`--------+--------+--------+--------+--------+--------/                     \--------+--------+--------+--------+--------+--------'
                          _______, _______, _______, _______,                       _______, _______, _______, _______
    //                  `--------+--------+--------+--------'                     `--------+--------+--------+--------'
    ),
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case SCRL:
      if (record->event.pressed) {
        isScrollMode = true;
        dprint("scroll ON\n");
      }
      else {
        isScrollMode = false;
        dprint("scroll OFF\n");
      }
      return false;
  }
  return true;
}

void matrix_init_user(void) {
    init_paw3204();
}

void matrix_scan_user(void) {
    static int  cnt;
    static bool paw_ready;

    report_mouse_t mouse_rep = pointing_device_get_report();

    if (cnt++ % 50 == 0) {
        uint8_t pid = read_pid_paw3204();
        if (pid == 0x30) {
            dprint("paw3204 OK\n");
            paw_ready = true;
        } else {
            dprintf("paw3204 NG:%d\n", pid);
            paw_ready = false;
        }
    }

    if (paw_ready) {
        uint8_t stat;
        int8_t x, y;
        int8_t r_x, r_y;

        read_paw3204(&stat, &x, &y);

        // 45-degree angle
        int8_t degree = 45;
        r_x =  x * cos(degree) + y * sin(degree);
        r_y = -x * sin(degree) + y * cos(degree);
        /* normal angle
        r_x = y;
        r_y = x;
        */

        if (isScrollMode) {
            if (cnt % 5 == 0) {
                mouse_rep.v = -r_y;
                mouse_rep.h = r_x;
            }
        } else {
            mouse_rep.x = r_x;
            mouse_rep.y = r_y;
        }

        if (cnt % 10 == 0) {
            dprintf("stat:%3d x:%4d y:%4d\n", stat, mouse_rep.x, mouse_rep.y);
        }

        if (stat & 0x80) {
            pointing_device_set_report(mouse_rep);
        }
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _LOWER:
        isScrollMode = true;
        break;
    default:
        isScrollMode = false;
        break;
    }
  return state;
}
