#include <stdio.h>
#pragma warning(disable: 4996)
#define MAX_PRODUCTS 100

typedef struct {
    int stock;
    int sales;
    int inventory;
} Product;

void InputStock(Product products[], int num_products) {
    printf("��ǰ�� �԰� ������ �Է��ϼ���.\n");
    for (int i = 0; i < num_products; i++) {
        printf("��ǰ %d�� �԰� ����: ", i + 1);
        scanf("%d", &products[i].stock);
    }
}

void InputSales(Product products[], int num_products) {
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
}

void CalculateInventory(Product products[], int num_products) {
    for (int i = 0; i < num_products; i++) {
        products[i].inventory = products[i].stock - products[i].sales;
    }
}

void PrintInventory(Product products[], int num_products) {
    printf("\n��ü ��ǰ�� ��� ����:\n");
    for (int i = 0; i < num_products; i++) {
        printf("��ǰ %d: %d\n", i + 1, products[i].inventory);
    }
}

void SalesRate(Product products[], int num_products) {
    int total_sales = 0, total_stock = 0;
    for (int i = 0; i < num_products; i++) {
        total_sales += products[i].sales;
        total_stock += products[i].stock;
    }
    double sales_rate = (double)total_sales / total_stock * 100;
    printf("�� �Ǹŷ�: %d (�Ǹ���: %.2f%%)\n", total_sales, sales_rate);
}

void FindExtremes(Product products[], int num_products) {
    int max_sales = products[0].sales, min_sales = products[0].sales;
    int max_id = 1, min_id = 1;
    for (int i = 1; i < num_products; i++) {
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
}

void InventoryWarnings(Product products[], int num_products) {
    for (int i = 0; i < num_products; i++) {
        if (products[i].inventory <= 2) {
            printf("��ǰ ID %d: ��� ����(%d)\n", i + 1, products[i].inventory);
        }
    }
}

int main(void) {
    Product products[MAX_PRODUCTS];
    int num_products;

    printf("��ǰ�� ������ �Է��ϼ��� (1~100): ");
    scanf("%d", &num_products);

    if (num_products < 1 || num_products > 100) {
        printf("��ǰ�� ������ 1���� 100 ���̿��� �մϴ�.\n");
        return 1;
    }

    InputStock(products, num_products);
    InputSales(products, num_products);
    CalculateInventory(products, num_products);
    PrintInventory(products, num_products);
    SalesRate(products, num_products);
    FindExtremes(products, num_products);
    InventoryWarnings(products, num_products);

    return 0;
}
