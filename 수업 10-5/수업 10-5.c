#include <stdio.h>
#include <string.h>
#define MAX_PRODUCTS 5
#pragma warning(disable: 4996)

typedef struct {
    int id;
    char name[100];
    int stock;
    int sales;
    int price;
    int totalSalesAmount;
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
        while (getchar() != '\n'); // 버퍼를 비웁니다.
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

    if (products[id - 1].sales > products[id - 1].stock) {
        printf("오류: 판매량이 입고량을 초과할 수 없습니다.\n");
        products[id - 1].sales = 0;
    }
}

void ProductStatus(Product products[]) {
    CalculateInventory(products);

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

void SaveProducts(Product products[]) {
    FILE* file = fopen("products.dat", "wb");
    if (file == NULL) {
        printf("파일을 저장하는데 실패했습니다.\n");
        return;
    }
    fwrite(products, sizeof(Product), MAX_PRODUCTS, file);
    fclose(file);
    printf("상품 정보가 파일에 저장되었습니다.\n");
}

void LoadProducts(Product products[]) {
    FILE* file = fopen("products.dat", "rb");
    if (file == NULL) {
        printf("저장된 파일이 없습니다.\n");
        return;
    }
    fread(products, sizeof(Product), MAX_PRODUCTS, file);
    fclose(file);
    printf("상품 정보가 파일에서 불러와졌습니다.\n");
}

int main(void) {
    Product products[MAX_PRODUCTS] = { 0 };

    while (1) {
        printf("원하는 메뉴를 선택하세요.(1. 입고, 2. 판매, 3. 개별현황, 4. 전체현황, 5. 상품정보저장, 6. 상품정보가져오기, 7. 종료)\n");
        if (scanf("%d", &select) != 1) {
            printf("잘못된 입력입니다. 다시 시도하세요.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (select) {
        case 1:
            InputStock(products);
            break;
        case 2:
            InputSales(products);
            break;
        case 3:
            ProductStatus(products);
            break;
        case 4:
            AllProductStatus(products);
            break;
        case 5:
            SaveProducts(products);
            break;
        case 6:
            LoadProducts(products);
            break;
        case 7:
            printf("프로그램을 종료합니다.\n");
            return 0;
        default:
            printf("잘못된 선택입니다. 다시 시도하세요.\n");
            break;
        }
    }
}