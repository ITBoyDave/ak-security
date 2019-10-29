/*
 * base64.c
 *
 *  Created on: Oct 27, 2019
 *      Author: bigboydave
 */

#include <base64.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __cplusplus
#define boolean	_Bool
#define true	1
#define false	0
#else
#define _Bool	boolean
#if __cplusplus < 201103L
#define boolean	boolean
#define false	false
#define true	true
#endif
#endif
#define __bool_true_false_are_defined	1
#define MIMELINEMAX 76

/**
 * This array is a lookup table that translates 6-bit positive integer
 * index values into their "Base64 Alphabet" equivalents as specified
 * in "Table 1: The Base64 Alphabet" of RFC 2045 (and RFC 4648).
 */
const char ENCODE_TO_BASE64[64] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
		'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',
		'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
		'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y',
		'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/' };
/**
 * It's the lookup table for "URL and Filename safe Base64" as specified
 * in Table 2 of the RFC 4648, with the '+' and '/' changed to '-' and
 * '_'. This table is used when BASE64_URL is specified.
 */
const char ENCODE_TO_BASE64_URL[64] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
		'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
		'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
		'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
		'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-', '_' };

/**
 * Lookup table for decoding unicode characters drawn from the
 * "Base64 Alphabet" (as specified in Table 1 of RFC 2045) into
 * their 6-bit positive integer equivalents.  Characters that
 * are not in the Base64 alphabet but fall within the bounds of
 * the array are encoded to -1.
 *
 */
const int DECODE_FROM_BASE64[256] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1,
		-1, 63, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -2, -1, -1,
		-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18,
		19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1, -1, 26, 27, 28, 29, 30,
		31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
		49, 50, 51, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };

/**
 * Lookup table for decoding "URL and Filename safe Base64 Alphabet"
 * as specified in Table2 of the RFC 4648.
 */
const int DECODE_FROM_BASE64_URL[256] = { -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		62, -1, -1, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -2, -1,
		-1, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,
		18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, 63, -1, 26, 27, 28, 29,
		30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
		48, 49, 50, 51, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };

struct Encoder {
	char newline[2];
	int linemax;
	boolean isURL;
	boolean doPadding;
	char* (*encode)(struct Encoder *encoder, const char *str);
	int (*encode_calc)(struct Encoder *encoder, const char src[], int offset,
			int limit, char dst[], const char base64[]);
	int (*encode_outlength)(struct Encoder *encoder, int srclen);
};

struct Decoder {
	boolean isURL;
	boolean isMIME;
	char* (*decode)(struct Decoder *decoder, const char *str);
	int (*decode_calc)(struct Decoder *decoder, const char src[], int offset,
			int limit, char dst[], const int base64[]);
	int (*decode_outlength)(struct Decoder *decoder, const char src[],
			int offset, int limit, const int base64[256]);
};

/**
 *
 */
char* encode(struct Encoder *encoder, const char *str) {
	int srclen = strlen(str);
	int len = encoder->encode_outlength(encoder, srclen);
	char dst[len];
	char src[srclen];
	strcpy(src, str);
	if (encoder->isURL) {
		return strndup(dst,
				encoder->encode_calc(encoder, src, 0, srclen, dst,
						ENCODE_TO_BASE64_URL));
	} else {
		return strndup(dst,
				encoder->encode_calc(encoder, src, 0, srclen, dst,
						ENCODE_TO_BASE64));
	}
}

/**
 *
 */
