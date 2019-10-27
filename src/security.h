/*
 * security.h
 *
 *  Created on: Oct 23, 2019
 *      Author: bigboydave
 */

#include <stdio.h>
#include <stdlib.h>
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
	printf("encrypt : _str = %s, length = %lu;\n", _str, length);
	int firstFlag = 0;
	char strarry[length];
	char _strarry[length];
	strcpy(strarry, _str);
	strcpy(_strarry, _str);
	for (int index = 0; index < length; index++) {
		char ch = _strarry[index];
		printf("encrypt : _strarry = %s, index = %d, ch = %d;\n", _strarry, index, ch);
		if (index % 2 == 0) {
			strarry[index] = sum(ch, 0);
		} else {
			strarry[index] = sum(ch, 0);
		}
	}
	printf("encrypt : strarry = %s;\n", strarry);
	char *pchars = strndup(_str, length);
	strcpy(pchars, strarry);
	printf("encrypt : input = %s; result = %s;\n", _str, pchars);
	return pchars;
}

/**
 * 解密
 */

char* decrypt(const char *_str) {
	long unsigned int length = strlen(_str);
	char _strarry[length];
	char strarry[length];
	strcpy(strarry, _str);
	strcpy(_strarry, _str);
	for (int index = 0; index < length; index++) {
		char ch = _strarry[index];
		if (index % 2 == 0) {
			strarry[index] = sum(ch, 0);
		} else {
			strarry[index] = sum(ch, 0);
		}
	}
	char *pchars = strndup(_str, length);
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
