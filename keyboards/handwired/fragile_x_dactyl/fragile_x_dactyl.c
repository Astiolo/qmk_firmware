#include "fragile_x_dactyl.h"

#include "drivers/sensors/pmw3360.h"

// #include "print.h"

static int8_t scroll_h;
static int8_t scroll_v;

#ifdef OLED_ENABLE
bool oled_task_kb(void) {
    if(!oled_task_user()) { return false; }

    return false;
}
#endif

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  // debug_enable=true;
  // debug_matrix=true;
  // debug_keyboard=true;
  // debug_mouse=true;
}

// void pointing_device_init_kb(void){
//     if(is_keyboard_left())
//         return;

//     // read config from EEPROM and update if needed

//     config_oddball_t kb_config;
//     kb_config.raw = eeconfig_read_kb();

//     if(!kb_config.cpi) {
//         kb_config.cpi = CPI_2;
//         eeconfig_update_kb(kb_config.raw);
//     }

//     pointing_device_set_cpi(kb_config.cpi);
// }

report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
    if (!is_keyboard_master()) return mouse_report;

    // dprintf("mouse x: %d, y: %d\n", mouse_report.x, mouse_report.y);
    int8_t clamped_x = mouse_report.x, clamped_y = mouse_report.y;
    mouse_report.x = 0;
    mouse_report.y = 0;

    if (is_keyboard_left()) {
        // accumulate scroll
        scroll_h += clamped_x;
        scroll_v += clamped_y;

        int8_t scaled_scroll_h = scroll_h / SCROLL_DIVIDER;
        int8_t scaled_scroll_v = scroll_v / SCROLL_DIVIDER;

        // clear accumulated scroll on assignment

        if (scaled_scroll_h != 0) {
            mouse_report.h = -scaled_scroll_h;
            scroll_h       = 0;
        }

        if (scaled_scroll_v != 0) {
            mouse_report.v = -scaled_scroll_v;
            scroll_v       = 0;
        }
    } else {
        mouse_report.x = -clamped_x;
        mouse_report.y = clamped_y;
    }

    return mouse_report;
}