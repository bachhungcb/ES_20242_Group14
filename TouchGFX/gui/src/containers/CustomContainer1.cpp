#include <gui/containers/CustomContainer1.hpp>

#include <touchgfx/Color.hpp> // Có thể cần nếu bạn dùng màu
#include <touchgfx/widgets/canvas/Line.hpp> // Có thể cần nếu bạn dùng Line
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>

using namespace touchgfx;
CustomContainer1::CustomContainer1()
{
	setWidth(240);
	setHeight(320);
	add(line);

	line.setStart(15, 15); // Bắt đầu tại (50, 50)
	line.setEnd(70, 10); // Kết thúc tại (200, 150)
	line.setLineWidth(15);  // Độ dày của đường thẳng là 5 pixel

	static PainterRGB565 linePainter; // Khai báo static để tránh tạo lại mỗi lần
	linePainter.setColor(Color::getColorFromRGB(0, 0, 255)); // Màu xanh dương
	line.setPainter(linePainter);

	// Thiết lập kiểu kết thúc đường thẳng (tùy chọn)
	line.setLineEndingStyle(Line::ROUND_CAP_ENDING); // Đầu tròn

	invalidate();
}

void CustomContainer1::draw(const touchgfx::Rect& invalidatedArea) const
{
    // Gọi hàm draw của lớp cha để đảm bảo nó vẫn vẽ nền container
    Container::draw(invalidatedArea);

    line.draw(invalidatedArea);

}

void CustomContainer1::initialize()
{
    CustomContainer1Base::initialize();
}
