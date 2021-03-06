#include "RTSUtil.h"
#include "wMain.h"
#include "wRTSProg.h"
#include "wRTSRemove.h"
#include "wRTSConfirm.h"
#include "SysCommand.h"

wRTSConfirm::wRTSConfirm(): mWindow("RTS/Confirm")
{
	m_bkg.setParent(this);
	m_bkg.load(m_style, "bkg");
	m_icon.setParent(this);
	m_icon.load(m_style, "icon");

	char buf[128];
	sprintf(buf, "device_%d", rTSUtil.getCurrentType());
	m_channel.setParent(this);
	m_channel.load(m_style, buf);

	int num = rTSUtil.getCurrentNumber();
	sprintf(buf, "%d", num);
	m_number.setParent(this);
	m_number.load(m_style, "number");
	if (num > 1 && num < 10) {
		m_number.load(m_style, "number_1");
	} else if (num >= 10) {
		m_number.load(m_style, "number_2");
	}
	m_number.setText(buf);

	m_arrow.setParent(this);
	m_arrow.load(m_style, "arrow");
	m_gestures.setParent(this);
	m_gestures.load(m_style, "gestures");

	loadNavigation();
	gettimeofday(&led_tv, NULL);
}

wRTSConfirm::~wRTSConfirm()
{
}

void wRTSConfirm::doEvent(mEvent *e)
{
	mWindow::doEvent(e);
	if (e->type == mEvent::KeyPress) {
		if (e->wParam == KEY_M_DEL) {
			rTSUtil.setCurrentAction(rTSUtil.REMOVE);
			wRTSProg *rtsProg = new wRTSProg();
			rtsProg->show();
		} else if (e->wParam == KEY_M_CANCEL) {
			wRTSRemove *rtsRemove = new wRTSRemove();
			rtsRemove->show();
		} else if (e->wParam == KEY_M_HOME) {
			wMain *main = new wMain();
			main->show();
		}
	}
}

void wRTSConfirm::doTimer(void)
{
	mWindow::doTimer();
	if (__val(led_tv) && __ts(led_tv) > 200) {
		loadLed();
		memset(&led_tv, 0, sizeof(led_tv));
	}
}

void wRTSConfirm::loadNavigation(void)
{
	m_confirm.setParent(this);
	m_confirm.load(m_style, "confirm");
	m_cancel.setParent(this);
	m_cancel.load(m_style, "cancel");
	m_separator.setParent(this);
	m_separator.load(m_style, "separator");
	m_home.setParent(this);
	m_home.load(m_style, "home");
}

void wRTSConfirm::loadLed(void)
{
	uint8_t data[9] = {0};
	for (int i = LED1; i <= LED9; i++) {
		if (i >= LED7) {
			data[i] = LED_ON;
		} else {
			data[i] = LED_OFF;
		}
	}
	command.sendLedControl(data);
}