#pragma once

#include "config_common.h"

#define VENDOR_ID 0xA571
#define PRODUCT_ID 0xF58D
#define PRODUCT FragileXDactyl
#define DEVICE_VER 0x0000

// Rows are doubled-up
#define MATRIX_ROWS 12
#define MATRIX_COLS 6

// #define MATRIX_ROW_PINS { A0, A1, C15, B1, A15, B3 }
#define MATRIX_ROW_PINS { A15, B3, B4, B5, B6, B7}
#define MATRIX_COL_PINS { B12, B13, B14, B15, A8, A10 }
#define DIODE_DIRECTION COL2ROW

#define SPLIT_HAND_PIN B10
#define SPLIT_USB_DETECT
#define USE_SERIAL

/* serial.c configuration for split keyboard (From Tractyl f411)*/ 
#define SERIAL_USART_FULL_DUPLEX  // Enable full duplex operation mode.
#define SERIAL_USART_TX_PIN      A2
#define SERIAL_USART_RX_PIN      A3
#define SERIAL_USART_DRIVER      SD2
#define SERIAL_USART_TX_PAL_MODE 7    // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7
#define SERIAL_USART_RX_PAL_MODE 7    // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7
#define SERIAL_USART_TIMEOUT     100  // USART driver timeout. default 100

/* i2c config for oleds (From Tractyl f411)*/
#define I2C_DRIVER        I2CD1
#define I2C1_SCL_PIN      B8 
#define I2C1_SDA_PIN      B9
#define I2C1_SCL_PAL_MODE 4
#define I2C1_SDA_PAL_MODE 4
#define I2C1_CLOCK_SPEED  400000
/* For Legacy Compatibility: */
#define I2C1_SCL 8
#define I2C1_SDA 9


/* optical sensor settings */
#define SCROLL_DIVIDER 12
#define CPI_1 2000
#define CPI_2 4000
#define CPI_3 8000
/* SPI Settings for Optical Sensor */
#define SPI_DRIVER                           SPID1
#define SPI_SCK_PIN                          A5
#define SPI_SCK_PAL_MODE                     5
#define SPI_MOSI_PIN                         A7
#define SPI_MOSI_PAL_MODE                    5
#define SPI_MISO_PIN                         A6
#define SPI_MISO_PAL_MODE                    5
/* pmw3360 config  */
#define PMW3360_CS_PIN                       B0
#define PMW3360_SPI_MODE                     3
#define PMW3360_SPI_DIVISOR                  64

#define COMBO_COUNT 1

// Defines for OLED data transfer between sides
#ifdef OLED_ENABLE
// #define SPLIT_TRANSPORT_MIRROR
#define SPLIT_LAYER_STATE_ENABLE
// #define SPLIT_MODS_ENABLE
// #define SPLIT_WPM_ENABLE
// #define SPLIT_OLED_ENABLE
#endif
