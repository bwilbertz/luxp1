/*
 * (c) 2019 B. Wilbertz
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */

#include "luxp1.h"

#include <Streaming.h>

#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <PubSubClient.h>

#include "EncryptedFrame.h"
#include "Decryptor.h"
#include "JsonFormatter.h"

char FRAME[LEN];
char P1DATA[LEN];
char TELEGRAM[JLEN];

ADC_MODE(ADC_VCC);

WiFiClient wifi_client;
PubSubClient mqtt_client(wifi_client);

EncryptedFrame frame;
Decryptor cipher(key_SM);
JsonFormatter formatter;
unsigned int broken_frame_counter = 0;

void setup_wifi() {
	WiFi.mode(WIFI_STA);
	//WiFi.config(staticIP, gateway, subnet, gateway);
	WiFi.hostname("luxp1");
	WiFi.begin(SSID, PASSWORD);

	Serial.print("Connecting");
	while (WiFi.status() != WL_CONNECTED) {
		delay(50);
		Serial.print(".");
	}
	Serial.println();

	Serial.print("Connected, IP address: ");
	Serial.println(WiFi.localIP());
}

void ota_updates() {
	t_httpUpdate_return ret = ESPhttpUpdate.update(MQTT_SERVER, 80,
			"/esp/update/arduino.php", VERSION);
	switch (ret) {
	case HTTP_UPDATE_FAILED:
		Serial.printf("[update] Update failed. Error (%d): %s",
				ESPhttpUpdate.getLastError(),
				ESPhttpUpdate.getLastErrorString().c_str());
		break;
	case HTTP_UPDATE_NO_UPDATES:
		Serial.println("[update] Update no Update.");
		break;
	case HTTP_UPDATE_OK:
		Serial.println("[update] Update ok."); // may not called we reboot the ESP
		break;
	}
}

void publish(const char* msg) {
	Serial.print("Publish message: ");
	Serial.println(msg);
	mqtt_client.publish(TOPIC, msg);
	mqtt_client.loop();
}

void publish_raw(const uint8_t* payload, unsigned int len) {
	mqtt_client.publish(TOPIC_RAW, payload, len);
	mqtt_client.loop();
}

void publish_p1(const char* msg) {
	mqtt_client.publish(TOPIC_P1, msg);
	mqtt_client.loop();
}

boolean mqtt_connect() {
	return mqtt_client.connect("luxp1", LAST_WILL_TOPIC, 0, true, "offline");
}

void setup() {
	Serial.begin(115200);
	Serial.setTimeout(SERIAL_TIMEOUT);
	Serial.setRxBufferSize(LEN);
	Serial.println();

	Serial << "Version: " << VERSION << endl;

	uint16_t voltage = ESP.getVcc();

	Serial.printf("Voltage: %0.2fV\n", voltage / 1000.0f);

	setup_wifi();

#ifdef OTA_UPDATE
	ota_updates();
	delay(50);
#endif

	mqtt_client.setServer(MQTT_SERVER, 1883);
	if (!mqtt_connect()) {
		Serial << "[mqtt] connection failed, rc=" << mqtt_client.state()
				<< endl;
	} else {
		mqtt_client.loop();

		mqtt_client.publish(LAST_WILL_TOPIC, "online", true);
		mqtt_client.loop();
		yield();
		mqtt_client.publish(TOPIC_FW, VERSION, true);
		mqtt_client.loop();
		delay(10);
	}

	// consume first frame, which might be corrupted due to startup...
	Serial.readBytes(FRAME, LEN);

}

void reconnect() {
	while (!mqtt_client.connected()) {
		Serial.print("[mqtt] Reconnecting...");
		if (!mqtt_connect()) {
			Serial << "[mqtt] failed, rc=" << mqtt_client.state()
					<< " retrying in 5 seconds" << endl;
			delay(5000);
		} else {
			mqtt_client.publish(LAST_WILL_TOPIC, "online", true);
			mqtt_client.loop();
			delay(10);
		}
	}
}

void loop() {
	if (!mqtt_client.connected()) {
		reconnect();
	}
	mqtt_client.loop();

#ifndef USE_TEST_DATA
	if (Serial.available() > 0) {
		unsigned int len = Serial.readBytes(FRAME, LEN);
#else
	{
		delay(10000); //wait for 10 sec
		unsigned int len = test_data_len;
		memcpy(FRAME, test_data, len);
#endif
		if (len > 0) {
			Serial << "Received " << len << " bytes of data" << endl;
			yield();
#ifdef OUTPUT_RAW
			publish_raw((const uint8_t*) FRAME, len);
#endif
			if (!frame.parseNewFrame((uint8_t*) FRAME, len)) {
				Serial << "Failed to parse frame" << endl;
				broken_frame_counter++;
				return;
			}
			yield();

			if (!cipher.decryptIntoBuffer(&frame, (uint8_t*) P1DATA)) {
				Serial << "Failed to verify signature of p1 data" << endl;
				broken_frame_counter++;
				return;
			}
			yield();

			// ensure 0 termination of data
			P1DATA[frame.getPayloadLength()] = 0;
#ifdef DEBUG
			Serial << "Decrypted data: " << P1DATA << endl;
#endif
#ifdef OUTPUT_P1
			publish_p1(P1DATA);
#endif

			// format as json and publish
			if (!formatter.formatP1DataAsJson(TELEGRAM, P1DATA)) {
				Serial << "Failed to format p1 data as json" << endl;
				broken_frame_counter++;
				return;
			}
			yield();
			if (!formatter.addDeviceInfoToJson(TELEGRAM, "", millis(),
					ESP.getVcc(), frame.getSeqNum(), broken_frame_counter)) {
				Serial << "Failed to add device info to json" << endl;
				return;
			}
			publish(TELEGRAM);
		}
	}
}

