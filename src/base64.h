/*
 * base64.h
 *
 *  Created on: Oct 27, 2019
 *      Author: bigboydave
 */

#ifndef BASE64_H_
#define BASE64_H_

#endif /* BASE64_H_ */

/**
 * base default
 */
char* base64_encode(const char *str);

/**
 * url
 */
char* base64_encode_url(const char *str);

/**
 * mime
 */
char* base64_encode_mime(const char *str);


/**
 * base default
 */
char* base64_decode(const char *str);

/**
 * url
 */
char* base64_decode_url(const char *str);

/**
 * mime
 */
char* base64_decode_mime(const char *str);

