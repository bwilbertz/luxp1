/*
 * (c) 2019 B. Wilbertz
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */

#ifndef JSONFORMATTER_H_
#define JSONFORMATTER_H_

#include <ArduinoJson.h>

#define JLEN 2048

class JsonFormatter {
public:
	JsonFormatter() :
			doc() {
	}
	;
	virtual ~JsonFormatter() {
	}
	;

	bool formatP1DataAsJson(char* json, const char* p1data);

	bool addDeviceInfoToJson(char* json, const String& deviceId,
			unsigned long uptime, uint16_t vcc, unsigned int frame_number,
			unsigned int broken_frame_counter);

private:
	StaticJsonDocument<JLEN> doc;

	String fixString(String str);
};

#endif /* JSONFORMATTER_H_ */
