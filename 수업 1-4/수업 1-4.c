#include <stdio.h>
#pragma warning(disable: 4996)
#define MAX_PRODUCTS 100

typedef struct {
    int stock;      
    int sales;      
    int inventory;  
} Product;

int main(void) {
    int num_products;
    Product products[MAX_PRODUCTS];
    int id;

    printf("상품의 개수를 입력하세요 (1~100): ");
    scanf("%d", &num_products);

    if (num_products < 1 || num_products > 100) {
        printf("상품의 개수는 1에서 100 사이여야 합니다.\n");
        return 1;
    }

    printf("상품별 입고 수량을 입력하세요.\n");
    for (int i = 0; i < num_products; i++) {
        printf("상품 %d의 입고 수량: ", i + 1);
        scanf("%d", &products[i].stock);
    }

    printf("상품별 판매 수량을 입력하세요.\n");
    for (int i = 0; i < num_products; i++) {
        while (1) {
            printf("상품 %d의 판매 수량: ", i + 1);
            scanf("%d", &products[i].sales);

            if (products[i].sales > products[i].stock) {
                printf("판매 수량은 입고 수량을 초과할 수 없습니다. 다시 입력하세요.\n");
            }
            else {
                break;
            }
        }
    }

    for (int i = 0; i < num_products; i++) {
        products[i].inventory = products[i].stock - products[i].sales;
    }

    printf("재고를 확인할 상품 ID를 입력하세요 (1~%d): ", num_products);
    scanf("%d", &id);

    if (id < 1 || id > num_products) {
        printf("잘못된 ID입니다.\n");
    }
    else {
        printf("상품 %d의 재고 수량: %d\n", id, products[id - 1].inventory);
    }

    printf("전체 상품의 재고 수량:\n");
    for (int i = 0; i < num_products; i++) {
        printf("상품 %d: %d\n", i + 1, products[i].inventory);
    }

    return 0;
}
