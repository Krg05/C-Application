#include <stdio.h>

int main(void) {
	/*
	���ڿ�
	char str1[5] = { 'a', 'b', 'c', 'd', '\0' };
	char str2[5] = "abcd";
	char str3[5];

	printf("%s\n %s\n", str1, str2);
	scanf("%s", str3);
	printf("%s", str3);
	
	vs

	���ڹ迭
	char str1[5] = { 'a', 'b', 'c', 'd', 'e' };
	char str2[5] = "abcd";

	printf("%s\n %s\n", str1, str2);
	*/

	/*
	���ڿ�
	char str1[] = "string array";
	char* str2 = "char pointer";
	printf("%s\n", str1);
	printf("%s\n", str2);
	
	vs

	������
	char* message = "char pointer";
	printf("%s\n", message);
	message = "change message";
	printf("%s\n", message);
	*/

	/*
	����
	char message[] = "char pointer";
	printf("%s\n", message);
	message = "change message";
	printf("%s\n", message);
	*/

	char message[20] = "hello world\n";
	printf("%s", message);

	return 0;
}