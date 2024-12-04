#include <stdio.h>
#include <string.h>
#include <math.h>
#define WORD 16
#pragma warning(disable: 4996)

void getBinary(char bin[], char sr[], int n) {
    int len = strlen(sr);
    int padding = n - len;

    if (len > n) {
        printf("Input too long\n");
        return;
    }

    for (int i = 0; i < padding; i++) {
        bin[i] = '0';
    }

    for (int i = 0; i < len; i++) {
        bin[padding + i] = sr[i];
    }
    bin[n] = '\0';
}

void complement2(char bin[], int n) {
    int flip = 0;

    for (int i = n - 1; i >= 0; i--) {
        if (flip) {
            bin[i] = (bin[i] == '0') ? '1' : '0';
        }
        if (bin[i] == '1' && !flip) {
            flip = 1;
        }
    }
}

int bin2dec(char bin[], int n) {
    int result = 0;
    int is_negative = (bin[0] == '1');

    if (is_negative) {
        char temp[WORD + 1];
        strcpy(temp, bin);
        complement2(temp, n);

        for (int i = 0; i < n; i++) {
            if (temp[i] == '1') {
                result += (1 << (n - 1 - i));
            }
        }
        result = -result;
    }
    else {
        for (int i = 0; i < n; i++) {
            if (bin[i] == '1') {
                result += (1 << (n - 1 - i));
            }
        }
    }

    return result;
}


int main() {
	char input1[100];
	char input2[100];
	char op[10];

	char binary1[WORD + 1] = { 0 };
	char binary2[WORD + 1] = { 0 };

	int result;
	int num1, num2;

	printf("<<<<<input>>>>>\n");
	gets(input1);
	gets(op);
	gets(input2);
	getBinary(binary1, input1, WORD);
	getBinary(binary2, input2, WORD);

	num1 = bin2dec(binary1, WORD);
	num2 = bin2dec(binary2, WORD);

	switch (op[0]) {
	case '+':
		result = num1 + num2;
		break;
	case '-':
		result = num1 + num2;
		break;
	case '*':
		result = num1 + num2;
		break;
	case '/':
		result = num1 + num2;
		break;
	case '%':
		result = num1 + num2;
		break;
	default:
		printf("bad operator...\n");
		break;
	}
    printf("%s(%d) %c %s(%d) = %d\n", binary1, num1, op[0], binary2, num2, result);

	return 0;
}