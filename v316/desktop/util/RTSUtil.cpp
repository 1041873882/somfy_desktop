#include "RTSUtil.h"

#define  SYS_FILE_PATH   "/dnake/data"
#define  SAVE_FILE_NAME  "RTSSetting.xml"

RTSUtil rTSUtil;
RTSUtil::RTSUtil()
{
	for (int i = 0; i < CHANNEL_MAX; i++) {
		RTSchannels[i].type = TYPE_DEFAULT;
	}
}

RTSUtil::~RTSUtil()
{
}

void RTSUtil::add(int channel, int type)
{
	RTSchannels[channel].number++;
	RTSchannels[channel].type = type;
}

void RTSUtil::remove(int channel)
{
	RTSchannels[channel].number = RTSchannels[channel].type = TYPE_DEFAULT;
}

void RTSUtil::setSelectedChnId(int id)
{
	selectedChnId = id;
}

int RTSUtil::getSelectedChnId()
{
	return selectedChnId;
}

void RTSUtil::setCurrentNumber(int num)
{
	currentNumber = num;
}

int RTSUtil::getCurrentNumber()
{
	return currentNumber;
}

void RTSUtil::setCurrentType(int type)
{
	currentType = type;
}

int RTSUtil::getCurrentType()
{
	return currentType;
}

int RTSUtil::getChannelType(int channel)
{
	if (channel < 0 || channel >= CHANNEL_MAX) {
		return TYPE_DEFAULT;
	}
	return RTSchannels[channel].type;
}

int RTSUtil::getChannelNumber(int num)
{
	if (num < 0 || num >= CHANNEL_MAX) {
		return TYPE_DEFAULT;
	}
	return RTSchannels[num].number;
}

void RTSUtil::setCurrentAction(int action)
{
	currentAction = action;
}

int RTSUtil::getCurrentAction()
{
	return currentAction;
}

const char *RTSUtil::dir()
{
	return SYS_FILE_PATH;
}

void RTSUtil::load()
{
	dxml p;
	char s[128];
	sprintf(s, "%s/%s", dir(), SAVE_FILE_NAME);
	p.loadFile(s);
	for (int i = 0; i < CHANNEL_MAX; i++) {
		sprintf(s, "/rts/chn_%d/type", i+1);
		RTSchannels[i].type = p.getInt(s, 0);
		sprintf(s, "/rts/chn_%d/num", i+1);
		RTSchannels[i].number = p.getInt(s, 0);
	}
	setCurrentType(p.getInt("/current/type", 1));
}

void RTSUtil::save()
{
	char s[128];
	dxml p;
	for (int i = 0; i < CHANNEL_MAX; i++) {
		sprintf(s, "/rts/chn_%d/type", i+1);
		p.setInt(s, RTSchannels[i].type);
		sprintf(s, "/rts/chn_%d/num", i+1);
		p.setInt(s, RTSchannels[i].number);
	}
	p.setInt("/current/type", getCurrentType());
	sprintf(s, "%s/%s", dir(), SAVE_FILE_NAME);
	p.saveFile(s);
	system("sync");
}

void RTSUtil::reset()
{
	char s[128];
	sprintf(s, "%s/%s", dir(), SAVE_FILE_NAME);
	dxml p(s);
	p.reset();
}
