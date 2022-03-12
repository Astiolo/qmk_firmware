#include QMK_KEYBOARD_H

#define _QWERTY 0
#define _GAME 1
#define _MATH 2
#define _MOUSE_L 3
#define _MOUSE_R 4

#define GAME TG(_GAME)
#define MATH LT(_MATH, KC_RWIN)
#define MOUSE_R LT(_MOUSE_R, KC_ENT)
#define MOUSE_L LT(_MOUSE_L, KC_ENT)

#define L_TAB RCS(KC_TAB)
#define R_TAB LCTL(KC_TAB)
#define CL_TAB LCTL(KC_W)

const uint16_t PROGMEM combo_sel_game[] = {KC_GRV, KC_EQL, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(combo_sel_game, GAME)
};

#define MOUSE_LAYOUT LAYOUT(\
        _______,_______,_______, CL_TAB, L_TAB , R_TAB ,                        L_TAB  , R_TAB , CL_TAB,_______,_______,_______ ,\
        _______,_______,KC_VOLU,KC_MNXT,KC_BTN5,KC_BTN4,                        KC_BTN4,KC_BTN5,KC_MNXT,KC_VOLU,_______,_______,\
        _______,_______,KC_MUTE,KC_MPLY,KC_BTN2,KC_BTN1,                        KC_BTN1,KC_BTN2,KC_MPLY,KC_MUTE,_______,_______,\
        _______,_______,KC_VOLD,KC_MPRV,_______,KC_BTN3,                        KC_BTN3,_______,KC_MPRV,KC_VOLD,_______,_______,\
                        KC_HOME, KC_END,                                                        KC_PGUP,KC_PGDN,\
                                _______,_______,_______,                        _______,_______,_______,\
                        _______,        _______,                                        _______,        _______,\
                                _______,_______,_______,                        _______,_______,_______\
    )

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        KC_GRV , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                         KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_EQL,
        KC_TAB , KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  ,                         KC_Y  , KC_U  , KC_I  , KC_O  , KC_P  ,KC_MINS,
        KC_LSFT, KC_A  , KC_S  , KC_D  , KC_F  , KC_G  ,                         KC_H  , KC_J  , KC_K  , KC_L  ,KC_SCLN,KC_QUOT,
        KC_LCTL, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,                         KC_N  , KC_M  ,KC_COMM, KC_DOT,KC_SLSH,KC_BSLASH,
                        KC_LEFT,KC_RIGHT,                                                        KC_UP ,KC_DOWN,
                                 KC_SPC,KC_LCTL,MOUSE_L,                        MOUSE_R,KC_BSPC, KC_DEL,
                         KC_ESC,        KC_LALT,                                        KC_LALT,         KC_ESC,
                          MEH_T(KC_SPC), KC_HOME,KC_LWIN,                         MATH  , KC_END,KC_LSFT
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

    [_MATH] = LAYOUT(
        _______, KC_F1 , KC_F2 , KC_F3 , KC_F4 ,KC_LCBR,                        KC_RCBR,_______,_______,_______,_______,_______,
        _______, KC_F5 , KC_F6 , KC_F7 , KC_F8 ,KC_LBRC,                        KC_RBRC, KC_P7 , KC_P8 , KC_P9 ,KC_PLUS,_______,
        _______, KC_F9 , KC_F11, KC_F12, KC_F12,KC_LPRN,                        KC_RPRN, KC_P4 , KC_P5 , KC_P6 ,KC_MINS,KC_PIPE,
        _______,_______,_______,_______,_______,KC_LABK,                        KC_RABK, KC_P1 , KC_P2 , KC_P3 ,KC_EQL ,KC_UNDS,
                        _______,KC_PSCR,                                                         KC_P0 , KC_P0 ,
                                _______,_______,_______,                        _______,_______,_______,
                        _______,        _______,                                        _______,        _______,
                                _______,_______,_______,                        _______,_______,_______
    ),

    [_MOUSE_L] = MOUSE_LAYOUT,

    [_MOUSE_R] = MOUSE_LAYOUT
};

#ifdef OLED_ENABLE
uint16_t startup_timer;

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    startup_timer = timer_read();
    oled_clear();
    return rotation;
}
static void render_logo(void) {
    static const char PROGMEM raw_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 24, 60, 60,124,252,252,252,252,188, 60, 24,  0,  0,  0,  0,  0, 24, 60,188,252,252,252,252,124, 60, 60, 24,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  3,  7, 15, 31, 62,252,248,240,248,252, 62, 31, 15,  7,  3,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0, 32,224, 32,160, 32, 96,  0,128,128,  0,128,128,  0,  0,  0,128,128,128,  0,  0,  0,  0,128,128,  0,128,128,  0,128,128,160,  0,  0,  0,  0,  0, 32,224,  0,  0,  0,  0,  0,128,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0, 96,240,120,124, 62, 31, 15,  7,  3,  7, 15, 31, 62,124,120,240, 96,  0,  0,  0,  0,  0,  0,  0, 32,224, 32, 32, 64,128,  0,  0,  0,128,128,128,  0,  0,  0,  0,128,128,128,128,  0,  0,128,192,128,128,128,  0,128,128,128,  0,128,128,128,  0,  0, 32,224,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0, 16, 31, 17,  3,  0,  0,  0, 16, 31, 17, 16, 16,  0,  0, 12, 18, 18, 18, 31, 16,  0, 15, 80, 80, 81, 63,  0,  0, 16, 16, 31, 16, 16,  0,  0, 16, 16, 31, 16, 16,  0,  0, 15, 18, 18, 18, 19,  0,  0, 12, 30, 30, 30, 30, 30, 31, 30, 30, 30, 12,  0,  0,  0,  0,  0,  0,  0, 12, 30, 30, 30, 31, 30, 30, 30, 30, 30, 12,  0, 16, 31, 16, 16,  8,  7,  0,  0, 12, 18, 18, 18, 31, 16,  0, 15, 16, 16, 16,  9,  0,  0,  0, 15, 16, 16, 16,  8,  0, 65, 70,120, 76,  3,  0,  0, 16, 16, 31, 16, 16,  0,  0,  0,  0,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}


bool oled_task_user(void) {
  static bool finished_timer = false;
    if (!finished_timer && (timer_elapsed(startup_timer) < 20000)) {
        render_logo();
    } else {
        if (!finished_timer) {
            oled_clear();
            finished_timer = true;
        }
        // Host Keyboard Layer Status
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state)) {
            case _QWERTY:
                oled_write_P(PSTR("Default\n"), false);
                break;
            case _GAME:
                oled_write_P(PSTR("Game\n"), false);
                break;
            case _MATH:
                oled_write_P(PSTR("Math\n"), false);
                break;
            case _MOUSE_L:
                oled_write_P(PSTR("Mouse L\n"), false);
                break;
            case _MOUSE_R:
                oled_write_P(PSTR("Mouse R\n"), false);
                break;
            default:
                oled_write_P(PSTR("Undefined\n"), false);
        }
        // Write lock status
        led_t led_state = host_keyboard_led_state();
        oled_write_P(PSTR("\nNUM: "), false);
        oled_write_char(led_state.num_lock ? 0x04 : 0x09, false);
        oled_write_P(PSTR(" CAP: "), false);
        oled_write_char(led_state.caps_lock ? 0x04 : 0x09, false);
        oled_write_P(PSTR(" SCR: "), false);
        oled_write_char(led_state.scroll_lock ? 0x04 : 0x09, false);

        // TODO: Write actual DPI
        oled_write_P(PSTR("\nDPI: 300"), false);
        
    }
    return false;
}
#endif