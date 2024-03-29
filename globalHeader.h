#ifndef GLOBALHEADER_H
#define GLOBALHEADER_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

extern int pixel_buffer_start;
extern int intersectionArray[2] = {
    0};  // Array to store the intersection points

extern void plot_pixel(int x, int y, short int line_color);
extern void clear_screen();
extern void swap(int *a, int *b);
extern void draw_line(int x0, int y0, int x1, int y1, short int line_color);
extern void get_intersection_between_two_linear_lines(int x0, int x1, int y0,
                                                      int y1, int x2, int x3,
                                                      int y2, int y3);
extern void get_intersection_between_linear_line_and_quadratic_curve(
    int x0, int y0, int x1, int y1, int a, int b, int c);  // Not tested

/*******************************************************************************
 * This file provides address values that exist in the DE1-SoC Computer
 ******************************************************************************/
#define BOARD "DE1-SoC"

/* Memory */
#define DDR_BASE 0x40000000
#define DDR_END 0x7FFFFFFF
#define A9_ONCHIP_BASE 0xFFFF0000
#define A9_ONCHIP_END 0xFFFFFFFF
#define SDRAM_BASE 0x00000000
#define SDRAM_END 0x03FFFFFF
#define FPGA_PIXEL_BUF_BASE 0x08000000
#define FPGA_PIXEL_BUF_END 0x0803FFFF
#define FPGA_CHAR_BASE 0x09000000
#define FPGA_CHAR_END 0x09001FFF

/* Cyclone V FPGA devices */
#define LED_BASE 0xFF200000
#define LEDR_BASE 0xFF200000
#define HEX3_HEX0_BASE 0xFF200020
#define HEX5_HEX4_BASE 0xFF200030
#define SW_BASE 0xFF200040
#define KEY_BASE 0xFF200050
#define JP1_BASE 0xFF200060
#define JP2_BASE 0xFF200070
#define PS2_BASE 0xFF200100
#define PS2_DUAL_BASE 0xFF200108
#define JTAG_UART_BASE 0xFF201000
#define IrDA_BASE 0xFF201020
#define TIMER_BASE 0xFF202000
#define TIMER_2_BASE 0xFF202020
#define AV_CONFIG_BASE 0xFF203000
#define RGB_RESAMPLER_BASE 0xFF203010
#define PIXEL_BUF_CTRL_BASE 0xFF203020
#define CHAR_BUF_CTRL_BASE 0xFF203030
#define AUDIO_BASE 0xFF203040
#define VIDEO_IN_BASE 0xFF203060
#define EDGE_DETECT_CTRL_BASE 0xFF203070
#define ADC_BASE 0xFF204000

/* Cyclone V HPS devices */
#define HPS_GPIO1_BASE 0xFF709000
#define I2C0_BASE 0xFFC04000
#define I2C1_BASE 0xFFC05000
#define I2C2_BASE 0xFFC06000
#define I2C3_BASE 0xFFC07000
#define HPS_TIMER0_BASE 0xFFC08000
#define HPS_TIMER1_BASE 0xFFC09000
#define HPS_TIMER2_BASE 0xFFD00000
#define HPS_TIMER3_BASE 0xFFD01000
#define FPGA_BRIDGE 0xFFD0501C
/***************************************************/

/*****************************************************************************/
/* Macros for accessing the control registers.                               */
/*****************************************************************************/

#define NIOS2_READ_STATUS(dest) \
  do {                          \
    dest = __builtin_rdctl(0);  \
  } while (0)

#define NIOS2_WRITE_STATUS(src) \
  do {                          \
    __builtin_wrctl(0, src);    \
  } while (0)

#define NIOS2_READ_ESTATUS(dest) \
  do {                           \
    dest = __builtin_rdctl(1);   \
  } while (0)

#define NIOS2_READ_BSTATUS(dest) \
  do {                           \
    dest = __builtin_rdctl(2);   \
  } while (0)

#define NIOS2_READ_IENABLE(dest) \
  do {                           \
    dest = __builtin_rdctl(3);   \
  } while (0)

#define NIOS2_WRITE_IENABLE(src) \
  do {                           \
    __builtin_wrctl(3, src);     \
  } while (0)

#define NIOS2_READ_IPENDING(dest) \
  do {                            \
    dest = __builtin_rdctl(4);    \
  } while (0)

#define NIOS2_READ_CPUID(dest) \
  do {                         \
    dest = __builtin_rdctl(5); \
  } while (0)
/*************************************************************************/

/**************************PS2_keyboard**************************/
extern volatile char byte1, byte2, byte3;  // PS/2 variables

extern volatile int timeout;  // used to synchronize with the timer

extern int main(void);
extern void interrupt_handler(void);
extern void interval_timer_ISR(void);
extern void PS2_ISR(void);
/*****************************************************************/

/**************************Audio**************************/
extern void delay(int delay_time);
extern void audio_playback_mono(int *samples, int n);
extern void play_audio(); // Call this to play music for 1 loop
/*********************************************************/

#endif