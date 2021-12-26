#pragma once

#include "config_common.h"

#define VENDOR_ID 0xA571
#define PRODUCT_ID 0xF58D
#define PRODUCT FragileXDactyl
#define DEVICE_VER 0

// Rows are doubled-up
#define MATRIX_ROWS 12
#define MATRIX_COLS 6

#define MATRIX_ROW_PINS { A0, A1, A2, A3, A4, A5 }
#define MATRIX_COL_PINS { B0, B1, B2, B3, B4, B5 }

#define DIODE_DIRECTION COL2ROW