/*
 * (c) 2019 B. Wilbertz
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */

#ifndef DECRYPTOR_H_
#define DECRYPTOR_H_

#include <AES.h>
#include <Crypto.h>
#include <GCM.h>

#include "EncryptedFrame.h"

class Decryptor {
public:
	Decryptor() :
			cipher(), key(nullptr) {
	}
	;

	Decryptor(const uint8_t* key) :
			cipher(), key(key) {
	}
	;
	virtual ~Decryptor() {
	}
	;

	bool decryptIntoBuffer(const EncryptedFrame* frame, uint8_t* buffer);
private:
	GCM<AES128> cipher;
	const uint8_t* key;

};

#endif /* DECRYPTOR_H_ */
