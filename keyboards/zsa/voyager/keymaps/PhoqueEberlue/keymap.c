// Copyright 2023 ZSA Technology Labs, Inc <@zsa>
// Copyright 2023 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include <stdatomic.h>
#include QMK_KEYBOARD_H

#define C_WRDL LCTL(KC_LEFT)
#define C_WRDR LCTL(KC_RIGHT)

// Notes:
// - Disabling "rgb_matrix" in keyboard.json disables the ability to turn off rgb with RGB_TOG :(
//
// TODO:
// - add fn keys maybe?
// - continue the nav vim like layout
// - add more comments


// Defining AZERAK (Dvorak with azerty symbols)
#define A_1    LSFT(KC_1)    // 1
#define A_2    LSFT(KC_2)    // 2
#define A_3    LSFT(KC_3)    // 3
#define A_4    LSFT(KC_4)    // 4
#define A_5    LSFT(KC_5)    // 5
#define A_6    LSFT(KC_6)    // 6
#define A_7    LSFT(KC_7)    // 7
#define A_8    LSFT(KC_8)    // 8
#define A_9    LSFT(KC_9)    // 9
#define A_0    LSFT(KC_0)    // 0

#define A_EXLM KC_SLSH       // !
#define A_AT   ALGR(KC_0)    // @
#define A_HASH ALGR(KC_3)    // #
#define A_DLR  KC_RBRC       // $
#define A_PERC LSFT(KC_QUOT) // %
#define A_CIRC KC_LBRC       // ^
#define A_AMPR KC_1          // &
#define A_ASTR KC_BSLS       // *
#define A_LPRN KC_5          // (
#define A_RPRN KC_MINS       // )
#define A_BSLS ALGR(KC_8)    // "\"
#define A_PIPE ALGR(KC_6)    // |
#define A_GRV  ALGR(KC_7)    // `
#define A_TILD ALGR(KC_2)    // ~
#define A_SLSH LSFT(KC_DOT)  // "/"
#define A_PLUS LSFT(KC_EQL)  // +
#define A_LBRC ALGR(KC_5)    // [
#define A_LCBR ALGR(KC_4)    // {
#define A_RCBR ALGR(KC_EQL)  // }
#define A_RBRC ALGR(KC_MINS) // ]
#define A_EQL  KC_EQL        // =

#define A_SQOT KC_4          // '
#define A_DQOT KC_3          // "
#define A_LABK KC_NUBS       // <
#define A_RABK LSFT(KC_NUBS) // >
#define A_COMM KC_M          // ,
#define A_QMRK LSFT(KC_M)    // ?
#define A_SCLN KC_COMM       // ;
#define A_CLN  KC_DOT        // :
#define A_DOT  LSFT(KC_COMM) // .
#define A_DASH KC_6          // -
#define A_USCR KC_8          // _

// Letters with rebind
#define A_q    KC_A          // q
#define A_a    KC_Q          // a
#define A_m    KC_SCLN       // m
#define A_w    KC_Z          // w
#define A_z    KC_W          // z

#define A_Q    LSFT(KC_A)    // Q
#define A_A    LSFT(KC_Q)    // A
#define A_M    LSFT(KC_SCLN) // M
#define A_W    LSFT(KC_Z)    // W
#define A_Z    LSFT(KC_W)    // Z

// Letters without rebind but still defining constants for shifted letters
#define A_B    LSFT(KC_B)
#define A_C    LSFT(KC_C)
#define A_D    LSFT(KC_D)
#define A_E    LSFT(KC_E)
#define A_F    LSFT(KC_F)
#define A_G    LSFT(KC_G)
#define A_H    LSFT(KC_H)
#define A_I    LSFT(KC_I)
#define A_J    LSFT(KC_J)
#define A_K    LSFT(KC_K)
#define A_L    LSFT(KC_L)
#define A_N    LSFT(KC_N)
#define A_O    LSFT(KC_O)
#define A_P    LSFT(KC_P)
#define A_R    LSFT(KC_R)
#define A_S    LSFT(KC_S)
#define A_T    LSFT(KC_T)
#define A_U    LSFT(KC_U)
#define A_V    LSFT(KC_V)
#define A_X    LSFT(KC_X)
#define A_Y    LSFT(KC_Y)

