#ifndef MAINSCREENVIEW_HPP
#define MAINSCREENVIEW_HPP

#include <gui_generated/mainscreen_screen/MainScreenViewBase.hpp>
#include <gui/mainscreen_screen/MainScreenPresenter.hpp>



class MainScreenView : public MainScreenViewBase
{
public:
    MainScreenView();
    virtual ~MainScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();

    virtual void dot1Selected();
    virtual void dot2Selected();
    virtual void dot3Selected();
    virtual void dot4Selected();
    virtual void dot5Selected();
    virtual void dot6Selected();
    virtual void dot7Selected();
    virtual void dot8Selected();
    virtual void dot9Selected();

    virtual void confirmPattern();

    virtual void addDot(int dotNumber);
    virtual void clearConnectedDot();
    virtual void deletePattern();

    virtual void sucessIden();
    virtual void falseIden();
protected:
};

#endif // MAINSCREENVIEW_HPP
