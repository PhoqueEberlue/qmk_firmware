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


// French characters
#define EACU KC_2          // é
#define EGRV KC_7          // è
#define AGRV KC_0          // à
#define CCED KC_9          // ç
#define UGRV KC_QUOT       // ù
#define EURO ALGR(KC_E)    // €
#define DEG  LSFT(KC_MINS) // °
#define DIAE LSFT(CIRC)  // ¨
//
#define PIPE LSFT(KC_BSLS)

// Dvorak remaps
#define LBRC KC_MINS
#define RBRC KC_EQL
#define LCBR LSFT(KC_MINS)
#define RCBR LSFT(KC_EQL)
#define PLUS LSFT(KC_RBRC)
#define EQL  KC_RBRC

// Mod taps
// Naming: <key when tap>_<key when hold>
#define SPC_GUI  MT(MOD_LGUI, KC_SPC)
#define DEL_ALT  MT(MOD_LALT, KC_DEL)
#define ENT_CTL  MT(MOD_LCTL, KC_ENT)
#define BSPC_SFT MT(MOD_LSFT, KC_BSPC)

// Combos
const uint16_t PROGMEM altgr_combo[] = {SPC_GUI, DEL_ALT, COMBO_END};

combo_t key_combos[] = {
    COMBO(altgr_combo, KC_ALGR),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
    // ┌────────┬────────┬────────┬────────┬────────┬────────┐                    ┌────────┬────────┬────────┬────────┬────────┬────────┐
        KC_TAB  ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,                     KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_LBRC ,
    // ├────────┼────────┼────────┼────────┼────────┼────────┤                    ├────────┼────────┼────────┼────────┼────────┼────────┤
        KC_ESC  ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,                     KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_QUOT ,
    // ├────────┼────────┼────────┼────────┼────────┼────────┤                    ├────────┼────────┼────────┼────────┼────────┼────────┤
        DM_REC1 ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,                     KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,DM_PLY1 ,
    // ├────────┼────────┼────────┼────────┼────────┼────────┤                    ├────────┼────────┼────────┼────────┼────────┼────────┤
        KC_BTN1 ,KC_WH_D ,KC_WH_U ,KC_BTN2 ,SPC_GUI ,DEL_ALT ,                     ENT_CTL ,BSPC_SFT,KC_MS_L ,KC_MS_D ,KC_MS_U ,KC_MS_R ,
    // └────────┴────────┴────────┴────────┼────────┼────────┤                    ├────────┼────────┼────────┴────────┴────────┴────────┘
                                            MO(1)   ,TG(3)   ,                     RGB_TOG ,MO(2)
    //                                     └────────┴────────┘                    └────────┴────────┘
    ),
    // Numeric, symbols and FN
    [1] = LAYOUT(
    // ┌────────┬────────┬────────┬────────┬────────┬────────┐                    ┌────────┬────────┬────────┬────────┬────────┬────────┐
        KC_GRV  ,KC_EXLM ,KC_AT   ,KC_HASH ,KC_DLR  ,KC_PERC ,                     KC_CIRC ,KC_AMPR ,KC_ASTR ,KC_LPRN ,KC_RPRN ,KC_BSLS ,
    // ├────────┼────────┼────────┼────────┼────────┼────────┤                    ├────────┼────────┼────────┼────────┼────────┼────────┤
        KC_TILD ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,                     KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,PIPE    ,
    // ├────────┼────────┼────────┼────────┼────────┼────────┤                    ├────────┼────────┼────────┼────────┼────────┼────────┤
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        PLUS    ,LBRC    ,LCBR    ,RCBR    ,RBRC    ,EQL     ,
    // ├────────┼────────┼────────┼────────┼────────┼────────┤                    ├────────┼────────┼────────┼────────┼────────┼────────┤
        _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
    // └────────┴────────┴────────┴────────┼────────┼────────┤                    ├────────┼────────┼────────┴────────┴────────┴────────┘
                                            _______, _______,                      RGB_MOD, _______
    //                                     └────────┴────────┘                    └────────┴────────┘
    ),
    // FN/Navigation layout
    [2] = LAYOUT(
    // ┌────────┬────────┬────────┬────────┬────────┬────────┐                    ┌────────┬────────┬────────┬────────┬────────┬────────┐
        _______, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,                       _______, _______, C_WRDL,  C_WRDR,  _______, _______,
    // ├────────┼────────┼────────┼────────┼────────┼────────┤                    ├────────┼────────┼────────┼────────┼────────┼────────┤
        _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,                       _______, KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RIGHT,_______,
    // ├────────┼────────┼────────┼────────┼────────┼────────┤                    ├────────┼────────┼────────┼────────┼────────┼────────┤
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______,
    // ├────────┼────────┼────────┼────────┼────────┼────────┤                    ├────────┼────────┼────────┼────────┼────────┼────────┤
        _______, _______, _______, _______, _______,  _______,                     _______, _______, _______, _______, _______, _______,
    // └────────┴────────┴────────┴────────┼────────┼────────┤                    ├────────┼────────┼────────┴────────┴────────┴────────┘
                                            _______,  _______,                     _______, _______
    //                                     └────────┴────────┘                    └────────┴────────┘
    ),
    // Gaming layout (no mod tap, shift ctrl on the right place)
    [3] = LAYOUT(
    // ┌────────┬────────┬────────┬────────┬────────┬────────┐                    ┌────────┬────────┬────────┬────────┬────────┬────────┐
        _______ ,_______, _______, _______, _______,  _______,                     _______, _______ ,_______ ,_______ ,_______ ,_______,
    // ├────────┼────────┼────────┼────────┼────────┼────────┤                    ├────────┼────────┼────────┼────────┼────────┼────────┤
        _______ ,_______, _______, _______, _______,  _______,                     _______, _______ ,_______ ,_______ ,_______ , _______,
    // ├────────┼────────┼────────┼────────┼────────┼────────┤                    ├────────┼────────┼────────┼────────┼────────┼────────┤
        KC_LSFT ,_______, _______, _______, _______,  _______,                     _______, _______, _______ ,_______ ,_______ , _______,
    // ├────────┼────────┼────────┼────────┼────────┼────────┤                    ├────────┼────────┼────────┼────────┼────────┼────────┤
        KC_LCTL ,_______, _______, _______, KC_SPC,  KC_DEL,                       KC_ENT,  KC_BSPC, _______, _______ ,_______ , _______,
    // └────────┴────────┴────────┴────────┼────────┼────────┤                    ├────────┼────────┼────────┴────────┴────────┴────────┘
                                            _______,  _______,                     _______, _______
    //                                     └────────┴────────┘                    └────────┴────────┘
    ),
};
