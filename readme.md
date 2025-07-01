# Hệ Thống An Ninh Kiểm Tra Mật Khẩu Đơn Giản
## Simple Security Password Verification System

Dự án hệ thống an ninh sử dụng STM32F429I Discovery Kit và TouchGFX GUI Framework để tạo ra một hệ thống xác thực mật khẩu dựa trên pattern (mẫu hình).

---

## 📋 Tổng Quan Dự Án

Đây là một hệ thống an ninh đơn giản được phát triển trên kit STM32F429I Discovery, sử dụng TouchGFX để tạo giao diện người dùng trực quan. Hệ thống cho phép người dùng đặt và xác minh mật khẩu thông qua việc chọn một chuỗi các chấm theo một pattern nhất định.

### ✨ Tính Năng Chính

- **Giao diện cảm ứng trực quan** với TouchGFX GUI Framework
- **Xác thực pattern** - người dùng tạo mật khẩu bằng cách chọn chuỗi 9 chấm
- **Phản hồi LED**: 
  - LED xanh (GPIO_PIN_13): Xác thực thành công
  - LED đỏ (GPIO_PIN_14): Xác thực thất bại
- **Hệ thống khóa bảo mật**: Khóa 30 giây sau 5 lần nhập sai
- **Quản lý pattern động** với PatternManager class
- **Nhiều màn hình**:
  - HomeScreen: Màn hình chính
  - MainScreen: Xác thực mật khẩu
  - CustomScreen: Đăng ký pattern mới

### 🎯 Cách Thức Hoạt Động

1. **Đăng ký Pattern**: Người dùng tạo pattern mới bằng cách chọn chuỗi các chấm trên lưới 3x3
2. **Xác thực**: Nhập pattern đã đăng ký để mở khóa hệ thống
3. **Phản hồi**: LED xanh/đỏ hiển thị kết quả xác thực
4. **Bảo mật**: Hệ thống khóa tạm thời sau nhiều lần thử sai

---

## 🛠️ Thông Số Kỹ Thuật

### Hardware Requirements
- **Vi điều khiển**: STM32F429ZIT6
- **Kit phát triển**: STM32F429I Discovery Board (Rev D01)
- **Màn hình**: LCD TFT 2.4" (320x240 pixels, 16bpp)
- **Cảm ứng**: Touch screen capacitive
- **LEDs**: 
  - PG13: LED xanh (xác thực thành công)
  - PG14: LED đỏ (xác thực thất bại)

### Software Requirements
- **IDE**: STM32CubeIDE (khuyến nghị) hoặc IAR EWARM/MDK-ARM
- **Framework**: TouchGFX Designer 4.x
- **HAL Library**: STM32F4xx HAL Driver
- **RTOS**: FreeRTOS
- **Compiler**: GCC ARM hoặc IAR/Keil

### Cấu Hình Pin
```
GPIO Configuration:
- PG13: LED xanh (GPIO_MODE_OUTPUT_PP)
- PG14: LED đỏ (GPIO_MODE_OUTPUT_PP)
- PE2: VSYNC_FREQ (Performance monitoring)
- PE3: RENDER_TIME (Performance monitoring)
- PE4: FRAME_RATE (Performance monitoring)
- PE5: MCU_ACTIVE (Performance monitoring)

Display Configuration:
- Resolution: 320x240 pixels
- Color Depth: 16bpp (RGB565)
- Interface: LTDC + SPI (for touch)
```

---

## 🚀 Cài Đặt và Triển Khai

### Bước 1: Chuẩn Bị Môi Trường
```bash
# Cài đặt STM32CubeIDE (khuyến nghị)
# Download từ: https://www.st.com/en/development-tools/stm32cubeide.html

# Cài đặt STM32CubeProgrammer
# Download từ: https://www.st.com/en/development-tools/stm32cubeprog.html

# Cài đặt TouchGFX Designer
# Download từ: https://www.st.com/en/development-tools/touchgfxdesigner.html
```

### Bước 2: Clone và Mở Project
```bash
# Clone repository
git clone <repository-url>
cd ES_20242_Group14

# Mở project trong STM32CubeIDE
# File -> Open Projects from File System -> Chọn thư mục dự án
```

