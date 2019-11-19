#include <security.h>
#include <stdio.h>
#include <aksecurity.h>

/*
 * Class:     cn_bigboydave_common_security_AkSecurity
 * Method:    encrypt
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_cn_bigboydave_common_core_security_AkSecurity_encrypt(
		JNIEnv *env, jobject obj, jstring value) {
	const char *str = (*env)->GetStringUTFChars(env, value, 0);
	str = encrypt(str);
	jstring key = (*env)->NewStringUTF(env, str);
	(*env)->ReleaseStringUTFChars(env, value, str);
	return key;
}

/*
 * Class:     cn_bigboydave_common_security_AkSecurity
 * Method:    decrypt
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_cn_bigboydave_common_core_security_AkSecurity_decrypt(
		JNIEnv *env, jobject obj, jstring key) {
	const char *str = (*env)->GetStringUTFChars(env, key, 0);
	str = decrypt(str);
	jstring value = (*env)->NewStringUTF(env, str);
	(*env)->ReleaseStringUTFChars(env, key, str);
	return value;
}

int main() {
	char *input = "草泥马比的c语言";
	char *target = encrypt(input);
	printf("input = %s, target = %s;\n", input, target);
	char *origin = decrypt(target);
	printf("input = %s; target = %s;\n", target, origin);
	return 0;
}
