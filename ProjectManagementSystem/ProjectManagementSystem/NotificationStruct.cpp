#include "NotificationStruct.h"

Notification::Notification(nType ty, std::string txt, std::string sdr, std::string rvr) {

	type = ty;
	text = txt;
	sender = sdr;
	receiver = rvr;

}