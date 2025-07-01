/*
 * FlashStorage.h
 *
 *  Created on: Jun 27, 2025
 *      Author: phuon
 */

#ifndef FLASH_STORAGE_H
#define FLASH_STORAGE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void Flash_Write_Pattern(const int* data, uint8_t length);
void Flash_Read_Pattern(int* data, uint8_t* length);
void Flash_Erase_PatternStorage(void);

#ifdef __cplusplus
}
#endif

#endif /* FLASHSTORAGE_H_ */
