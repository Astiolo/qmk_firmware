#include QMK_KEYBOARD_H

#define _QWERTY 0
#define _GAME 1
#define _LOWER 2
#define _RAISE 3

#define GAME TG(_GAME)
#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

const uint16_t PROGMEM combo_sel_game[] = {KC_GRV, KC_EQL, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(combo_sel_game, GAME)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        KC_GRV , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                         KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_EQL,
        KC_TAB , KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  ,                         KC_Y  , KC_U  , KC_I  , KC_O  , KC_P  ,KC_MINS,
        KC_LSFT, KC_A  , KC_S  , KC_D  , KC_F  , KC_G  ,                         KC_H  , KC_J  , KC_K  , KC_L  ,KC_SCLN,KC_QUOT,
        KC_LCTL, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,                         KC_N  , KC_M  ,KC_COMM, KC_DOT,KC_SLSH,KC_BSLASH,
                        KC_LEFT,KC_RIGHT,                                                        KC_UP , KC_DOWN,
                                KC_SPC, KC_LCTL, RAISE ,                         LOWER ,KC_BSPC, KC_DEL,
                         KC_ESC,        KC_LALT,                                         KC_END,         KC_ESC,
                                KC_MEH, KC_HOME, KC_LWIN,                        KC_ENT, KC_END,KC_LSFT
    ),

    [_GAME] = LAYOUT(
      _______, _______ ,_______,_______,_______,_______,                         _______,_______,_______,_______,_______,_______,
        KC_T  , KC_TAB , KC_Q  , KC_W  , KC_E  , KC_R  ,                         _______,_______,_______,_______,_______,_______,
        KC_G  , KC_LSFT, KC_A  , KC_S  , KC_D  , KC_F  ,                         _______,_______,_______,_______,_______,_______,
        KC_B  , KC_LCTL, KC_Z  , KC_X  , KC_C  , KC_V  ,                         _______,_______,_______,_______,_______,_______,
                        _______,_______,                                                 _______,_______,
                                _______,_______,_______,                         _______,_______,_______,
                        _______,        _______,                                         _______,        _______,
                                _______,_______, _______,                        _______,_______,_______

    ),

    [_LOWER] = LAYOUT(
        KC_TILD,KC_EXLM, KC_AT ,KC_HASH,KC_DLR ,KC_PERC,                        KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_DEL ,
        _______,_______,_______,_______,_______,KC_LBRC,                        KC_RBRC, KC_P7 , KC_P8 , KC_P9 ,_______,KC_PLUS,
        _______,KC_HOME,KC_PGUP,KC_PGDN,KC_END ,KC_LPRN,                        KC_RPRN, KC_P4 , KC_P5 , KC_P6 ,KC_MINS,KC_PIPE,
        _______,_______,_______,_______,_______,KC_LABK,                        KC_RABK, KC_P1 , KC_P2 , KC_P3 ,KC_EQL ,KC_UNDS,
                        _______,KC_PSCR,                                                         KC_P0 ,_______,
                                _______,_______,_______,                        _______,_______,_______,
                        _______,        _______,                                        _______,        _______,
                                _______,_______,_______,                        _______,_______,_______

    ),

    [_RAISE] = LAYOUT(
          KC_F12 , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,                        KC_F6  , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 ,
          _______,_______,_______,_______,_______,KC_LBRC,                        KC_RBRC,_______,KC_NLCK,KC_INS ,KC_SLCK,KC_MUTE,
          _______,KC_LEFT,KC_UP  ,KC_DOWN,KC_RGHT,KC_LPRN,                        KC_RPRN,KC_MPRV,KC_MPLY,KC_MNXT,_______,KC_VOLU,
          _______,_______,_______,_______,_______,_______,                        _______,_______,_______,_______,_______,KC_VOLD,
                          _______,_______,                                                        KC_EQL ,_______,
                                  _______,_______,_______,                        _______,_______,_______,
                          _______,        _______,                                        _______,        _______,
                                  _______,_______,_______,                        _______,_______,_______
    )
};

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _GAME:
            oled_write_P(PSTR("Game\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
    return false;
}
#endif