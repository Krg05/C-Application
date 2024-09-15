#include <stdio.h>

void test(int* p, char* cp) {
	printf("test: p = %p, cp = %p\n", p, cp);
	printf("test: p = %d, *cp = %d\n", *p, *cp);
	*p = 60;
	*cp = '$';
	printf("test: p = %p, cp = %p\n", p, cp);
}

int main(void) {
	int a = 50;
	char ch = '*';
	printf("main: a = %d, ch = %d\n", a, ch);
	test(&a, &ch);
	printf("main: a = %d, ch = %d\n", a, ch);

	return 0;
}