### Bước 3: Cấu Hình Project

#### 3.1 STM32CubeIDE Configuration
1. Mở file `STM32F429I_DISCO_REV_D01.ioc` với STM32CubeMX
2. Kiểm tra cấu hình clock: 
   - System Clock: 180 MHz
   - AHB Clock: 180 MHz
   - APB1 Clock: 45 MHz
   - APB2 Clock: 90 MHz
3. Cấu hình GPIO pins theo bảng trên
4. Enable LTDC và FMC interfaces
5. Generate code

#### 3.2 TouchGFX Configuration
```bash
# Mở TouchGFX Designer
# File -> Open -> Chọn file FInalProject1.touchgfx

# Kiểm tra cấu hình:
# - Target: STM32F429I-DISCO
# - Display: 320x240, 16bpp
# - Platform: FreeRTOS
```

### Bước 4: Build và Flash

#### 4.1 Build Project
```bash
# Trong STM32CubeIDE:
# Project -> Build Project (Ctrl+B)
# Hoặc sử dụng command line:
cd STM32CubeIDE
make -j8
```

#### 4.2 Flash Hardware
```bash
# Kết nối STM32F429I Discovery qua USB ST-Link
# Trong STM32CubeIDE:
# Run -> Run As -> STM32 C/C++ Application

# Hoặc sử dụng STM32CubeProgrammer:
STM32_Programmer_CLI -c port=SWD -w STM32F429I_DISCO_REV_D01.hex -v -rst
```

#### 4.3 Debug và Monitor
```bash
# Performance monitoring (tùy chọn):
# Kết nối oscilloscope đến các pins PE2-PE5 để monitor performance

# Serial debug (tùy chọn):
# Kết nối UART để xem debug output
```

---

## 💡 Hướng Dẫn Sử Dụng

### Khởi Động Hệ Thống
1. Power on STM32F429I Discovery board
2. Hệ thống sẽ khởi động và hiển thị HomeScreen
3. Touch "START" để vào MainScreen

### Đăng Ký Pattern Mới
1. Từ MainScreen, touch nút "REGISTER"
2. Chuyển sang CustomScreen
3. Touch các chấm theo thứ tự mong muốn (tối đa 9 chấm)
4. Touch "CONFIRM" để lưu pattern
5. LED đỏ sẽ nhấp nháy xác nhận

### Xác Thực Pattern
1. Ở MainScreen, touch các chấm theo pattern đã đăng ký
2. Touch "CONFIRM" để xác thực
3. **Thành công**: LED xanh sáng
4. **Thất bại**: LED đỏ sáng, số lần thử giảm
5. **Hết lượt thử**: Hệ thống khóa 30 giây

### Reset Pattern
1. Touch nút "DELETE" để xóa pattern hiện tại
2. Cả hai LED sẽ tắt

---

## 📁 Cấu Trúc Dự Án

```
ES_20242_Group14/
├── Core/                          # STM32 HAL và system files
│   ├── Inc/                       # Header files
│   └── Src/                       # Source files
├── Drivers/                       # STM32 HAL drivers
├── TouchGFX/                      # TouchGFX framework files
│   ├── App/                       # TouchGFX application
│   ├── gui/                       # GUI source code
│   │   ├── include/gui/           # GUI headers
│   │   └── src/                   # GUI implementation
│   ├── generated/                 # Auto-generated TouchGFX code
│   └── target/                    # Target-specific implementations
├── Shared/                        # Shared components
│   ├── PatternManager.hpp         # Pattern management class
│   └── PatternManager.cpp
├── STM32CubeIDE/                  # STM32CubeIDE project files
├── MDK-ARM/                       # Keil µVision project files
├── EWARM/                         # IAR EWARM project files
└── README.md                      # Documentation file
```

### Key Source Files
- `MainScreenView.cpp`: Logic xác thực pattern chính
- `CustomScreenView.cpp`: Logic đăng ký pattern mới
- `PatternManager.cpp`: Quản lý lưu trữ và so sánh pattern
- `TouchGFXGPIO.cpp`: GPIO control cho performance monitoring

---

## 🔧 API Reference

