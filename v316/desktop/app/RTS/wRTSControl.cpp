#include "wMain.h"
#include "RTSUtil.h"
#include "SysCommand.h"
#include "wRTSControl.h"

wRTSControl::wRTSControl(): mWindow("RTS/Control")
{
	m_bkg.setParent(this);
	m_bkg.load(m_style, "bkg");
	m_icon.setParent(this);
	m_icon.load(m_style, "icon");

	m_time_area.setParent(this);
	m_time_area.load(m_style, "time_area");
	m_time.setParent(this);
	m_time.load(m_style, "time");
	m_date.setParent(this);
	m_date.load(m_style, "date");

	m_minutes = -1;
	loadTime();
	loadNavigation();
	gettimeofday(&led_tv, NULL);
}

wRTSControl::~wRTSControl()
{
}

void wRTSControl::doEvent(mEvent *e)
{
	mWindow::doEvent(e);
	if (e->type == mEvent::KeyPress) {
		int channel_id = rTSUtil.getSelectedChnId();
		if (e->wParam == KEY_M_ACT_UP) {
			command.sendSwitchControl(channel_id+1, 1);
		} else if(e->wParam == KEY_M_ACT_STOP) {
			command.sendSwitchControl(channel_id+1, 2);
		} else if (e->wParam == KEY_M_ACT_DOWN) {
			command.sendSwitchControl(channel_id+1, 3);
		} else if (e->wParam == KEY_M_HOME) {
			wMain *main = new wMain();
			main->show();
		}
	}
}

void wRTSControl::doTimer()
{
	mWindow::doTimer();
	loadTime();
	if (__val(led_tv) && __ts(led_tv) > 200) {
		loadLed();
		memset(&led_tv, 0, sizeof(led_tv));
	}
}

void wRTSControl::loadTime(void)
{
	time_t now = time(NULL);
	struct tm *tm = localtime(&now);
	if (m_minutes != tm->tm_min) {
		m_minutes = tm->tm_min;
		char timeBuf[32];
		sprintf(timeBuf, "%02d:%02d", tm->tm_hour, tm->tm_min);
		m_time.setText(timeBuf);
		sprintf(timeBuf, "%02d/%02d/%d", tm->tm_mday, tm->tm_mon+1, tm->tm_year+1900);
		m_date.setText(timeBuf);
	}
}

void wRTSControl::loadNavigation(void)
{
	m_menu_area.setParent(this);
	m_menu_area.load(m_style, "menu_area");
	char buf[128];
	int select_channel = rTSUtil.getSelectedChnId();
	for (int i = 0; i < CTRL_CHN_MAX; i++) {
		sprintf(buf, "channel_%d", i+1);
		m_channel[i].setParent(this);
		m_channel[i].load(m_style, buf);
		if (select_channel == i) {
			sprintf(buf, "device_%d", rTSUtil.getChannelType(i));
		} else {
			sprintf(buf, "device_%d_1", rTSUtil.getChannelType(i));
		}
		m_channel[i].loadUrl(m_style, buf);
	}
	m_select_func.setParent(this);
	m_select_func.load(m_style, "select_func");
	sprintf(buf, "device_%d_2", rTSUtil.getChannelType(select_channel));
	m_select_func.loadUrl(m_style, buf);
	m_up.setParent(this);
	m_up.load(m_style, "up");
	m_stop.setParent(this);
	m_stop.load(m_style, "stop");
	m_down.setParent(this);
	m_down.load(m_style, "down");
	m_separator.setParent(this);
	m_separator.load(m_style, "separator");
	m_home.setParent(this);
	m_home.load(m_style, "home");
}

void wRTSControl::loadLed(void)
{
	uint8_t data[9] = {0};
	for (int i = LED1; i <= LED9; i++) {
		if (i > LED5) {
			data[i] = LED_ON;
		} else {
			data[i] = LED_OFF;
		}
	}
	command.sendLedControl(data);
}
