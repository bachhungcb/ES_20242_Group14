#include "PatternManager.hpp"
#include <string.h> // Cho memcpy
extern "C"{
	#include "FlashStorage.h"
}
// Khởi tạo instance tĩnh duy nhất
PatternManager& PatternManager::getInstance()
{
    static PatternManager instance; // Được khởi tạo lần đầu khi được gọi
    return instance;
}

const int* PatternManager::getReferencePattern() const
{
    return referencePattern;
}

uint8_t PatternManager::getReferencePatternLength() const
{
    return currentPatternLength;
}

void PatternManager::setReferencePattern(const int* newPattern, uint8_t length)
{
    if (length <= MAX_PATTERN_LENGTH) {
        memcpy(referencePattern, newPattern, length * sizeof(int));
        currentPatternLength = length;
        Flash_Write_Pattern(referencePattern, currentPatternLength);
    } else {
        // Xử lý lỗi nếu pattern quá dài
        // Ví dụ: in ra debug message hoặc không làm gì cả
    }
}

void PatternManager::loadPattern()
{
	Flash_Read_Pattern(referencePattern, &currentPatternLength);
}

void PatternManager::clearReferencePattern()
{
    currentPatternLength = 0;
    Flash_Erase_PatternStorage();
    // Tùy chọn: memset(referencePattern, 0, sizeof(referencePattern));
}