### PatternManager Class
```cpp
class PatternManager {
public:
    static PatternManager& getInstance();
    const int* getReferencePattern() const;
    uint8_t getReferencePatternLength() const;
    void setReferencePattern(const int* newPattern, uint8_t length);
    void clearReferencePattern();
};
```

### MainScreenView Class
```cpp
class MainScreenView : public MainScreenViewBase {
public:
    virtual void dot1Selected() through dot9Selected();
    virtual void confirmPattern();
    virtual void deletePattern();
    void sucessIden();        // Successful authentication
    void falseIden();         // Failed authentication
};
```

### Security Features
- **Maximum attempts**: 5 lần thử
- **Lock duration**: 30 giây (1800 ticks)
- **Pattern length**: 1-9 chấm
- **Pattern validation**: Real-time với LED feedback

---


## 👥 Đội Ngũ Phát Triển

| Tên | MSSV | Vai Trò | Email |
|-----|------|---------|-------|
| **Đàm Thanh Bách** | 20225600 | Team Leader, Backend Development | dam.tb225600@sis.hust.edu.vn |
| **Nguyễn Bình An** | 20225591 | Frontend Development, TouchGFX GUI | nguyen.ba225591@sis.hust.edu.vn |
| **Đỗ Mạnh Phương** | 20225660 | Hardware Integration, Testing | do.mp225660@sis.hust.edu.vn |
| **Lê Thị Ngọc Thảo** | 20225673 | Documentation, UI/UX Design | le.tnt225673@sis.hust.edu.vn |

### Phân Công Công Việc
- **Đàm Thanh Bách**: PatternManager class, Authentication logic, Security features
- **Nguyễn Bình An**: TouchGFX GUI design, Screen transitions, User interactions
- **Đỗ Mạnh Phương**: GPIO configuration, LED control, Hardware debugging
- **Lê Thị Ngọc Thảo**: UI design, Documentation, User experience testing

---

## 📄 License và Copyright

```
MIT License

Copyright (c) 2024 ES_20242_Group14

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

---

## 🔗 Tài Liệu Tham Khảo

### STM32 Resources
- [STM32F429I Discovery User Manual](https://www.st.com/resource/en/user_manual/um1670-discovery-kit-with-stm32f429zi-mcu-stmicroelectronics.pdf)
- [STM32F4xx HAL Driver Documentation](https://www.st.com/resource/en/user_manual/um1725-description-of-stm32f4-hal-and-lowlayer-drivers-stmicroelectronics.pdf)
- [STM32CubeIDE User Guide](https://www.st.com/resource/en/user_manual/um2609-stm32cubeide-user-guide-stmicroelectronics.pdf)

### TouchGFX Resources
- [TouchGFX Documentation](https://touchgfx.zendesk.com/hc/en-us)
- [TouchGFX Designer User Guide](https://touchgfx.zendesk.com/hc/en-us/articles/207300425-TouchGFX-Designer-User-Guide)
- [TouchGFX Development on STM32](https://www.st.com/content/st_com/en/ecosystems/touchgfx.html)

### Development Tools
- [STM32CubeMX](https://www.st.com/en/development-tools/stm32cubemx.html)
- [STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html)
- [TouchGFX Designer](https://www.st.com/en/development-tools/touchgfxdesigner.html)

---

## 📞 Liên Hệ và Hỗ Trợ

- **Repository**: [GitHub Repository Link]
- **Issues**: [GitHub Issues Link]
- **Email hỗ trợ**: es20242.group14@gmail.com

### Báo Cáo Lỗi (Bug Reports)
Khi báo cáo lỗi, vui lòng bao gồm:
1. Mô tả chi tiết lỗi
2. Các bước tái tạo lỗi
3. Screenshots/videos nếu có
4. Thông tin về hardware và software version
5. Log files hoặc debug output

### Đóng Góp (Contributing)
Chúng tôi hoan nghênh mọi đóng góp! Vui lòng:
1. Fork repository
2. Tạo feature branch
3. Commit changes với message rõ ràng
4. Submit pull request

---

**Ngày cập nhật**: Tháng 7, 2025  
**Phiên bản**: v1.0.0  
**Trạng thái**: Production Ready ✅
 