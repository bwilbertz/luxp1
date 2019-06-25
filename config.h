/*
 * (c) 2019 B. Wilbertz
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <ESP8266WiFi.h>

#define LEN 1532
#define SERIAL_TIMEOUT 20
//#define OTA_UPDATE 1
//#define OUTPUT_RAW 1
#define OUTPUT_P1 1
//#define USE_TEST_DATA 1

const char* VERSION = "luxp1-0.0.1";

const char* SSID = "YourSSID";
const char* PASSWORD = "YourPassword";

const char* MQTT_SERVER = "XXX.XXX.XXX.XXX";
const char* TOPIC_RAW = "luxp1/meter/raw";
const char* TOPIC_P1 = "luxp1/meter/p1data";
const char* TOPIC_FW = "luxp1/meter/firmware";
const char* TOPIC = "luxp1/meter/telegram";
const char* LAST_WILL_TOPIC = "luxp1/meter/status";

//Key for SAGXXXXXXXXXXXXX:
uint8_t key_SM[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

#ifdef USE_TEST_DATA
unsigned char test_data[] = { 0xdb, 0x08, 0x53, 0x41, 0x47, 0xff, 0xff, 0xff,
		0xff, 0xff, 0x82, 0x02, 0x7a, 0x30, 0x00, 0x00, 0x01, 0xa8, 0x16, 0x09,
		0xe5, 0x2b, 0xcd, 0x80, 0x49, 0xd2, 0xee, 0x43, 0x7e, 0x2c, 0xa3, 0x37,
		0xb6, 0xf4, 0xa2, 0x52, 0xd6, 0xe3, 0x3d, 0x46, 0xdb, 0x70, 0x1c, 0x29,
		0xdc, 0x71, 0xa1, 0xec, 0x6c, 0x27, 0x1b, 0xb1, 0x57, 0x4c, 0xd3, 0xde,
		0x77, 0x99, 0x74, 0x2d, 0xa8, 0x23, 0x67, 0xe2, 0x68, 0xe7, 0xac, 0x73,
		0x70, 0x8d, 0x2b, 0x08, 0xc2, 0xf2, 0x4e, 0xed, 0x48, 0xf6, 0xf8, 0x94,
		0xed, 0xb8, 0xc9, 0x98, 0xbc, 0x77, 0xe1, 0x8f, 0x68, 0x71, 0x1f, 0xb9,
		0x93, 0x9c, 0xdc, 0x34, 0x32, 0xf2, 0x6e, 0xaa, 0x8e, 0x91, 0xb5, 0xcf,
		0xb2, 0x84, 0x71, 0x1d, 0x81, 0x50, 0x69, 0x1e, 0x8c, 0x05, 0xcc, 0x24,
		0x28, 0x20, 0x65, 0x2c, 0x27, 0x83, 0xcd, 0x15, 0x29, 0x3e, 0x1d, 0x43,
		0x3b, 0x6b, 0x47, 0x57, 0x37, 0xad, 0x04, 0x13, 0xd9, 0x73, 0xee, 0xf0,
		0x4c, 0x00, 0x89, 0xf8, 0x40, 0x0e, 0x39, 0x27, 0x7d, 0xca, 0xc6, 0x24,
		0xb1, 0x26, 0xaf, 0x83, 0x9e, 0xeb, 0xdd, 0x51, 0x61, 0x34, 0xc4, 0x8f,
		0xea, 0x6f, 0x83, 0xa8, 0xe1, 0x2e, 0xff, 0x37, 0xd3, 0xb6, 0xc7, 0xfa,
		0x0f, 0xa0, 0x03, 0xce, 0x74, 0x2b, 0x31, 0x95, 0x26, 0x52, 0xe0, 0x7f,
		0x64, 0xa1, 0x3f, 0xab, 0x5a, 0xfb, 0xd5, 0x26, 0xfb, 0x79, 0x7d, 0xa8,
		0x53, 0xfe, 0x85, 0xdc, 0xb9, 0xb2, 0x40, 0x0a, 0x65, 0x98, 0xc8, 0xa9,
		0x38, 0xfc, 0x94, 0xc7, 0xc4, 0xd8, 0xde, 0x9c, 0x8e, 0xd1, 0x42, 0x38,
		0x60, 0x04, 0x98, 0x1a, 0xfa, 0xd8, 0x0e, 0xf7, 0xfb, 0x30, 0xc0, 0xa3,
		0xfd, 0x48, 0x02, 0x08, 0x0d, 0x77, 0x53, 0x99, 0xbf, 0x8e, 0xc6, 0x4d,
		0xf5, 0xbc, 0x88, 0xa8, 0x96, 0xba, 0x26, 0xec, 0x1e, 0xc4, 0x01, 0xfd,
		0x98, 0xe6, 0xcb, 0xe8, 0x33, 0x1b, 0xeb, 0x69, 0xca, 0x12, 0x7b, 0xc2,
		0xa0, 0xbe, 0x19, 0x66, 0xe5, 0x88, 0x91, 0x52, 0xd1, 0x9f, 0x33, 0x75,
		0x76, 0xe4, 0xe2, 0x79, 0x39, 0xa4, 0x33, 0xba, 0x57, 0x59, 0xe5, 0x6d,
		0xbb, 0xfd, 0x81, 0x8e, 0x08, 0x91, 0xc7, 0x34, 0x90, 0xe1, 0xb5, 0x08,
		0xa0, 0x46, 0xf6, 0xba, 0x71, 0x47, 0x11, 0x3f, 0x7b, 0x61, 0xae, 0x28,
		0x5a, 0xf7, 0xb3, 0x76, 0x71, 0x9c, 0x79, 0x47, 0x11, 0x4e, 0xff, 0x13,
		0xab, 0x6a, 0xd3, 0xa5, 0x9f, 0x5a, 0xfd, 0xe0, 0xd9, 0x69, 0xac, 0x1a,
		0x7d, 0xca, 0x28, 0xef, 0x2f, 0xc1, 0x11, 0x93, 0x18, 0x09, 0xe5, 0xc7,
		0x6a, 0x0d, 0x63, 0x74, 0x2b, 0xab, 0xd8, 0xc7, 0x4d, 0xd1, 0xbd, 0x4c,
		0x5c, 0x1a, 0xe4, 0x6c, 0x23, 0x3c, 0x42, 0x6f, 0x7e, 0xad, 0x22, 0xaf,
		0x0a, 0xc9, 0xbb, 0x0c, 0x31, 0x30, 0x1f, 0xf3, 0xc3, 0x2b, 0x07, 0xd0,
		0x6f, 0xb0, 0x40, 0x46, 0xd0, 0x29, 0x01, 0x06, 0x58, 0xa6, 0x0d, 0x08,
		0xeb, 0xa6, 0x2e, 0xd4, 0x4a, 0xb1, 0xca, 0x5a, 0x7f, 0x4f, 0xda, 0x31,
		0xae, 0xb6, 0xd9, 0xe5, 0x7c, 0xeb, 0xd2, 0x86, 0xda, 0xcf, 0x8a, 0xe3,
		0x50, 0x41, 0x50, 0xbd, 0xfa, 0x52, 0x7a, 0x24, 0x0c, 0xd5, 0x65, 0x71,
		0x28, 0xb2, 0xc8, 0x71, 0x85, 0xe1, 0x01, 0xa3, 0xfd, 0x4b, 0xca, 0x04,
		0x56, 0x7e, 0xdb, 0x0f, 0x96, 0xbf, 0xe0, 0x0c, 0xa0, 0xf6, 0xa2, 0x54,
		0x09, 0xaa, 0x9d, 0xaa, 0x78, 0x2e, 0xae, 0x74, 0xb4, 0xb0, 0xd2, 0xed,
		0xa7, 0x2e, 0x5c, 0xb9, 0x5c, 0x53, 0xda, 0x0a, 0x7f, 0x11, 0x3d, 0xbb,
		0x86, 0xd9, 0x20, 0xed, 0x59, 0xe6, 0x45, 0x4b, 0x35, 0xdd, 0x40, 0x6e,
		0x52, 0x74, 0x23, 0xb2, 0x6c, 0x00, 0xe7, 0x83, 0xa0, 0x85, 0x2b, 0x96,
		0x1b, 0xa9, 0xe0, 0x3a, 0x44, 0x45, 0x54, 0x84, 0x35, 0x64, 0x3c, 0x59,
		0x55, 0xb2, 0x1f, 0x64, 0x9b, 0xfa, 0x34, 0x44, 0xae, 0x36, 0x9a, 0xd3,
		0x61, 0x83, 0x8f, 0x6e, 0xed, 0x34, 0xb9, 0xd8, 0xe3, 0x71, 0x03, 0x63,
		0x5e, 0x96, 0x7c, 0x5f, 0xae, 0xab, 0xcf, 0xa7, 0x59, 0x4f, 0x5f, 0xfb,
		0x78, 0x8d, 0x49, 0xfd, 0xc0, 0xd9, 0xcd, 0x59, 0xa1, 0xda, 0x7a, 0x1a,
		0xd7, 0x12, 0xb2, 0xba, 0xf8, 0x68, 0xca, 0x47, 0x4e, 0xbd, 0xf1, 0x28,
		0xdf, 0x89, 0xdc, 0xbf, 0xfb, 0xcb, 0x28, 0x18, 0xe5, 0x3c, 0x7e, 0xe8,
		0x76, 0x86, 0x5e, 0x3f, 0x35, 0x39, 0x34, 0x62, 0x3c, 0x05, 0xe8, 0xb9,
		0xa4, 0xc1, 0x65, 0x36, 0x4b, 0xcc, 0x54, 0x44, 0x72, 0xf4, 0x09, 0x29,
		0xe0, 0xf8, 0x16, 0xe7, 0xc4, 0xdc, 0xc9, 0x2b, 0x4f, 0xb6, 0x17, 0x0b,
		0xbe, 0x58, 0x7a, 0x76, 0x07, 0x29, 0x98, 0x92, 0x99, 0x75, 0x9c, 0xcc,
		0xa7, 0x46, 0x19 };
unsigned int test_data_len = 647;
#endif

#endif /* CONFIG_H_ */
