/**********************************************************/
/*  SPDX-License-Identifier: MIT                          */
/*  SPDX-FileCopyrightText: Copyright (c) 2023 sugoku     */
/*  https://github.com/sugoku/piuio-pico-brokeIO          */
/**********************************************************/

#ifndef _INPUT_MODE_H
#define _INPUT_MODE_H

#include "hardware/flash.h"
#include "hardware/sync.h"
#include "piuio_config.h"

typedef struct {
    // The current input mode (eg: PIUIO, XInput, Switch, Gamecube, etc).
    uint8_t input_mode;

    // For ITG dedicabs; swap 1P and 2P lights in non-PIUIO modes.
    uint8_t swap_pad_lights;
} mutable_config_t;

mutable_config_t* get_config();
void write_config(mutable_config_t* new_config);

#endif