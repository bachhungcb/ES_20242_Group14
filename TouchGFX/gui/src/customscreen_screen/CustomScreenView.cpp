#include <gui/customscreen_screen/CustomScreenView.hpp>
#include <gui/containers/CustomContainer1.hpp>
#include "../../../../../FInalProject1/STM32CubeIDE/Shared/PatternManager.hpp"

#include "main.h"
#include "cmsis_os.h"
#include "app_touchgfx.h"
#include "stdlib.h"
#include <cstring>
CustomScreenView::CustomScreenView()
{

}

#define MAX_DOTS 9 // Kích thước tối đa của pattern
int registerDots[MAX_DOTS];
int registerDotsCount = 0; // Biến đếm số lượng chấm đã chọn

void CustomScreenView::setupScreen()
{
    CustomScreenViewBase::setupScreen();

}

void CustomScreenView::tearDownScreen()
{
    CustomScreenViewBase::tearDownScreen();
}

void CustomScreenView::addDot(int dotNumber){
	if (registerDotsCount < MAX_DOTS) {
		registerDots[registerDotsCount++] = dotNumber;
	}
}

void CustomScreenView::clearConnectedDot() {
    registerDotsCount = 0;
    memset(registerDots, 0, sizeof(registerDots));
}

void CustomScreenView::dot1Selected(){
	addDot(1);
}

void CustomScreenView::dot2Selected(){
	addDot(2);
}

void CustomScreenView::dot3Selected(){
	addDot(3);
}

void CustomScreenView::dot4Selected(){
	addDot(4);
}

void CustomScreenView::dot5Selected(){
	addDot(5);
}

void CustomScreenView::dot6Selected(){
	addDot(6);
}

void CustomScreenView::dot7Selected(){
	addDot(7);
}

void CustomScreenView::dot8Selected(){
	addDot(8);
}

void CustomScreenView::dot9Selected(){
	addDot(9);
}


void CustomScreenView::deletePatern(){
	clearConnectedDot();
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_RESET);
}

void CustomScreenView::confirmNewPattern(){
		// Lấy instance duy nhất của PatternManager
	    PatternManager& patternManager = PatternManager::getInstance();

	    // Lưu pattern mới từ registerDots vào PatternManager
	    patternManager.setReferencePattern(registerDots, registerDotsCount);

	    // Sau khi lưu, bạn có thể muốn:
	    // 1. Xóa pattern tạm thời trên màn hình đăng ký
	    clearConnectedDot();

	    // 2. Cung cấp phản hồi cho người dùng (ví dụ: hiển thị thông báo "Lưu thành công!")
	    //    Nếu bạn có một TextAre hoặc Image trên UI để hiển thị thông báo, bạn có thể cập nhật nó ở đây.
	    //    Ví dụ: successMessageText.setAlpha(255); successMessageText.invalidate();

	    // 3. Chuyển về màn hình chính hoặc màn hình khác
	    //    Để chuyển màn hình, bạn sẽ gọi một hàm trong Presenter của CustomScreenView
	    //    hoặc trực tiếp thông qua đối tượng Application nếu CustomScreenView được cấp quyền truy cập.
	    //    Ví dụ (giả sử có presenter và hàm tương ứng):
	    //    presenter->gotoMainScreen();
	    //    Hoặc thông qua Application (nếu bạn có thể truy cập):
	    //    application().gotoMainScreenScreenNoTransition(); // Cần khai báo application() và hàm trong Application.hpp

	    // Tùy chọn: báo hiệu thành công bằng LED
	    HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_14);
}

