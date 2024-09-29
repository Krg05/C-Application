#include <stdio.h>
#include <string.h>
#pragma warning(disable: 4996)

int main() {
	char src[100] = "source contents";
	char dest[100];
	printf("length of src = %ld\n", strlen(src));
	strcpy(dest, src);
	printf("after copy. src = \"%s\", desc \"%s\"\n", src, dest);
	printf("comp  = %d\n", strcmp(src, dest));
	strcat(dest, src);
	printf("after strcat. src = \"%s\", desc \"%s\"\n", src, dest);
	return 0;
}