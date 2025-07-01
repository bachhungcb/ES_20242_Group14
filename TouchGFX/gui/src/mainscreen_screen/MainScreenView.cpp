#include <gui/mainscreen_screen/MainScreenView.hpp>
#include "BitmapDatabase.hpp"
#include <touchgfx/Color.hpp>

#include "../../../../../ES_20242/STM32CubeIDE/Shared/PatternManager.hpp" 	 //do bọn STM32CubeIDE quá ngu không thể nhận biết được đường dẫn
																				 //nên phải dùng như này bọn ngu lợn này mới nhận được
																				 //config đủ kiểu rồi nhưng bọn ngu này chúng nó nhận diện sai đường dẫn, nhầm
																				 //chúng nó thậm chí còn không phân biệt được workspace và file solution
																				 //bọn này xứng đáng bị tử hình
																				 //3 tiếng không làm gì, chỉ ngồi xem thằng CubeIDE tự động chọn đến một cái đường dẫn không có thật
																				 //và tất nhiên cái đường dẫn đấy không dùng được rồi
#include "main.h"
#include "cmsis_os.h"
#include "app_touchgfx.h"
#include "stdlib.h"
#include <cstring>
using namespace std;

#define MAX_DOTS 9 // Kích thước tối đa của pattern
int conectedDots[MAX_DOTS];
int conectedDotsCount = 0; // Biến đếm số lượng chấm đã chọn

static const uint8_t MAX_ATTEMPTS = 5;
uint8_t remainingAttempts;
Unicode::UnicodeChar attemptsBuffer[30];

const int REFERENCE_PATTERN[] = {1, 2, 3, 6, 9};
const int REFERENCE_PATTERN_LENGTH = sizeof(REFERENCE_PATTERN) / sizeof(REFERENCE_PATTERN[0]);

// Các biến dùng cho mục đích khóa màn hình
static const uint16_t LOCK_DURATION_TICKS = 30 * 60;
bool locked;
uint32_t lockedUntilTick;
uint32_t currentTick;

MainScreenView::MainScreenView()
{
	MainScreenViewBase::setupScreen();
}

void MainScreenView::setupScreen()
{
    MainScreenViewBase::setupScreen();
    remainingAttempts = MAX_ATTEMPTS;
    locked = false;
    currentTick = 0;
}

void MainScreenView::tearDownScreen()
{
    MainScreenViewBase::tearDownScreen();
}

void MainScreenView::handleTickEvent()
{
	currentTick++;

	if (locked && currentTick >= lockedUntilTick) {
	    locked = false;
	    remainingAttempts = MAX_ATTEMPTS;

	    Unicode::snprintf(attemptsBuffer, sizeof(attemptsBuffer) / sizeof(Unicode::UnicodeChar),
	                      "%d attempts remains", remainingAttempts);
	    attemptsText.setWildcard(attemptsBuffer);
	    attemptsText.invalidate();

	    lockNotice.setVisible(false); // Ẩn thông báo
	    lockNotice.invalidate();
	}
}

void MainScreenView::addDot(int dotNumber){
	if (conectedDotsCount < MAX_DOTS) {
		conectedDots[conectedDotsCount++] = dotNumber;
	}
}

void MainScreenView::clearConnectedDot() {
    conectedDotsCount = 0;
    memset(conectedDots, 0, sizeof(conectedDots));
}

void MainScreenView::sucessIden(){
	 HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_SET);
	 HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_RESET);
	 clearConnectedDot();
}
//quá ngu để tạo 1 hàm tham chiếu bên file h nên mới phải code thế này
//ide ngu như lợn
void MainScreenView::falseIden() {
    // Bật đèn đỏ báo lỗi, tắt đèn xanh
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_RESET);
    clearConnectedDot();

    if (!locked) {
        if (remainingAttempts > 0) {
            remainingAttempts--;

            if (remainingAttempts > 0) {
                Unicode::snprintf(attemptsBuffer, sizeof(attemptsBuffer) / sizeof(Unicode::UnicodeChar),
                                  "%d attempts remains", remainingAttempts);
            } else {
                // Hết lượt thử: đặt trạng thái khóa
                locked = true;
                lockedUntilTick = currentTick + LOCK_DURATION_TICKS;
                Unicode::strncpy(attemptsBuffer, "Locked for 30s", sizeof(attemptsBuffer));
            }

            attemptsText.setWildcard(attemptsBuffer);
            attemptsText.invalidate();
        }

        if (remainingAttempts == 0) {
            lockNotice.setVisible(true);  // Hiện notice nếu có
            lockNotice.invalidate();
        }
    }
}


void MainScreenView::dot1Selected(){
	addDot(1);
}

void MainScreenView::dot2Selected(){
	addDot(2);
}

void MainScreenView::dot3Selected(){
	addDot(3);
}

void MainScreenView::dot4Selected(){
	addDot(4);
}

void MainScreenView::dot5Selected(){
	addDot(5);
}

void MainScreenView::dot6Selected(){
	addDot(6);
}

void MainScreenView::dot7Selected(){
	addDot(7);
}

void MainScreenView::dot8Selected(){
	addDot(8);
}

void MainScreenView::dot9Selected(){
	addDot(9);
}

void MainScreenView::deletePattern(){
	clearConnectedDot();
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_RESET);
}


void MainScreenView::confirmPattern(){
	PatternManager& patternManager = PatternManager::getInstance();

	// Lấy pattern tham chiếu từ PatternManager
	const int* referencePattern = patternManager.getReferencePattern();
	uint8_t referencePatternLength = patternManager.getReferencePatternLength();

	 if (conectedDotsCount != referencePatternLength) {
	        // HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_RESET); // Bật LED báo lỗi (ví dụ)
		 	falseIden();
	        return;
	 }
	 if(referencePatternLength == 0 && conectedDotsCount == 0){
		 falseIden();
		 return;
	 }
	 int patternMatches = 1;
	 for (int i = 0; i < conectedDotsCount; ++i) {
		 if (conectedDots[i] != referencePattern[i]) {
			 patternMatches = 0; // Tìm thấy sự khác biệt
			 break; // Thoát vòng lặp ngay lập tức
		 }
	 }

	 if (patternMatches == 1) {
		 // Pattern khớp!
		 sucessIden();
	 } else {
		 // Pattern không khớp
		 // Ví dụ: Bật một LED khác hoặc hiển thị thông báo lỗi trên màn hình
		  falseIden();
	 }

	 clearConnectedDot();
}




