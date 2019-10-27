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
char* base64_encode(char *str);

/**
 * url
 */
char* base64_encode_url(char *str);

/**
 * mime
 */
char* base64_encode_mime(char *str);


/**
 * base default
 */
char* base64_decode(char *str);

/**
 * url
 */
char* base64_decode_url(char *str);

/**
 * mime
 */
char* base64_decode_mime(char *str);

