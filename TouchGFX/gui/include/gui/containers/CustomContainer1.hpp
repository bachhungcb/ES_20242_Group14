#ifndef CUSTOMCONTAINER1_HPP
#define CUSTOMCONTAINER1_HPP

#include <gui_generated/containers/CustomContainer1Base.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/canvas/Line.hpp>
#include <touchgfx/hal/Types.hpp>
#include <vector>

using namespace std;
using namespace touchgfx;

class CustomContainer1 : public CustomContainer1Base
{
public:
    CustomContainer1();
    virtual ~CustomContainer1() {}

    virtual void initialize();
    void setDotCoordinates(const vector<Point>& coords) {
	   dotCoordinates = coords;
    }

    void setPattern(const std::vector<int>& pattern, Point currentTouchPos = Point(static_cast<int32_t>(-1), static_cast<int32_t>(-1)));
    virtual void draw(const touchgfx::Rect& invalidatedArea) const;
protected:
   	   vector<Point> dotCoordinates; // Tọa độ trung tâm của các chấm
       vector<int> currentPattern; // Các ID chấm đã chọn
       Point lastTouchPosition; // Vị trí chạm cuối cùng (để vẽ đường tạm thời)
       bool drawingInProgress; // Cờ báo hiệu đang trong quá trình vẽ

       Line line; // Sử dụng một đối tượng Line để vẽ

       // Hàm helper để lấy tọa độ của một chấm theo ID
       Point getDotCenter(int dotId) const;
};

#endif // CUSTOMCONTAINER1_HPP
