#ifndef PATTERN_MANAGER_HPP
#define PATTERN_MANAGER_HPP

#include <cstdint> // Để sử dụng int16_t, uint8_t, v.v.

// Định nghĩa kích thước tối đa của pattern
#define MAX_PATTERN_LENGTH 9

class PatternManager
{
public:
    // Lấy instance duy nhất của PatternManager (Singleton pattern)
    static PatternManager& getInstance();

    // Lấy pattern tham chiếu (pattern đã lưu)
    const int* getReferencePattern() const;
    uint8_t getReferencePatternLength() const;

    // Thiết lập pattern tham chiếu mới (cho màn hình đăng ký)
    void setReferencePattern(const int* newPattern, uint8_t length);

    // Xóa pattern hiện tại
    void clearReferencePattern();

private:
    // Private constructor để ngăn tạo đối tượng từ bên ngoài (Singleton)
    PatternManager() {}
    // Ngăn copy constructor và assignment operator
    PatternManager(const PatternManager&) = delete;
    PatternManager& operator=(const PatternManager&) = delete;

    int referencePattern[MAX_PATTERN_LENGTH];
    uint8_t currentPatternLength = 0;
};

#endif // PATTERN_MANAGER_HPP