#include QMK_KEYBOARD_H
#include <string.h>

enum my_keycodes {
  PIKACHU = SAFE_RANGE,
  MESSAGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_split_3x6_3(LSFT_T(KC_TAB), KC_Q, KC_W, KC_E, KC_R, KC_T, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_BSPC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, OSM(MOD_LCTL), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, MO(2), KC_SPC, MO(1), KC_NO, KC_NO, KC_NO),
	[1] = LAYOUT_split_3x6_3(KC_LBRC, KC_P, KC_O, KC_I, KC_U, KC_Y, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_QUOT, KC_SCLN, KC_L, KC_K, KC_J, KC_H, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_RBRC, KC_SLSH, KC_DOT, KC_COMM, KC_M, KC_N, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, TG(3), KC_LGUI, KC_TRNS, KC_NO, KC_NO, KC_NO),
	[2] = LAYOUT_split_3x6_3(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_DEL, KC_6, KC_7, KC_8, KC_9, KC_0, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, OSM(MOD_LALT), KC_MINS, KC_EQL, KC_GRV, KC_BSLS, KC_ENT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_LGUI, TG(3), KC_NO, KC_NO, KC_NO),
	[3] = LAYOUT_split_3x6_3(KC__VOLDOWN, KC__VOLUP, KC_UP, KC_F22, KC_F23, KC_PSCR, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, PIKACHU, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_ASTG, KC_NO, KC_NO, LCA(KC_GRV), KC_ENT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, TG(3), TG(3), TG(3), KC_NO, KC_NO, KC_NO)
};

bool pikachu_enabled = false;
bool message_enabled = false;

#ifdef OLED_ENABLE
#include <stdio.h>

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return rotation;
}

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

void oled_render_logo(void) {
    static const char PROGMEM raw_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 12,124,252,248,120, 48, 48, 32, 64,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,128,192,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  3, 12, 16, 96,192,128,128,  1,  3,  6, 12,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8, 16, 16, 16,  8,  8, 12,  4,  4,  2,  2,  2,  1,131, 71, 63, 31, 15,  3,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192, 56, 14,  1,  0,  0, 24, 44, 36, 24,  0,  0,  0,128,128,  0,  0,  0,  0, 48, 88, 72, 48,  0,  0,  0,  2,  6, 62,226,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,127,128,  6, 15, 15,  6,  0,  0,  0,  0,  0, 96, 88, 73, 72, 88, 96,  0,  0,  0,  0,  0, 24, 60, 60, 24,  0,  0,  0,131,126,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

char keylog_str[86] = {};
int i = 0;

const char code_to_name[44] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    ' ', ' ', ' ', ' '
    };

const char caps_to_name[44] = {
    ' ', ' ', ' ', ' ', 'A', 'B', 'C', 'D', 'E', 'F',
    'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    ' ', ' ', ' ', ' '
    };

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
  if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode == 42){
    if (record->event.pressed) {
        if (i > 0){
            i--;
        }
        keylog_str[i] = '\0';
        oled_clear();
        oled_write(keylog_str, false);
    }
  }
  if (keycode < 40 || keycode == 44){
    if ((keyboard_report->mods & MOD_BIT (KC_LSFT)) || (keyboard_report->mods & MOD_BIT (KC_RSFT))) {
        name = caps_to_name[keycode];
    } else {
        name = code_to_name[keycode];
    }

    keylog_str[i] = name;
    i++;
    if (i == 85){
        i = 0;
        memset(keylog_str, 0, sizeof(keylog_str));
    }
    oled_clear();
    oled_write(keylog_str, false);
  }
}

bool oled_task_user(void) {
    if (pikachu_enabled || layer_state == L_ADJUST) {
        oled_clear();
        oled_render_logo();
    } else if (keylog_str[0] != '\0'){
        oled_clear();
        oled_write(keylog_str, false);
    } else if (!message_enabled || keylog_str[0] == '\0'){
        oled_clear();
    }
    //}
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case PIKACHU:
      if (record->event.pressed) {
        pikachu_enabled = !pikachu_enabled;
      }
      return false; // Skip all further processing of this key
    case MESSAGE:
      if (record->event.pressed) {
        message_enabled = !message_enabled;
      }
      return false; // Skip all further processing of this key
    default:
      if (record->event.pressed && message_enabled) {
        set_keylog(keycode, record);
      }
      return true; // Process all other keycodes normally
  }
}

#endif // OLED_ENABLE
