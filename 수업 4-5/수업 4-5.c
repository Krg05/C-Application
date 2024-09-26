#include <stdio.h>
#define MAX_PRODUCTS 5
#pragma warning(disable: 4996)

typedef struct {
    int stock;
    int sales;
    int inventory;
    char name[100];
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
        if (scanf("%d", &select) != 1 || (select != 1 && select != 2)) {
            printf("�߸��� �����Դϴ�. �ٽ� �õ��ϼ���.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (select) {
        case 1:
            for (int i = 0; i < MAX_PRODUCTS; i++) {
                printf("��ǰ %d�� �԰� ������ �Է��ϼ���: ", i + 1);
                while (scanf("%d", &products[i].stock) != 1 || products[i].stock < 0) {
                    printf("�߸��� �Է��Դϴ�. ����� �Է��ϼ���: ");
                    while (getchar() != '\n');
                }
            }
            break;
        case 2:
            printf("��ǰ ID: ");
            while (scanf("%d", &id) != 1 || id < 1 || id > MAX_PRODUCTS) {
                printf("�߸��� ID�Դϴ�. �ٽ� �Է��ϼ���: ");
                while (getchar() != '\n');
            }
            printf("��ǰ %d�� �԰� ������ �Է��ϼ���: ", id);
            while (scanf("%d", &products[id - 1].stock) != 1 || products[id - 1].stock < 0) {
                printf("�߸��� �Է��Դϴ�. ����� �Է��ϼ���: ");
                while (getchar() != '\n');
            }
            break;
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
    printf("��� ����\n");
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        printf("��ǰ %d: %d\n", i + 1, products[i].inventory);
    }
    //�Ǹŷ�
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        if (products[i].stock < 0 || products[i].sales < 0) {
            printf("����: ��ǰ %d�� ��� �Ǹ� ������ �����Դϴ�. �����͸� Ȯ���ϼ���.\n", i + 1);
            return 1;
        }
        total_sales += products[i].sales;
        total_stock += products[i].stock;
    }
    if (total_stock == 0) {
        printf("����: �� ��� ������ 0�Դϴ�. �Ǹ����� ����� �� �����ϴ�.\n");
        return;
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
    printf("���� ���� �Ǹŵ� ��ǰ: ID %d, ��ǰ��: %s, �Ǹŷ� %d\n", max_id, products[max_id - 1].name, max_sales);
    printf("���� ���� �Ǹŵ� ��ǰ: ID %d, ��ǰ��: %s, �Ǹŷ� %d\n", min_id, products[min_id - 1].name, min_sales);
    //��� ����
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        if (products[i].inventory <= 2) {
            printf("��ǰ ID %d: ��ǰ��: %s ��� ����(%d)\n", i + 1, products[i].name, products[i].inventory);
        }
    }
}

void ProductName(Product products[]) {
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        printf("ID %d ��ǰ��: ", i + 1);
        scanf("%s", products[i].name);
    }
}

int main(void) {
    Product products[MAX_PRODUCTS] = { 0 };
    while (1) {
        printf("���ϴ� �޴��� �����ϼ���.(1. �԰�, 2. �Ǹ�, 3. ��ǰ��Ȳ, 4. ��ǰ�� �Է�, 5. ����)\n");
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
            ProductName(products);
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