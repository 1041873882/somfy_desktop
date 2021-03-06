
#ifndef __W_SETUP_H__
#define __W_SETUP_H__

#include "mWindow.h"
#include "mButton.h"

#define MAX_SET_BTN			10
#define MAX_NUM_PER_LINE	5

class wSetup: public mWindow {
public:
	wSetup();
	virtual ~wSetup();

	void loadLed(void);
	void doTimer(void);
	void doEvent(mEvent *e);
	void doConfirm(void);
	void loadSetBtn(void);
	void selectChange(void);
	void loadNavigation(void);
	void doVideoSetting(int type);
	void doChange(int direction);
private:
	mPixmap m_bkg;
	mPixmap m_icon;

	mPixmap m_set_btn[MAX_SET_BTN];
	mPixmap m_select_area;

	mPixmap m_right;
	mPixmap m_left;
	mPixmap m_down;
	mPixmap m_confirm;
	mPixmap m_separator;
	mPixmap m_home;
private:
	struct timeval led_tv;
};

#endif

