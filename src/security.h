/*
 * security.h
 *
 *  Created on: Oct 23, 2019
 *      Author: bigboydave
 */
#include <stdio.h>
#include <string.h>

#ifndef SECURITY_H_
#define SECURITY_H_
#endif /* SECURITY_H_ */

/**
 * 加密
 */

char* encrypt(const char *_str);

/**
 * 解密
 */

char* decrypt(const char *_str);

/**
 * sum
 */

char sum(char ch, int index);

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
	bzero(_strarry, length);
	bzero(strarry, length);
	strcpy(_strarry, _str);
	for (int index = 0; index < length; index++) {
		char ch = _strarry[index];
		if (index % 2 == 0) {
			strarry[index] = sum(ch, -6);
		} else {
			strarry[index] = sum(ch, 5);
		}
	}
	char *pchars = strndup(_str, length - 1);
	strcpy(pchars, strarry);
	return pchars;
}

/**
 * 解密
 */

char* decrypt(const char *_str) {
	long unsigned int length = strlen(_str);
	char _strarry[length];
	char strarry[length];
	bzero(_strarry, length);
	bzero(strarry, length);
	strcpy(_strarry, _str);
	for (int index = 0; index < length; index++) {
		char ch = _strarry[index];
		if (index % 2 == 0) {
			strarry[index] = sum(ch, 6);
		} else {
			strarry[index] = sum(ch, -5);
		}
	}
	char *pchars = strndup(_str, length - 1);
	strcpy(pchars, strarry);
	return pchars;
}

/**
 * sum
 */
char sum(char ch, int index) {
	int num = ch;
	char c = num + index;
	return c;
}

