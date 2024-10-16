#include <stdio.h>
#include <string.h>
#define MAX_PRODUCTS 5
#pragma warning(disable: 4996)

typedef struct {
    int id;
    char name[100];
    int stock;
    int sales;
    int price; // 상품 가격
    int totalSalesAmount; // 총 판매 금액
} Product;

int select = 0;
int id;

void CalculateInventory(Product products[]) {
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        products[i].totalSalesAmount = products[i].sales * products[i].price;
    }
}

void InputStock(Product products[]) {
    printf("입고 메뉴 실행(상품 ID 입력): ");
    while (scanf("%d", &id) != 1 || id < 1 || id > MAX_PRODUCTS) {
        printf("잘못된 입력입니다. 다시 입력하세요.\n");
        while (getchar() != '\n');
    }

    printf("상품명 입력: ");
    scanf("%s", products[id - 1].name);
    printf("입고량 입력: ");
    scanf("%d", &products[id - 1].stock);
    printf("판매 가격 입력: ");
    scanf("%d", &products[id - 1].price);
}

void InputSales(Product products[]) {
    printf("판매 메뉴 실행(상품 ID 입력): ");
    while (scanf("%d", &id) != 1 || id < 1 || id > MAX_PRODUCTS) {
        printf("잘못된 입력입니다. 다시 입력하세요.\n");
        while (getchar() != '\n');
    }

    printf("판매량 입력: ");
    scanf("%d", &products[id - 1].sales);

    // 판매량이 입고량을 초과하면 오류 메시지 출력
    if (products[id - 1].sales > products[id - 1].stock) {
        printf("오류: 판매량이 입고량을 초과할 수 없습니다.\n");
        products[id - 1].sales = 0; // 판매량 초기화
    }
}

void ProductStatus(Product products[]) {
    CalculateInventory(products);

    // 개별 상품 정보 출력
    printf("개별 상품 정보 입력(상품 ID 입력): ");
    while (scanf("%d", &id) != 1 || id < 1 || id > MAX_PRODUCTS) {
        printf("잘못된 입력입니다. 다시 입력하세요.\n");
        while (getchar() != '\n');
    }

    printf("상품명: %s, 가격: %d, 입고량: %d, 판매량: %d, 총 판매 금액: %d\n",
        products[id - 1].name, products[id - 1].price, products[id - 1].stock,
        products[id - 1].sales, products[id - 1].totalSalesAmount);
}

void AllProductStatus(Product products[]) {
    CalculateInventory(products);

    printf("전체 상품 현황:\n");
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        printf("ID: %d, 상품명: %s, 가격: %d, 입고량: %d, 판매량: %d, 총 판매 금액: %d\n",
            i + 1, products[i].name, products[i].price, products[i].stock,
            products[i].sales, products[i].totalSalesAmount);
    }
}

int main(void) {
    Product products[MAX_PRODUCTS] = { 0 };

    while (1) {
        printf("원하는 메뉴를 선택하세요.(1. 입고, 2. 판매, 3. 개별현황, 4. 전체현황, 5. 종료)\n");
        scanf("%d", &select);

        switch (select) {
        case 1:
            InputStock(products);
            continue;
        case 2:
            InputSales(products);
            continue;
        case 3:
            ProductStatus(products);
            continue;
        case 4:
            AllProductStatus(products);
            continue;
        case 5:
            printf("프로그램을 종료합니다.\n");
            return 0;
        default:
            printf("잘못된 선택입니다. 다시 시도하세요.\n");
            continue;
        }
    }
}
