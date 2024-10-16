#include <stdio.h>
#include <string.h>
#define MAX_PRODUCTS 5
#pragma warning(disable: 4996)

typedef struct {
    int id;
    char name[100];
    int stock;
    int sales;
    int price; // ��ǰ ����
    int totalSalesAmount; // �� �Ǹ� �ݾ�
} Product;

int select = 0;
int id;

void CalculateInventory(Product products[]) {
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        products[i].totalSalesAmount = products[i].sales * products[i].price;
    }
}

void InputStock(Product products[]) {
    printf("�԰� �޴� ����(��ǰ ID �Է�): ");
    while (scanf("%d", &id) != 1 || id < 1 || id > MAX_PRODUCTS) {
        printf("�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���.\n");
        while (getchar() != '\n');
    }

    printf("��ǰ�� �Է�: ");
    scanf("%s", products[id - 1].name);
    printf("�԰� �Է�: ");
    scanf("%d", &products[id - 1].stock);
    printf("�Ǹ� ���� �Է�: ");
    scanf("%d", &products[id - 1].price);
}

void InputSales(Product products[]) {
    printf("�Ǹ� �޴� ����(��ǰ ID �Է�): ");
    while (scanf("%d", &id) != 1 || id < 1 || id > MAX_PRODUCTS) {
        printf("�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���.\n");
        while (getchar() != '\n');
    }

    printf("�Ǹŷ� �Է�: ");
    scanf("%d", &products[id - 1].sales);

    // �Ǹŷ��� �԰��� �ʰ��ϸ� ���� �޽��� ���
    if (products[id - 1].sales > products[id - 1].stock) {
        printf("����: �Ǹŷ��� �԰��� �ʰ��� �� �����ϴ�.\n");
        products[id - 1].sales = 0; // �Ǹŷ� �ʱ�ȭ
    }
}

void ProductStatus(Product products[]) {
    CalculateInventory(products);

    // ���� ��ǰ ���� ���
    printf("���� ��ǰ ���� �Է�(��ǰ ID �Է�): ");
    while (scanf("%d", &id) != 1 || id < 1 || id > MAX_PRODUCTS) {
        printf("�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���.\n");
        while (getchar() != '\n');
    }

    printf("��ǰ��: %s, ����: %d, �԰�: %d, �Ǹŷ�: %d, �� �Ǹ� �ݾ�: %d\n",
        products[id - 1].name, products[id - 1].price, products[id - 1].stock,
        products[id - 1].sales, products[id - 1].totalSalesAmount);
}

void AllProductStatus(Product products[]) {
    CalculateInventory(products);

    printf("��ü ��ǰ ��Ȳ:\n");
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        printf("ID: %d, ��ǰ��: %s, ����: %d, �԰�: %d, �Ǹŷ�: %d, �� �Ǹ� �ݾ�: %d\n",
            i + 1, products[i].name, products[i].price, products[i].stock,
            products[i].sales, products[i].totalSalesAmount);
    }
}

int main(void) {
    Product products[MAX_PRODUCTS] = { 0 };

    while (1) {
        printf("���ϴ� �޴��� �����ϼ���.(1. �԰�, 2. �Ǹ�, 3. ������Ȳ, 4. ��ü��Ȳ, 5. ����)\n");
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
            printf("���α׷��� �����մϴ�.\n");
            return 0;
        default:
            printf("�߸��� �����Դϴ�. �ٽ� �õ��ϼ���.\n");
            continue;
        }
    }
}
