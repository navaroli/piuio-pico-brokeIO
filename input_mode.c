/**********************************************************/
/*  SPDX-License-Identifier: MIT                          */
/*  SPDX-FileCopyrightText: Copyright (c) 2023 sugoku     */
/*  https://github.com/sugoku/piuio-pico-brokeIO          */
/**********************************************************/

#include "input_mode.h"

int get_input_mode() {
    #if defined(ALWAYS_DEFAULT_INPUT_MODE)
        input_mode = DEFAULT_INPUT_MODE;
    #else
        if (input_mode < 0)
            input_mode = read_input_mode();
        
        if (input_mode >= INPUT_MODE_COUNT)
            input_mode = DEFAULT_INPUT_MODE;
    #endif

    return input_mode;
}

int get_swap_pad_lights() {
    #if defined(ALWAYS_DEFAULT_INPUT_MODE)
        swap_pad_lights = 0;
    #else
        if (swap_pad_lights < 0)
            swap_pad_lights = read_swap_pad_lights();

        if (swap_pad_lights > 1)
            swap_pad_lights = 0;
    #endif

    return swap_pad_lights;
}

// thanks to Kevin Boone for the helpful information!
// https://kevinboone.me/picoflash.html

uint8_t read_input_mode() {
    // read byte at offset in memory where XIP_BASE is flash address start
    return *(uint8_t *)(XIP_BASE + INPUT_MODE_OFFSET);
}

uint8_t read_swap_pad_lights() {
    return *(uint8_t *)(XIP_BASE + INPUT_MODE_OFFSET + 1);
}

void write_input_mode(uint8_t input_mode_value, uint8_t swap_pad_lights_value) {
    #ifndef ALWAYS_DEFAULT_INPUT_MODE
    // at minimum we have to write FLASH_PAGE_SIZE bytes (256)
    // this sets the first value in the array and the rest should be 0
    uint8_t buf[FLASH_PAGE_SIZE] = {input_mode_value, swap_pad_lights_value};

    // disabling interrupts is required before writing to flash!
    uint32_t ints = save_and_disable_interrupts();

    // we erase the sector before we write to it
    flash_range_erase(INPUT_MODE_OFFSET, FLASH_SECTOR_SIZE);
    flash_range_program(INPUT_MODE_OFFSET, buf, FLASH_PAGE_SIZE);

    // we can restore interrupts afterwards
    restore_interrupts(ints);
    #endif
};