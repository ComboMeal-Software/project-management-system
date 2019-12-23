#include "NotificationStruct.h"

Notification::Notification(nType ty, std::string txt, std::string sdr, std::string prj) {

	type = ty;
	text = txt;
	sender = sdr;
	project = prj;

}