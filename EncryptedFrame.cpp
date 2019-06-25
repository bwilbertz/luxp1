/*
 * (c) 2019 B. Wilbertz
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */

#include "EncryptedFrame.h"

bool EncryptedFrame::parseNewFrame(uint8* frame, size_t len) {
	if (len < sizeof(FrameHeader))
		return false;

	this->frame_header = (FrameHeader*) frame;

	uint16_t packet_len = __builtin_bswap16(this->frame_header->packet_len_raw);
	this->seq_num = __builtin_bswap32(this->frame_header->frame_counter_raw);

#ifdef DEBUG
	Serial.printf(
			"Header: m1: %02x, id_len: %02x id: %02x, m2: %02x, len: %u, m3: %02x, seq: %u\n",
			frame_header->marker, frame_header->id_len, frame_header->id[0],
			frame_header->marker2, packet_len,
			frame_header->marker3, this->seq_num);
#endif

	// static sanity checks
	if (this->frame_header->marker != 0xdb
			|| this->frame_header->marker2 != 0x82
			|| this->frame_header->marker3 != 0x30
			|| this->frame_header->id_len != 8) {
#ifdef DEBUG
		Serial.printf(
				"Static check failed. m1: %02x, m2: %02x, m3: %02x, id_len: %u\n",
				this->frame_header->marker, this->frame_header->marker2,
				this->frame_header->marker3, this->frame_header->id_len);
#endif

		return false;
	}

	// overall packet length
	if (len < packet_len + 13u) {
#ifdef DEBUG
		Serial.printf("Packed length too short (%u vs %u)\n", len,
				packet_len + 13u);
#endif

		return false;
	}

	// set payload
	this->payload_len = packet_len - 17;
	this->payload = frame + 18;

	// set IV
	memcpy((void*) iv, (const void*) this->frame_header->id, 8);
	memcpy((void*) (iv + 8),
			(const void*) &this->frame_header->frame_counter_raw, 4);

	// set GCM tag
	memcpy((void*) gcm_tag, (const void*) (this->payload + this->payload_len),
			12);

	return true;
}

String EncryptedFrame::getDeviceId() const {
	// TODO
}
