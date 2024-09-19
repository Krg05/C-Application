#include <stdio.h>
#define MAX_PRODUCTS 5
#pragma warning(disable: 4996)

typedef struct {
    int stock;
    int sales;
    int inventory;
} Product;

int select = 0;
int id;

void CalculateInventory(Product products[]) {
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        products[i].inventory = products[i].stock - products[i].sales;
    }
}

void InputStock(Product products[]) {
    printf("입고수량 입력 : 전체 상품 입고수량 입력 1, 개별 상품 입력 2를 선택\n");
    while (1) {
        scanf("%d", &select);
        switch (select) {
        case 1:
            for (int i = 0; i < MAX_PRODUCTS; i++) {
                scanf("%d", &products[i].stock);
            }
            break;
        case 2:
            CalculateInventory(products);
            printf("상품 ID: ");
            scanf("%d", &id);
            if (id < 1 || id > MAX_PRODUCTS) {
                printf("잘못된 ID입니다.\n");
            }
            else {
                printf("상품 %d의 재고 수량: %d\n", id, products[id - 1].inventory);
            }
            break;
        default:
            printf("잘못된 선택입니다. 다시 시도하세요.\n");
            continue;
        }
        break;
    }
}

void InputSales(Product products[]) {
    printf("판매수량 입력 : 전체 상품 판매수량 입력 1, 개별 상품 입력 2를 선택\n");
    while (1) {
        scanf("%d", &select);
        switch (select) {
        case 1:
            for (int i = 0; i < MAX_PRODUCTS; i++) {
                while (1) {
                    scanf("%d", &products[i].sales);
                    if (products[i].sales > products[i].stock) {
                        printf("판매 수량은 입고 수량을 초과할 수 없습니다. 다시 입력하세요.\n");
                    }
                    else {
                        break;
                    }
                }
            }
            break;
        case 2:
            CalculateInventory(products);
            printf("상품 ID: ");
            scanf("%d", &id);
            if (id < 1 || id > MAX_PRODUCTS) {
                printf("잘못된 ID입니다.\n");
            }
            else {
                printf("상품 %d의 판매 수량: %d\n", id, products[id - 1].sales);
            }
            break;
        default:
            printf("잘못된 선택입니다. 다시 시도하세요.\n");
            continue;
        }
        break;
    }
}   

void ProductStatus(Product products[]) {
    CalculateInventory(products);
    int total_sales = 0, total_stock = 0;
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        printf("상품 %d: %d\n", i + 1, products[i].inventory);
    }
    //판매량
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        total_sales += products[i].sales;
        total_stock += products[i].stock;
    }
    double sales_rate = (double)total_sales / total_stock * 100;
    printf("총 판매량: %d (판매율: %.2f%%)\n", total_sales, sales_rate);
    //가장 많이/적게 팔린 상품
    int max_sales = products[0].sales, min_sales = products[0].sales;
    int max_id = 1, min_id = 1;
    for (int i = 1; i < MAX_PRODUCTS; i++) {
        if (products[i].sales > max_sales) {
            max_sales = products[i].sales;
            max_id = i + 1;
        }
        if (products[i].sales < min_sales) {
            min_sales = products[i].sales;
            min_id = i + 1;
        }
    }
    printf("가장 많이 판매된 상품: ID %d, 판매량 %d\n", max_id, max_sales);
    printf("가장 적게 판매된 상품: ID %d, 판매량 %d\n", min_id, min_sales);
    //재고 부족
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        if (products[i].inventory <= 2) {
            printf("상품 ID %d: 재고 부족(%d)\n", i + 1, products[i].inventory);
        }
    }
}

int main(void) {
    Product products[MAX_PRODUCTS] = { 0 };
    while (1) {
        printf("원하는 메뉴를 선택하세요.(1. 입고, 2. 판매, 3. 상품현황, 4. 종료)\n");
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
            printf("프로그램을 종료합니다.\n");
            return 0;
        default:
            printf("잘못된 선택입니다. 다시 시도하세요.\n");
            continue;
        }
    }
}