/*
 * security.h
 *
 *  Created on: Oct 23, 2019
 *      Author: bigboydave
 */
#ifndef SECURITY_H_
#define SECURITY_H_
#endif /* SECURITY_H_ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <base64.h>

/**
 * 加密
 */
char* encrypt(const char *_str);

/**
 * 解密
 */
char* decrypt(const char *str);

/**
 * sum
 */
char sum(char ch, int index) {
	int num = ch;
	char c = num + index;
	return c;
}

/**
 * number 48-57
 * a-z 97-122
 * A-Z 65-90
 * @ 64
 * : 58
 */
/**
 * 加密
 */
char* encrypt(const char *_str) {
	long unsigned int length = strlen(_str);
	int firstFlag = 0;
	char strarry[length];
	char _strarry[length];
	strcpy(strarry, _str);
	for (int index = 0; index < length; index++) {
		char ch = strarry[index];
		if (index % 2 == 0) {
			strarry[index] = sum(ch, 529);
		} else {
			strarry[index] = sum(ch, -115);
		}
	}
	char *pchars = base64_encode(strarry);
	return pchars;
}

/**
 * 解密
 */
char* decrypt(const char *str) {
	char *_str = base64_decode(str);
	long unsigned int length = strlen(_str);
	char strarry[length];
	strcpy(strarry, _str);
	for (int index = 0; index < length; index++) {
		char ch = strarry[index];
		if (index % 2 == 0) {
			strarry[index] = sum(ch, -529);
		} else {
			strarry[index] = sum(ch, 115);
		}
	}
	char *pchars = strndup(_str, length);
	strcpy(pchars, strarry);
	return pchars;
}

