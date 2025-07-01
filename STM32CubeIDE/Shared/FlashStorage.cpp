/*
 * FlashStorage.cpp
 *
 *  Created on: Jul 1, 2025
 *      Author: phuon
 */

#include "FlashStorage.h"
#include "stm32f4xx_hal.h"

#define FLASH_SECTOR_USED      FLASH_SECTOR_11
#define FLASH_ADDR_BASE        0x081E0000
#define VOLTAGE_RANGE          VOLTAGE_RANGE_3
#define MAX_PATTERN_LENGTH     50

void Flash_Write_Pattern(const int* data, uint8_t length) {
    HAL_FLASH_Unlock();

    // Xoá sector
    FLASH_Erase_Sector(FLASH_SECTOR_USED, VOLTAGE_RANGE);

    // Ghi từng phần tử
    for (uint32_t i = 0; i < length; i++) {
        HAL_FLASH_Program(TYPEPROGRAM_WORD, FLASH_ADDR_BASE + i * 4, data[i]);
    }

    // Ghi độ dài cuối cùng
    HAL_FLASH_Program(TYPEPROGRAM_WORD, FLASH_ADDR_BASE + MAX_PATTERN_LENGTH * 4, length);

    HAL_FLASH_Lock();
}

void Flash_Read_Pattern(int* data, uint8_t* length) {
    *length = *(uint32_t*)(FLASH_ADDR_BASE + MAX_PATTERN_LENGTH * 4);
    if (*length > MAX_PATTERN_LENGTH) *length = MAX_PATTERN_LENGTH;
    for (uint32_t i = 0; i < *length; i++) {
        data[i] = *(int*)(FLASH_ADDR_BASE + i * 4);
    }
}

void Flash_Erase_PatternStorage(void) {
    HAL_FLASH_Unlock();
    FLASH_Erase_Sector(FLASH_SECTOR_USED, VOLTAGE_RANGE);
    HAL_FLASH_Lock();
}
