/*
 * (c) 2019 B. Wilbertz
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */

#include <Arduino.h>
#include <Streaming.h>

#include "JsonFormatter.h"

String JsonFormatter::fixString(String str) {
	int n = str.length();
	char temp[2];
	for (int i = 0; i < n; i += 2) {
		temp[0] = str[i];
		temp[1] = str[i + 1];
		str[i / 2] = (uint16_t) strtoul(temp, NULL, 16);
	}

	return str.substring(0, n / 2);
}

bool JsonFormatter::formatP1DataAsJson(char* json, const char* p1data) {
	String str(p1data);

	// remove header
	int idx = str.indexOf('\n');
	str = str.substring(idx + 1);
	str[0] = '{';

	// remove crc
	idx = str.lastIndexOf('!');
	str = str.substring(0, idx - 3);
	str += "\"}";

	// transform into a parseable json
	str.replace(")(", "##");
	str.replace(")\r", "\",");
	// TODO optimize next replace. Performance bottleneck
	str.reserve(str.length() + 200);
	str.replace("(", "\":\"");
	str.replace("\n", "\"");

	// remove units from fields
	str.replace("*kWh", "");
	str.replace("*kvarh", "");
	str.replace("*kW", "");
	str.replace("*A\"", "\"");
	str.replace("*m3\"", "\"");

	// fix some fields
	DeserializationError error = deserializeJson(doc, str);

	if (error) {
#ifdef DEBUG
	  Serial.println("Json deserialization failed.");
	  Serial.println(str);
#endif

		return false;
	}

	char* strFields[] = { "1-3:0.2.0", "1-3:0.2.8", "0-0:42.0.0", "0-0:96.1.1",
			"0-0:96.1.0", "0-0:96.13.0", "0-0:96.14.0", "0-1:96.1.0",
			"0-2:96.1.0" };
	for (int i = 0; i < 9; i++) {
		if (doc.containsKey(strFields[i])) {
			doc[strFields[i]] = fixString(doc[strFields[i]]);
		}
	}

	// TODO fix log fields (containing ## separator)

	const size_t bytes = serializeJson(doc, json, JLEN);

	return bytes > 0;
}

bool JsonFormatter::addDeviceInfoToJson(char* json, const String& deviceId,
		unsigned long uptime, uint16_t vcc, unsigned int frame_number,
		unsigned int broken_frame_counter) {
	// Set new fields
	doc.clear();
	doc[F("deviceId")] = deviceId;
	doc[F("uptime")] = uptime;
	doc[F("vcc")] = vcc;
	doc[F("frame_number")] = frame_number;
	doc[F("frame_errors")] = broken_frame_counter;

	// move old json into nested field
	memmove(json + 9, json, strlen(json) + 1);
	strncpy(json, "{\"frame\": ", 9);

	// append new json
	char* ptr = json + strlen(json);
	const size_t bytes = serializeJson(doc, ptr, JLEN - (ptr - json));

	// replace wrong opening bracket
	ptr[0] = ',';

	return bytes > 0;
}

