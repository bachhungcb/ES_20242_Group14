#ifndef CUSTOMSCREENVIEW_HPP
#define CUSTOMSCREENVIEW_HPP

#include <gui_generated/customscreen_screen/CustomScreenViewBase.hpp>
#include <gui/customscreen_screen/CustomScreenPresenter.hpp>

class CustomScreenView : public CustomScreenViewBase
{
public:
    CustomScreenView();
    virtual ~CustomScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void dot1Selected();
	virtual void dot2Selected();
	virtual void dot3Selected();
	virtual void dot4Selected();
	virtual void dot5Selected();
	virtual void dot6Selected();
	virtual void dot7Selected();
	virtual void dot8Selected();
	virtual void dot9Selected();

    virtual void deletePatern();
    virtual void confirmNewPattern();
    virtual void addDot(int dotNumber);
    virtual void clearConnectedDot();
protected:
};

#endif // CUSTOMSCREENVIEW_HPP