// French characters
#define A_EACU KC_2          // é
#define A_EGRV KC_7          // è
#define A_AGRV KC_0          // à
#define A_CCED KC_9          // ç
#define A_UGRV KC_QUOT       // ù
#define A_EURO ALGR(KC_E)    // €
#define A_DEG  LSFT(KC_MINS) // °
#define A_DIAE LSFT(A_CIRC)  // ¨

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
    // ┌────────┬────────┬────────┬────────┬────────┬────────┐                    ┌────────┬────────┬────────┬────────┬────────┬────────┐
        KC_TAB  ,A_SQOT  ,A_COMM  ,A_DOT   ,KC_P    ,KC_Y    ,                     KC_F    ,KC_G    ,KC_C    ,KC_R    ,KC_L    ,A_SLSH  ,
    // ├────────┼────────┼────────┼────────┼────────┼────────┤                    ├────────┼────────┼────────┼────────┼────────┼────────┤
        KC_ESC  ,A_a     ,KC_O    ,KC_E    ,KC_U    ,KC_I    ,                     KC_D    ,KC_H    ,KC_T    ,KC_N    ,KC_S    ,A_DASH  ,
    // ├────────┼────────┼────────┼────────┼────────┼────────┤                    ├────────┼────────┼────────┼────────┼────────┼────────┤
        MO(1)   ,A_SCLN  ,A_q     ,KC_J    ,KC_K    ,KC_X    ,                     KC_B    ,A_m     ,A_w     ,KC_V    ,A_z     ,MO(1)   ,
    // ├────────┼────────┼────────┼────────┼────────┼────────┤                    ├────────┼────────┼────────┼────────┼────────┼────────┤
        KC_LCTL ,KC_LALT ,XXXXXXX ,KC_LGUI ,KC_SPC  ,KC_DEL  ,                     KC_ENT  ,KC_BSPC ,KC_LGUI ,XXXXXXX ,KC_RALT ,KC_RCTL ,
    // └────────┴────────┴────────┴────────┼────────┼────────┤                    ├────────┼────────┼────────┴────────┴────────┴────────┘
                                            MO(2)   ,TG(5)   ,                     MO(3)   ,MO(4)
    //                                     └────────┴────────┘                    └────────┴────────┘
    ),
    // Shifted letters layout
    [1] = LAYOUT(
    // ┌────────┬────────┬────────┬────────┬────────┬────────┐                    ┌────────┬────────┬────────┬────────┬────────┬────────┐
        KC_TAB,  A_DQOT,  A_LABK,  A_RABK,  A_P,     A_Y,                          A_F,     A_G,     A_C,     A_R,     A_L,     A_QMRK,
    // ├────────┼────────┼────────┼────────┼────────┼────────┤                    ├────────┼────────┼────────┼────────┼────────┼────────┤
        KC_ESC,  A_A,     A_O,     A_E,     A_U,     A_I,                          A_D,     A_H,     A_T,     A_N,     A_S,     A_USCR,
    // ├────────┼────────┼────────┼────────┼────────┼────────┤                    ├────────┼────────┼────────┼────────┼────────┼────────┤
        _______ ,A_CLN,   A_Q,     A_J,     A_K,     A_X,                          A_B,     A_M,     A_W,     A_V,     A_Z,     _______ ,
    // ├────────┼────────┼────────┼────────┼────────┼────────┤                    ├────────┼────────┼────────┼────────┼────────┼────────┤
        KC_LCTL, KC_LALT, XXXXXXX, KC_LGUI, KC_SPC,  KC_DEL,                       KC_ENT,  KC_BSPC, KC_LGUI, XXXXXXX, KC_RALT, KC_RCTL,
    // └────────┴────────┴────────┴────────┼────────┼────────┤                    ├────────┼────────┼────────┴────────┴────────┴────────┘
                                            MO(2),   TG(5),                        MO(3),   MO(4)
    //                                     └────────┴────────┘                    └────────┴────────┘
    ),
    // Numeric, symbols and FN
    [2] = LAYOUT(
    // ┌────────┬────────┬────────┬────────┬────────┬────────┐                    ┌────────┬────────┬────────┬────────┬────────┬────────┐
        A_GRV,   A_EXLM,  A_AT,    A_HASH,  A_DLR,   A_PERC,                        A_CIRC,  A_AMPR,  A_ASTR,  A_LPRN,  A_RPRN,  A_BSLS,
    // ├────────┼────────┼────────┼────────┼────────┼────────┤                    ├────────┼────────┼────────┼────────┼────────┼────────┤
        A_TILD,  A_1,     A_2,     A_3,    A_4,      A_5,                          A_6,     A_7,     A_8,     A_9,     A_0,     A_PIPE,
    // ├────────┼────────┼────────┼────────┼────────┼────────┤                    ├────────┼────────┼────────┼────────┼────────┼────────┤
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        A_PLUS,  A_LBRC,  A_LCBR,  A_RCBR,  A_RBRC,  A_EQL,
    // ├────────┼────────┼────────┼────────┼────────┼────────┤                    ├────────┼────────┼────────┼────────┼────────┼────────┤
        _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
    // └────────┴────────┴────────┴────────┼────────┼────────┤                    ├────────┼────────┼────────┴────────┴────────┴────────┘
                                            _______, _______,                      _______, _______
    //                                     └────────┴────────┘                    └────────┴────────┘
    ),
    // French characters
    [3] = LAYOUT(
    // ┌────────┬────────┬────────┬────────┬────────┬────────┐                    ┌────────┬────────┬────────┬────────┬────────┬────────┐
        _______, _______, A_DIAE  ,A_EURO  ,A_DEG   , _______,                     _______, _______ ,_______ ,_______ ,  _______,_______,
    // ├────────┼────────┼────────┼────────┼────────┼────────┤                    ├────────┼────────┼────────┼────────┼────────┼────────┤
        _______, A_AGRV  ,A_EACU  ,A_EGRV  ,A_UGRV  ,A_CCED  ,                     _______, _______ ,_______ ,_______ ,_______, _______,
    // ├────────┼────────┼────────┼────────┼────────┼────────┤                    ├────────┼────────┼────────┼────────┼────────┼────────┤
        _______, _______, _______, _______, _______,  _______,                     _______, _______, _______ ,_______ , _______, _______,
    // ├────────┼────────┼────────┼────────┼────────┼────────┤                    ├────────┼────────┼────────┼────────┼────────┼────────┤
        _______, _______, _______, _______, _______,  _______,                     _______, _______, _______, _______,  _______, _______,
    // └────────┴────────┴────────┴────────┼────────┼────────┤                    ├────────┼────────┼────────┴────────┴────────┴────────┘
                                            _______,  _______,                     _______, _______
    //                                     └────────┴────────┘                    └────────┴────────┘
    ),
    // Navigation layout
    [4] = LAYOUT(
    // ┌────────┬────────┬────────┬────────┬────────┬────────┐                    ┌────────┬────────┬────────┬────────┬────────┬────────┐
        _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,                       _______, _______, C_WRDL,  C_WRDR,  _______, _______,
    // ├────────┼────────┼────────┼────────┼────────┼────────┤                    ├────────┼────────┼────────┼────────┼────────┼────────┤
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        _______, KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RIGHT,_______,
    // ├────────┼────────┼────────┼────────┼────────┼────────┤                    ├────────┼────────┼────────┼────────┼────────┼────────┤
        _______, _______, _______, _______,  _______, _______,                    _______,   KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______,
    // ├────────┼────────┼────────┼────────┼────────┼────────┤                    ├────────┼────────┼────────┼────────┼────────┼────────┤
        _______, _______, _______, _______, _______,  _______,                     XXXXXXX, _______, _______, _______, _______, _______,
    // └────────┴────────┴────────┴────────┼────────┼────────┤                    ├────────┼────────┼────────┴────────┴────────┴────────┘
                                            _______,  _______,                     _______, _______
    //                                     └────────┴────────┘                    └────────┴────────┘
    ),
    // Mouse layout
    [5] = LAYOUT(
    // ┌────────┬────────┬────────┬────────┬────────┬────────┐                    ┌────────┬────────┬────────┬────────┬────────┬────────┐
        RGB_TOG, _______, _______, _______, _______,  _______,                     _______, _______ ,KC_BTN1,KC_BTN2,  _______,_______,
    // ├────────┼────────┼────────┼────────┼────────┼────────┤                    ├────────┼────────┼────────┼────────┼────────┼────────┤
        RGB_MOD, _______, _______, _______, _______,  _______,                     _______, KC_MS_L ,KC_MS_D ,KC_MS_U ,KC_MS_R, _______,
    // ├────────┼────────┼────────┼────────┼────────┼────────┤                    ├────────┼────────┼────────┼────────┼────────┼────────┤
        _______, _______, _______, _______, _______,  _______,                     _______, _______, KC_WH_D ,KC_WH_U, _______, _______,
    // ├────────┼────────┼────────┼────────┼────────┼────────┤                    ├────────┼────────┼────────┼────────┼────────┼────────┤
        _______, _______, _______, _______, _______,  _______,                     _______, _______, _______, _______,  _______, _______,
    // └────────┴────────┴────────┴────────┼────────┼────────┤                    ├────────┼────────┼────────┴────────┴────────┴────────┘
                                            _______,  _______,                     _______, _______
    //                                     └────────┴────────┘                    └────────┴────────┘
    ),
};
