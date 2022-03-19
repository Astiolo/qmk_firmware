#include "fragile_x_dactyl.h"

#include "drivers/sensors/pmw3360.h"

#include "print.h"

bool fxd_mouse_right = true;
bool fxd_mouse_adjust = false;
config_fxd_t fxd_kb_config;

#ifdef OLED_ENABLE
bool oled_task_kb(void) {
    if(!oled_task_user()) { return false; }

    return false;
}
#endif

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
//   debug_enable=true;
  // debug_matrix=true;
  // debug_keyboard=true;
  // debug_mouse=true;
}
void pointing_device_init_kb(void){
    // read config from EEPROM and update if needed
    fxd_kb_config.raw = eeconfig_read_kb();

    if(!fxd_kb_config.cpi) {
        fxd_kb_config.cpi = CPI_DEF;
        eeconfig_update_kb(fxd_kb_config.raw);
    }
    if(!fxd_kb_config.scroll) {
        fxd_kb_config.scroll = SCROLL_DEF;
        eeconfig_update_kb(fxd_kb_config.raw);
    }

    pointing_device_set_cpi(fxd_kb_config.cpi);
}

uint16_t adustThresh = 1<<15;
report_mouse_t pointing_device_task_combined_kb(report_mouse_t left_report, report_mouse_t right_report) {
    // Write eeprom config once finished adjusting
    static bool adjusting = false; 
    static bool changed; 
    static config_fxd_t old_cfg;
    static int8_t scroll_h = 0;
    static int8_t scroll_v = 0;

    // handle sensitivity adjustment and saving (only save if there were changes)
    if (!fxd_mouse_adjust && adjusting) {
        adjusting = false;
        if (changed){ 
            eeconfig_update_kb(fxd_kb_config.raw);
            changed = false;
        }
    }

    if (fxd_mouse_adjust) {
        adjusting = true;
        old_cfg = fxd_kb_config;

        fxd_kb_config.cpi -= left_report.y;
        fxd_kb_config.scroll += right_report.y;

        if (fxd_kb_config.cpi > adustThresh) fxd_kb_config.cpi = 0;
        if (fxd_kb_config.cpi > CPI_MAX) fxd_kb_config.cpi = CPI_MAX;
        if (fxd_kb_config.scroll > adustThresh) fxd_kb_config.scroll = 0;
        if (fxd_kb_config.scroll > SCROLL_MAX) fxd_kb_config.scroll = SCROLL_MAX;

        if(old_cfg.raw != fxd_kb_config.raw){
            pointing_device_set_cpi(fxd_kb_config.cpi);
            changed = true;
        }
        left_report.x = 0;
        left_report.y = 0;
        return pointing_device_combine_reports(left_report, right_report);
    }

    // handle handedness
    if (fxd_mouse_right) {
        scroll_h += left_report.x;
        scroll_v += left_report.y;
        left_report.x = 0;
        left_report.y = 0;
        right_report.x = -right_report.x;
    } else {
        scroll_h += right_report.x;
        scroll_v += right_report.y;
        right_report.x = 0;
        right_report.y = 0;
        left_report.x = -left_report.x;
    }

    // accumulate scroll
    int8_t scaled_scroll_h = scroll_h / fxd_kb_config.scroll;
    int8_t scaled_scroll_v = scroll_v / fxd_kb_config.scroll;

    // clear accumulated scroll on assignment
    if (scaled_scroll_h != 0) {
        combined_report.h = -scaled_scroll_h;
        scroll_h       = 0;
    }

    if (scaled_scroll_v != 0) {
        combined_report.v = -scaled_scroll_v;
        scroll_v       = 0;
        scroll_h       = 0;
    }

    return pointing_device_combine_reports(left_report, right_report);
}
// report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
//     // Write eeprom config once finished adjusting
//     static bool adjusting = false; 
//     static bool changed; 
//     static config_fxd_t old_cfg;
//     if (!fxd_mouse_adjust && adjusting) {
//         adjusting = false;
//         if (changed){ 
//             eeconfig_update_kb(fxd_kb_config.raw);
//             changed = false;
//         }
//     }

//     if (fxd_mouse_adjust) {
//         adjusting = true;
//         old_cfg = fxd_kb_config;

//         fxd_kb_config.cpi -= mouse_report.y;
//         fxd_kb_config.scroll -= mouse_report.x;

//         if (fxd_kb_config.cpi > adustThresh) fxd_kb_config.cpi = 0;
//         if (fxd_kb_config.cpi > CPI_MAX) fxd_kb_config.cpi = CPI_MAX;
//         if (fxd_kb_config.scroll > adustThresh) fxd_kb_config.scroll = 0;
//         if (fxd_kb_config.scroll > SCROLL_MAX) fxd_kb_config.scroll = SCROLL_MAX;

//         if(old_cfg.raw != fxd_kb_config.raw){
//             pointing_device_set_cpi(fxd_kb_config.cpi);
//             changed = true;
//         }
//         mouse_report.x = 0;
//         mouse_report.y = 0;
//     } else if ((!is_keyboard_left() && !fxd_mouse_right) || 
//         (is_keyboard_left() && fxd_mouse_right)) {
//         static int8_t scroll_h = 0;
//         static int8_t scroll_v = 0;
//         // accumulate scroll
//         scroll_h += mouse_report.x;
//         scroll_v += mouse_report.y;

//         int8_t scaled_scroll_h = scroll_h / fxd_kb_config.scroll;
//         int8_t scaled_scroll_v = scroll_v / fxd_kb_config.scroll;

//         // clear accumulated scroll on assignment

//         if (scaled_scroll_h != 0) {
//             mouse_report.h = -scaled_scroll_h;
//             scroll_h       = 0;
//         }

//         if (scaled_scroll_v != 0) {
//             mouse_report.v = -scaled_scroll_v;
//             scroll_v       = 0;
//             scroll_h       = 0;
//         }
//         mouse_report.x = 0;
//         mouse_report.y = 0;
//     } else {
//         mouse_report.x = -mouse_report.x;
//         mouse_report.y = mouse_report.y;
//     }

//     return mouse_report;
// }