int encode_calc(struct Encoder *encoder, const char src[], int offset,
		int limit, char dst[], const char base64[]) {
	int sp = offset;
	int slen = (limit - offset) / 3 * 3;
	int sl = offset + slen;
	if (encoder->linemax > 0 && slen > encoder->linemax / 4 * 3)
		slen = encoder->linemax / 4 * 3;
	int dp = 0;
	while (sp < sl) {
		int sl0 = (sp + slen) >= sl ? sp + slen : sp;
		for (int sp0 = sp, dp0 = dp; sp0 < sl0;) {
			unsigned int bits = (src[sp0++] & 0xff) << 16
					| (src[sp0++] & 0xff) << 8 | (src[sp0++] & 0xff);
			dst[dp0++] = (char) base64[(bits >> 18) & 0x3f];
			dst[dp0++] = (char) base64[(bits >> 12) & 0x3f];
			dst[dp0++] = (char) base64[(bits >> 6) & 0x3f];
			dst[dp0++] = (char) base64[bits & 0x3f];
		}
		int dlen = (sl0 - sp) / 3 * 4;
		dp += dlen;
		sp = sl0;
		if (dlen == encoder->linemax && sp < limit) {
			int newlinelen = sizeof(encoder->newline);
			for (int index = 0; index < newlinelen; index++) {
				dst[dp++] = encoder->newline[index];
			}
		}
	}
	if (sp < limit) {  // 1 or 2 leftover bytes
		int b0 = src[sp++] & 0xff;
		dst[dp++] = (char) base64[b0 >> 2];
		if (sp == limit) {
			dst[dp++] = (char) base64[(b0 << 4) & 0x3f];
			if (encoder->doPadding) {
				dst[dp++] = '=';
				dst[dp++] = '=';
			}
		} else {
			int b1 = src[sp++] & 0xff;
			dst[dp++] = (char) base64[((b0 << 4) & 0x3f) | (b1 >> 4)];
			dst[dp++] = (char) base64[(b1 << 2) & 0x3f];
			if (encoder->doPadding) {
				dst[dp++] = '=';
			}
		}
	}
	return dp;
}

/**
 *
 */
int encode_outlength(struct Encoder *encoder, int srclen) {
	int len = 0;
	if (encoder->doPadding) {
		len = 4 * ((srclen + 2) / 3);
	} else {
		int n = srclen % 3;
		len = 4 * (srclen / 3) + (n == 0 ? 0 : n + 1);
	}
	if (encoder->linemax > 0)                             // line separators
		len += (len - 1) / encoder->linemax * sizeof(encoder->newline);
	return len;
}

/**
 * RFC4648
 */
void Encoder_RFC4648(struct Encoder *RFC4648) {
	RFC4648->isURL = false;
	bzero(RFC4648->newline, sizeof(RFC4648->newline));
	RFC4648->linemax = -1;
	RFC4648->doPadding = true;
	RFC4648->encode = encode;
	RFC4648->encode_calc = encode_calc;
	RFC4648->encode_outlength = encode_outlength;
}

/**
 * RFC4648_URLSAFE
 */
void Encoder_RFC4648_URLSAFE(struct Encoder *RFC4648_URLSAFE) {
	RFC4648_URLSAFE->isURL = true;
	bzero(RFC4648_URLSAFE->newline, sizeof(RFC4648_URLSAFE->newline));
	RFC4648_URLSAFE->linemax = -1;
	RFC4648_URLSAFE->doPadding = true;
	RFC4648_URLSAFE->encode = encode;
	RFC4648_URLSAFE->encode_calc = encode_calc;
	RFC4648_URLSAFE->encode_outlength = encode_outlength;
}

/**
 * RFC2045
 */
void Encoder_RFC2045(struct Encoder *RFC2045) {
	RFC2045->isURL = false;
	RFC2045->newline[0] = '\r';
	RFC2045->newline[1] = '\n';
	RFC2045->linemax = MIMELINEMAX;
	RFC2045->doPadding = true;
	RFC2045->encode = encode;
	RFC2045->encode_calc = encode_calc;
	RFC2045->encode_outlength = encode_outlength;
}

/**
 * base default RFC4648
 */
char* base64_encode(const char *str) {
	struct Encoder RFC4648;
	Encoder_RFC4648(&RFC4648);
	return RFC4648.encode(&RFC4648, str);
}

/**
 * url RFC4648_URLSAFE
 */
