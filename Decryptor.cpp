/*
 * (c) 2019 B. Wilbertz
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */

#include "Decryptor.h"

uint8_t authdata[] = { 0x30, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
		0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF };

bool Decryptor::decryptIntoBuffer(const EncryptedFrame* frame,
		uint8_t* buffer) {
	this->cipher.setKey(this->key, this->cipher.keySize());
	this->cipher.setIV(frame->getIv(), frame->getIvLength());
	this->cipher.addAuthData(authdata, sizeof(authdata));

	this->cipher.decrypt(buffer, frame->getPayload(),
			frame->getPayloadLength());

	return this->cipher.checkTag((void*) frame->getGcmTag(),
			frame->getGcmTagLength());
}
