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

    printf("��ǰ�� ������ �Է��ϼ��� (1~100): ");
    scanf("%d", &num_products);

    if (num_products < 1 || num_products > 100) {
        printf("��ǰ�� ������ 1���� 100 ���̿��� �մϴ�.\n");
        return 1;
    }

    printf("��ǰ�� �԰� ������ �Է��ϼ���.\n");
    for (int i = 0; i < num_products; i++) {
        printf("��ǰ %d�� �԰� ����: ", i + 1);
        scanf("%d", &products[i].stock);
    }

    printf("��ǰ�� �Ǹ� ������ �Է��ϼ���.\n");
    for (int i = 0; i < num_products; i++) {
        while (1) {
            printf("��ǰ %d�� �Ǹ� ����: ", i + 1);
            scanf("%d", &products[i].sales);

            if (products[i].sales > products[i].stock) {
                printf("�Ǹ� ������ �԰� ������ �ʰ��� �� �����ϴ�. �ٽ� �Է��ϼ���.\n");
            }
            else {
                break;
            }
        }
    }

    for (int i = 0; i < num_products; i++) {
        products[i].inventory = products[i].stock - products[i].sales;
    }

    printf("��� Ȯ���� ��ǰ ID�� �Է��ϼ��� (1~%d): ", num_products);
    scanf("%d", &id);

    if (id < 1 || id > num_products) {
        printf("�߸��� ID�Դϴ�.\n");
    }
    else {
        printf("��ǰ %d�� ��� ����: %d\n", id, products[id - 1].inventory);
    }

    printf("��ü ��ǰ�� ��� ����:\n");
    for (int i = 0; i < num_products; i++) {
        printf("��ǰ %d: %d\n", i + 1, products[i].inventory);
    }

    return 0;
}