char* base64_encode_url(const char *str) {
	struct Encoder RFC4648_URLSAFE;
	Encoder_RFC4648_URLSAFE(&RFC4648_URLSAFE);
	return RFC4648_URLSAFE.encode(&RFC4648_URLSAFE, str);
}

/**
 * mime RFC2045
 */
char* base64_encode_mime(const char *str) {
	struct Encoder RFC2045;
	Encoder_RFC2045(&RFC2045);
	return RFC2045.encode(&RFC2045, str);
}

/**
 * -1 "Input byte[] should at least have 2 bytes for base64 bytes"
 */
int decode_outlength(struct Decoder *decoder, const char src[], int offset,
		int limit, const int base64[256]) {
	int paddings = 0;
	int len = limit - offset;
	if (len == 0)
		return 0;
	if (len < 2) {
		if (decoder->isMIME && base64[0] == -1) {
			return 0;
		} else {
			return -1;
		}
	}
	if (decoder->isMIME) {
		// scan all bytes to fill out all non-alphabet. a performance
		// trade-off of pre-scan or Arrays.copyOf
		int n = 0;
		while (offset < limit) {
			int b = src[offset++] & 0xff;
			if (b == '=') {
				len -= (limit - offset + 1);
				break;
			}
			if ((b = base64[b]) == -1)
				n++;
		}
		len -= n;
	} else {
		if (src[limit - 1] == '=') {
			paddings++;
			if (src[offset - 2] == '=')
				paddings++;
		}
	}
	if (paddings == 0 && (len & 0x3) != 0)
		paddings = 4 - (len & 0x3);
	return 3 * ((len + 3) / 4) - paddings;
}

/**
 * -1 Input byte array has wrong 4-byte ending unit
 * -2 Illegal base64 character
 * -3 Last unit does not have enough valid bits
 * -4 Input byte array has incorrect ending byte at offset
 */
int decode_calc(struct Decoder *decoder, const char src[], int offset,
		int limit, char dst[], const int base64[]) {
	int dp = 0;
	int bits = 0;
	int shiftto = 18;       //  of first byte of 4-byte atom
	while (offset < limit) {
		int b = src[offset++] & 0xff;
		if ((b = base64[b]) < 0) {
			if (b == -2) {
				if ((shiftto == 6 && (offset == limit || src[offset++] != '='))
						|| shiftto == 18) {
					return -1;
				}
				break;
			}
			if (decoder->isMIME)    // skip if for rfc2045
				continue;
			else
				return -2;
		}
		bits |= (b << shiftto);
		shiftto -= 6;
		if (shiftto < 0) {
			dst[dp++] = (char) (bits >> 16);
			dst[dp++] = (char) (bits >> 8);
			dst[dp++] = (char) (bits);
			shiftto = 18;
			bits = 0;
		}
	}
	// reached end of byte array or hit padding '=' characters.
	if (shiftto == 6) {
		dst[dp++] = (char) (bits >> 16);
	} else if (shiftto == 0) {
		dst[dp++] = (char) (bits >> 16);
		dst[dp++] = (char) (bits >> 8);
	} else if (shiftto == 12) {
		// dangling single "x", incorrectly encoded.
		return -3;
	}
	// anything left is invalid, if is not MIME.
	// if MIME, ignore all non-base64 character
	while (offset < limit) {
		if (decoder->isMIME && base64[src[offset++]] < 0)
			continue;
		printf("Input byte array has incorrect ending byte at %d\n", offset);
		return -4;
	}
	return dp;
}

