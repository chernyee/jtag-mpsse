/* Copyright 2014 Brian Swetland <swetland@frotz.net>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _JTAG_H_
#define _JTAG_H_

#include <stdint.h>

#define ONE_HUNDRED_KHZ 100000
#define FOUR_HUNDRED_KHZ 400000
#define ONE_MHZ 1000000
#define TWO_MHZ 2000000
#define THREE_MHZ 3000000
#define FIVE_MHZ 5000000
#define SIX_MHZ 6000000
#define TEN_MHZ 10000000
#define TWELVE_MHZ 12000000
#define THIRTY_MHZ 30000000
#define SIXTY_MHZ 60000000

#define MOVE_NONE		0,0
#define MOVE_ANY_TO_RESET_IDLE	8,0b01111111
#define MOVE_IDLE_TO_SHIFTDR	3,0b001
#define MOVE_IDLE_TO_SHIFTIR	4,0b0011
#define MOVE_IDLE_TO_CAPTUREDR	2,0b01
#define MOVE_CAPTUREDR_TO_SHIFTDR	1,0b0
#define MOVE_SHIFTDR_TO_UPDATEDR	2,0b11
#define MOVE_UPDATEDR_TO_IDLE	1,0b0
#define MOVE_SHIFTxR_TO_IDLE	3,0b011

#define MSB 1
#define LSB 0

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef struct jtag_handle JTAG;

JTAG *jtag_open(u32 vid, u32 pid, char *sn, u32 iface, u32 endianness);
void jtag_close(JTAG *jtag);

int jtag_enumerate(JTAG *jtag);
u32 jtag_get_nth_idcode(JTAG *jtag, u32 n);
int jtag_select(JTAG *jtag, u32 idcode);

int jtag_ir_wr(JTAG *jtag, u32 ir);
int jtag_dr_io(JTAG *jtag, u32 bitcount, u64 wdata, u64 *rdata);

int jtag_move(JTAG *jtag, int count, unsigned bits);
int _jtag_shift(JTAG *jtag, int count, u64 bits, u64 *out, int movecount, unsigned movebits);

int jtag_gpio_set_direction_and_state(JTAG *jtag, u16 direction, u16 state);
int jtag_gpio_write(JTAG *jtag, u16 pins, u16 state);
int jtag_set_clock_freq(JTAG *jtag, u32 freq);
int jtag_purge_rx_buffer(JTAG *jtag);
int jtag_set_endianness(JTAG *jtag, u32 endianness);
u32 jtag_get_endianness(JTAG *jtag);
u32 jtag_get_clock_freq(JTAG *jtag);

int spi_set_cs_pinmask(JTAG *jtag, u16 pinmask);
int spi_start(JTAG *jtag);
int spi_stop(JTAG *jtag);
int spi_write(JTAG *jtag, char *data, int nbytes);
int spi_read(JTAG *jtag, char *output, int nbytes);
int spi_exchange(JTAG *jtag, char *data, char *output, int nbytes);

#endif
