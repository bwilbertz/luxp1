/*
 * (c) 2019 B. Wilbertz
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */

#ifndef ENCRYPTEDFRAME_H_
#define ENCRYPTEDFRAME_H_

#include "Arduino.h"

struct __attribute__((__packed__)) header {
	uint8_t marker;
	uint8_t id_len;
	uint8_t id[8];
	uint8_t marker2;
	uint16_t packet_len_raw;
	uint8_t marker3;
	uint32_t frame_counter_raw;
};

typedef header FrameHeader;

class EncryptedFrame {
public:
	EncryptedFrame() :
			frame_header(nullptr), payload_len(0), seq_num(0), payload(nullptr) {
	}
	;
	virtual ~EncryptedFrame() {
	}
	;

	bool parseNewFrame(uint8* frame, unsigned int len);

	const uint8_t* getIv() const {
		return iv;
	}

	size_t getIvLength() const {
		return sizeof(iv);
	}

	const uint8_t* getGcmTag() const {
		return gcm_tag;
	}

	size_t getGcmTagLength() const {
		return sizeof(gcm_tag);
	}

	const uint8_t* getPayload() const {
		return payload;
	}

	size_t getPayloadLength() const {
		return payload_len;
	}

	unsigned int getSeqNum() const {
		return seq_num;
	}

	String getDeviceId() const;

private:
	FrameHeader* frame_header;
	size_t payload_len;
	unsigned int seq_num;
	uint8_t* payload;
	uint8_t gcm_tag[12];
	uint8_t iv[12];
};

#endif /* ENCRYPTEDFRAME_H_ */
