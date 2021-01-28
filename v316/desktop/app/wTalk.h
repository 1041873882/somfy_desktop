
#ifndef __W_TALK_H__
#define __W_TALK_H__

#include "mWindow.h"
#include "mButton.h"

#define MAX_CUSTOM_BTN	5

class wTalk: public mWindow {
public:
	wTalk();
	virtual ~wTalk();

	enum {
		AC_DEFAULT = 0,
		AC_EXIT    = 1,
		AC_ANSWER  = 2,
		AC_GATE    = 3,
		AC_DOOR    = 4,
		AC_CAMERA  = 5,
		AC_RTS     = 6,
		AC_END     = 7,
	};

	enum {
		LED_DEFAULT = 0,
		LED_ANSWER  = 1,
		LED_DOOR	= 2,
		LED_GATE	= 3,
		LED_CAMERA	= 4,
		LED_RTS		= 5,
		LED_CHANNEL	= 6,
	};


	void closeOsd(void);
	void loadLed(int mode);
	void loadLedLock(int mode);
	void doEvent(mEvent *e);
	void loadNavigation(int select);
	void doTimer(void);
	int  doJpegYv21(void *yuv, int w, int h, const char *url);

	int  doCaturePicture(void);
	void doHungup(void);
	void loadActionBkg(void);
	int  sendBothMonitorMsg(int action);
private:
	mPixmap m_osd;
	mPixmap m_action_bkg;
	mPixmap m_picture;
	mPixmap m_menu_area;
	mPixmap m_camera;
	mPixmap m_arrow;
	mPixmap m_custom_func[MAX_CUSTOM_BTN];
	mButton m_custom_number[MAX_CUSTOM_BTN];
	mPixmap m_channel[MAX_CUSTOM_BTN];
	mPixmap m_select_func;
	mPixmap m_back;
private:
	int m_cvbs_w;
	int m_cvbs_h;
	struct timeval m_cvbs_tv;
	struct timeval led_tv;
	struct timeval firstUI_tv;
	struct timeval lockLed_tv;
	
	int m_cvbs;
	uint8_t *m_cvbs_mm;
	int m_cvbs_sz;

	int m_arrow_action;
	int m_led_select;
	int m_menu_select;
	int m_action;
	time_t m_actionTime;
	int m_switchState;
	int m_toorbarState;
};

#endif