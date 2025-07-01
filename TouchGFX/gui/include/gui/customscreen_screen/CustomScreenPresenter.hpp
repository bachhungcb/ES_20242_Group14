#ifndef CUSTOMSCREENPRESENTER_HPP
#define CUSTOMSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class CustomScreenView;

class CustomScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    CustomScreenPresenter(CustomScreenView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~CustomScreenPresenter() {}

private:
    CustomScreenPresenter();

    CustomScreenView& view;
};

#endif // CUSTOMSCREENPRESENTER_HPP
