#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4996)

typedef struct point {
	int x;
	int y;
}POINT;

int inputMenu(void) {
	int input;
	printf("1. 만들기, 2. 출력하기, 3. 클리어, 4. 파일 저장, 5. 파일 로드, -1. 종료 : ");
	scanf("%d", &input);
	return input;
}

POINT* makePoint(void) {
	POINT* p = (POINT*)malloc(sizeof(POINT));
	p->x = rand() % 100;
	p->y = rand() % 100;
	return p;
}

void printPoint(POINT* p[], int size) {
	for (int i = 0; i < size; i++) {
		printf("x: %d, y: %d\n", p[i]->x, p[i]->y);
	}
}

void freePoints(POINT* p[], int size) {
	for (int i = 0; i < size; i++) {
		free(p[i]);
	}
}

int saveFile(POINT* p[], int count) {
	FILE* fp;
	fp = fopen("points.bin", "ab");
	if (fp == NULL) {
		return 0;
	}
	for (int i = 0; i < count; i++) {
		fwrite(p[i], sizeof(POINT), 1, fp);
	}
	fclose(fp);
	return 1;
}

int loadFile(POINT* p[], int max) {
	FILE* fp;
	int fSize, fCount;
	fp = fopen("points.bin", "rb");
	if (fp == NULL) {
		return 0;
	}

	fseek(fp, 0, SEEK_END);
	fSize = ftell(fp);
	fCount = fSize / sizeof(POINT);
	rewind(fp);

	for (int i = 0; i < fCount; i++) {
		if (i == max) {
			break;
		}
		p[i] = (POINT*)malloc(sizeof(POINT));
		fread(p[i], sizeof(POINT), 1, fp);
	}
	fclose(fp);
	return fCount;
}

int main() {
	int menu;
	int count = 0;
	POINT* points[100];	
	do {
		menu = inputMenu();
		if (menu == 1) {
			points[count] = makePoint();
			count++;
			printf("잘 만들었습니다.\n");
		}
		else if (menu == 2) {
			printPoint(points, count);
		}
		else if (menu == -1) {
			freePoints(points, count);
			printf("프로그램을 종료합니다.\n");
		}
	} while (menu > 0);

	return 0;
}

/*
	POINT* points;
	int count;
	scanf("%d", &count);

	points = (POINT*)malloc(sizeof(POINT) * count);

	for (int i = 0; i < count; i++) {
		points[i].x = rand() % 100;
		points[i].y = rand() % 100;
	}
	for (int i = 0; i < count; i++) {
		printf("x - %d, y - %d\n", points[i].x, points[i].y);
	}
*/