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
    printf("�԰� �޴� ����(��ǰ ID �Է�): ");
    while (scanf("%d", &id) != 1 || id < 1 || id > MAX_PRODUCTS) {
        printf("�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���.\n");
        while (getchar() != '\n'); // ���۸� ���ϴ�.
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

    if (products[id - 1].sales > products[id - 1].stock) {
        printf("����: �Ǹŷ��� �԰��� �ʰ��� �� �����ϴ�.\n");
        products[id - 1].sales = 0;
    }
}

void ProductStatus(Product products[]) {
    CalculateInventory(products);

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

void SaveProducts(Product products[]) {
    FILE* file = fopen("products.dat", "wb");
    if (file == NULL) {
        printf("������ �����ϴµ� �����߽��ϴ�.\n");
        return;
    }
    fwrite(products, sizeof(Product), MAX_PRODUCTS, file);
    fclose(file);
    printf("��ǰ ������ ���Ͽ� ����Ǿ����ϴ�.\n");
}

void LoadProducts(Product products[]) {
    FILE* file = fopen("products.dat", "rb");
    if (file == NULL) {
        printf("����� ������ �����ϴ�.\n");
        return;
    }
    fread(products, sizeof(Product), MAX_PRODUCTS, file);
    fclose(file);
    printf("��ǰ ������ ���Ͽ��� �ҷ��������ϴ�.\n");
}

int main(void) {
    Product products[MAX_PRODUCTS] = { 0 };

    while (1) {
        printf("���ϴ� �޴��� �����ϼ���.(1. �԰�, 2. �Ǹ�, 3. ������Ȳ, 4. ��ü��Ȳ, 5. ��ǰ��������, 6. ��ǰ������������, 7. ����)\n");
        if (scanf("%d", &select) != 1) {
            printf("�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���.\n");
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
            printf("���α׷��� �����մϴ�.\n");
            return 0;
        default:
            printf("�߸��� �����Դϴ�. �ٽ� �õ��ϼ���.\n");
            break;
        }
    }
}