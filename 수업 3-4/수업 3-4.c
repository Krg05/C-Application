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
    printf("�԰���� �Է� : ��ü ��ǰ �԰���� �Է� 1, ���� ��ǰ �Է� 2�� ����\n");
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
            printf("��ǰ ID: ");
            scanf("%d", &id);
            if (id < 1 || id > MAX_PRODUCTS) {
                printf("�߸��� ID�Դϴ�.\n");
            }
            else {
                printf("��ǰ %d�� ��� ����: %d\n", id, products[id - 1].inventory);
            }
            break;
        default:
            printf("�߸��� �����Դϴ�. �ٽ� �õ��ϼ���.\n");
            continue;
        }
        break;
    }
}

void InputSales(Product products[]) {
    printf("�Ǹż��� �Է� : ��ü ��ǰ �Ǹż��� �Է� 1, ���� ��ǰ �Է� 2�� ����\n");
    while (1) {
        scanf("%d", &select);
        switch (select) {
        case 1:
            for (int i = 0; i < MAX_PRODUCTS; i++) {
                while (1) {
                    scanf("%d", &products[i].sales);
                    if (products[i].sales > products[i].stock) {
                        printf("�Ǹ� ������ �԰� ������ �ʰ��� �� �����ϴ�. �ٽ� �Է��ϼ���.\n");
                    }
                    else {
                        break;
                    }
                }
            }
            break;
        case 2:
            CalculateInventory(products);
            printf("��ǰ ID: ");
            scanf("%d", &id);
            if (id < 1 || id > MAX_PRODUCTS) {
                printf("�߸��� ID�Դϴ�.\n");
            }
            else {
                printf("��ǰ %d�� �Ǹ� ����: %d\n", id, products[id - 1].sales);
            }
            break;
        default:
            printf("�߸��� �����Դϴ�. �ٽ� �õ��ϼ���.\n");
            continue;
        }
        break;
    }
}   

void ProductStatus(Product products[]) {
    CalculateInventory(products);
    int total_sales = 0, total_stock = 0;
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        printf("��ǰ %d: %d\n", i + 1, products[i].inventory);
    }
    //�Ǹŷ�
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        total_sales += products[i].sales;
        total_stock += products[i].stock;
    }
    double sales_rate = (double)total_sales / total_stock * 100;
    printf("�� �Ǹŷ�: %d (�Ǹ���: %.2f%%)\n", total_sales, sales_rate);
    //���� ����/���� �ȸ� ��ǰ
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
    printf("���� ���� �Ǹŵ� ��ǰ: ID %d, �Ǹŷ� %d\n", max_id, max_sales);
    printf("���� ���� �Ǹŵ� ��ǰ: ID %d, �Ǹŷ� %d\n", min_id, min_sales);
    //��� ����
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        if (products[i].inventory <= 2) {
            printf("��ǰ ID %d: ��� ����(%d)\n", i + 1, products[i].inventory);
        }
    }
}

int main(void) {
    Product products[MAX_PRODUCTS] = { 0 };
    while (1) {
        printf("���ϴ� �޴��� �����ϼ���.(1. �԰�, 2. �Ǹ�, 3. ��ǰ��Ȳ, 4. ����)\n");
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
            printf("���α׷��� �����մϴ�.\n");
            return 0;
        default:
            printf("�߸��� �����Դϴ�. �ٽ� �õ��ϼ���.\n");
            continue;
        }
    }
}