char* decode(struct Decoder *decoder, const char *str) {
	int srclen = strlen(str);
	char src[srclen];
	strcpy(src, str);
	int dstlen = 0;
	if (decoder->isURL) {
		dstlen = decoder->decode_outlength(decoder, src, 0, srclen,
				DECODE_FROM_BASE64_URL);
	} else {
		dstlen = decoder->decode_outlength(decoder, src, 0, srclen,
				DECODE_FROM_BASE64);
	}
	if (dstlen == -1) {
		printf("Input byte[] should at least have 2 bytes for base64 bytes!");
		exit(dstlen);
	}
	char dst[dstlen];
	int targetlen = 0;
	if (decoder->isURL) {
		targetlen = decoder->decode_calc(decoder, src, 0, srclen, dst,
				DECODE_FROM_BASE64_URL);
	} else {
		targetlen = decoder->decode_calc(decoder, src, 0, srclen, dst,
				DECODE_FROM_BASE64);
	}
	// assert targetlen
	if (targetlen > 0) {
		return strndup(dst, targetlen);
	} else {
		printf(
				"exit code = %d:\n -1 Input byte array has wrong 4-byte ending unit \n -2 Illegal base64 character \n -3 Last unit does not have enough valid bits \n -4 Input byte array has incorrect ending byte at offset \n",
				targetlen);
		exit(targetlen);
	}
}

/**
 * RFC4648
 */
void Decoder_RFC4648(struct Decoder *RFC4648) {
	RFC4648->isURL = false;
	RFC4648->isMIME = false;
	RFC4648->decode = decode;
	RFC4648->decode_calc = decode_calc;
	RFC4648->decode_outlength = decode_outlength;
}

/**
 * RFC4648_URLSAFE
 */
void Decoder_RFC4648_URLSAFE(struct Decoder *RFC4648_URLSAFE) {
	RFC4648_URLSAFE->isURL = true;
	RFC4648_URLSAFE->isMIME = false;
	RFC4648_URLSAFE->decode = decode;
	RFC4648_URLSAFE->decode_calc = decode_calc;
	RFC4648_URLSAFE->decode_outlength = decode_outlength;
}

/**
 * RFC2045
 */
void Decoder_RFC2045(struct Decoder *RFC2045) {
	RFC2045->isURL = false;
	RFC2045->isMIME = true;
	RFC2045->decode = decode;
	RFC2045->decode_calc = decode_calc;
	RFC2045->decode_outlength = decode_outlength;
}

/**
 * base default RFC4648
 */
char* base64_decode(const char *str) {
	struct Decoder RFC4648;
	Decoder_RFC4648(&RFC4648);
	return RFC4648.decode(&RFC4648, str);
}

/**
 * url RFC4648_URLSAFE
 */
char* base64_decode_url(const char *str) {
	struct Decoder RFC4648_URLSAFE;
	Decoder_RFC4648_URLSAFE(&RFC4648_URLSAFE);
	return RFC4648_URLSAFE.decode(&RFC4648_URLSAFE, str);
}

/**
 * mime RFC2045
 */
char* base64_decode_mime(const char *str) {
	struct Decoder RFC2045;
	Decoder_RFC2045(&RFC2045);
	return RFC2045.decode(&RFC2045, str);
}

/**
 * main 调试程序
 */
int main_test(int argc, char *args[]) {

	const char *origin0 = "c语言是最好的！TMD!";
	char *encode_origin0 = base64_encode(origin0);
	char *decode_encode_origin0 = base64_decode(encode_origin0);
	printf("origin0 = %s, encode_origin0 = %s, decode_encode_origin0 = %s;\n",
			origin0, encode_origin0, decode_encode_origin0);

	char *origin1 =
			"http://www.bigboydave.cn/service/weather?type=7d&city_name=杭州";
	char *encode_origin1 = base64_encode_url(origin1);
	char *decode_encode_origin1 = base64_decode_url(encode_origin1);
	printf("origin1 = %s, encode_origin1 = %s, decode_encode_origin1 = %s;\n",
			origin1, encode_origin1, decode_encode_origin1);

	char *origin = "Hello World!";
	char *encode_origin = base64_encode(origin);
	char *decode_encode_origin = base64_decode(encode_origin);
	printf("origin = %s, encode_origin = %s, decode_encode_origin = %s;\n",
			origin, encode_origin, decode_encode_origin);

	return 0;
}

