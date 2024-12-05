#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable: 4996)

typedef struct {
    int id;
    char* name; // ��ǰ �̸� ���� �Ҵ�
    int stock;
    int sales;
    int price;
    int totalSalesAmount;
} Product;

// ��� ��� �Լ�
void CalculateInventory(Product* products, int count) {
    for (int i = 0; i < count; i++) {
        products[i].totalSalesAmount = products[i].sales * products[i].price;
    }
}

// ��ǰ �߰�
Product* AddProduct(Product* products, int* count) {
    (*count)++;
    products = realloc(products, sizeof(Product) * (*count));
    if (products == NULL) {
        perror("�޸� ���Ҵ� ����");
        exit(EXIT_FAILURE);
    }

    Product* newProduct = &products[(*count) - 1];
    newProduct->id = *count;
    newProduct->name = (char*)malloc(100 * sizeof(char));
    if (newProduct->name == NULL) {
        perror("�޸� �Ҵ� ����");
        exit(EXIT_FAILURE);
    }

    printf("�� ��ǰ �߰� (ID: %d)\n", newProduct->id);
    printf("��ǰ�� �Է�: ");
    while (getchar() != '\n'); // �Է� ���� ����
    fgets(newProduct->name, 100, stdin);
    strtok(newProduct->name, "\n"); // ���� ���� ����
    printf("�԰� �Է�: ");
    scanf("%d", &newProduct->stock);
    printf("�Ǹ� ���� �Է�: ");
    scanf("%d", &newProduct->price);
    newProduct->sales = 0;
    newProduct->totalSalesAmount = 0;

    printf("��ǰ�� ���������� �߰��Ǿ����ϴ�.\n");
    return products;
}

// ��ǰ ����
Product* RemoveProduct(Product* products, int* count) {
    if (*count == 0) {
        printf("������ ��ǰ�� �����ϴ�.\n");
        return products;
    }

    int id;
    printf("������ ��ǰ ID�� �Է��ϼ���: ");
    while (scanf("%d", &id) != 1 || id < 1 || id > *count) {
        printf("�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���.\n");
        while (getchar() != '\n');
    }

    // ���� ó�� (�迭 ��� �̵�)
    free(products[id - 1].name); // �̸� �޸� ����
    for (int i = id - 1; i < (*count) - 1; i++) {
        products[i] = products[i + 1];
        products[i].id = i + 1; // ID ������
    }

    (*count)--;
    products = realloc(products, sizeof(Product) * (*count));
    if (products == NULL && *count > 0) {
        perror("�޸� ���Ҵ� ����");
        exit(EXIT_FAILURE);
    }

    printf("��ǰ�� ���������� �����Ǿ����ϴ�.\n");
    return products;
}

// ��ǰ �԰�
void InputStock(Product* products, int count) {
    int id;
    printf("�԰� �޴� ����(��ǰ ID �Է�): ");
    while (scanf("%d", &id) != 1 || id < 1 || id > count) {
        printf("�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���.\n");
        while (getchar() != '\n');
    }

    printf("�԰� �Է�: ");
    int stockIncrease;
    scanf("%d", &stockIncrease);
    products[id - 1].stock += stockIncrease;
    printf("��ǰ ID %d�� �԰��� ������Ʈ�Ǿ����ϴ�.\n", id);
}

// ��ǰ �Ǹ�
void InputSales(Product* products, int count) {
    int id;
    printf("�Ǹ� �޴� ����(��ǰ ID �Է�): ");
    while (scanf("%d", &id) != 1 || id < 1 || id > count) {
        printf("�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���.\n");
        while (getchar() != '\n');
    }

    printf("�Ǹŷ� �Է�: ");
    int salesAmount;
    scanf("%d", &salesAmount);

    if (salesAmount > products[id - 1].stock) {
        printf("����: �Ǹŷ��� �԰��� �ʰ��� �� �����ϴ�.\n");
    }
    else {
        products[id - 1].stock -= salesAmount;
        products[id - 1].sales += salesAmount;
        printf("��ǰ ID %d�� �ǸŰ� �Ϸ�Ǿ����ϴ�.\n", id);
    }
}

// ���� ��ǰ ��Ȳ
void ProductStatus(Product* products, int count) {
    int id;
    CalculateInventory(products, count);

    printf("���� ��ǰ ���� �Է�(��ǰ ID �Է�): ");
    while (scanf("%d", &id) != 1 || id < 1 || id > count) {
        printf("�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���.\n");
        while (getchar() != '\n');
    }

    Product* p = &products[id - 1];
    printf("��ǰ��: %s, ����: %d, �԰�: %d, �Ǹŷ�: %d, �� �Ǹ� �ݾ�: %d\n",
        p->name, p->price, p->stock, p->sales, p->totalSalesAmount);
}

// ��ü ��ǰ ��Ȳ
void AllProductStatus(Product* products, int count) {
    CalculateInventory(products, count);

    printf("��ü ��ǰ ��Ȳ:\n");
    for (int i = 0; i < count; i++) {
        Product* p = &products[i];
        printf("ID: %d, ��ǰ��: %s, ����: %d, �԰�: %d, �Ǹŷ�: %d, �� �Ǹ� �ݾ�: %d\n",
            p->id, p->name, p->price, p->stock, p->sales, p->totalSalesAmount);
    }
}


// ��ǰ ����
void SaveProducts(Product* products, int count) {
    FILE* file = fopen("products.dat", "wb");
    if (file == NULL) {
        printf("������ �����ϴµ� �����߽��ϴ�.\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        // ��ǰ �̸��� ���� ����
        int nameLength = strlen(products[i].name) + 1;
        fwrite(&nameLength, sizeof(int), 1, file);
        fwrite(products[i].name, sizeof(char), nameLength, file);
        fwrite(&products[i], sizeof(Product) - sizeof(char*), 1, file);
    }
    fclose(file);
    printf("��ǰ ������ ���Ͽ� ����Ǿ����ϴ�.\n");
}

// ��ǰ �ҷ�����
Product* LoadProducts(Product* products, int* count) {
    FILE* file = fopen("products.dat", "rb");
    if (file == NULL) {
        printf("����� ������ �����ϴ�.\n");
        return products;
    }

    int tempCount = 0;
    Product* tempProducts = NULL;

    while (1) {
        int nameLength;
        if (fread(&nameLength, sizeof(int), 1, file) != 1) break;

        tempCount++;
        tempProducts = realloc(tempProducts, sizeof(Product) * tempCount);
        if (tempProducts == NULL) {
            perror("�޸� ���Ҵ� ����");
            fclose(file);
            return products;
        }

        Product* current = &tempProducts[tempCount - 1];
        current->name = (char*)malloc(nameLength * sizeof(char));
        if (current->name == NULL) {
            perror("�޸� �Ҵ� ����");
            fclose(file);
            return products;
        }

        fread(current->name, sizeof(char), nameLength, file);
        fread(current, sizeof(Product) - sizeof(char*), 1, file);
    }

    fclose(file);
    free(products); // ���� �����͸� ����
    *count = tempCount;
    printf("��ǰ ������ ���Ͽ��� �ҷ��������ϴ�.\n");
    return tempProducts;
}

// ���� �Լ�
int main(void) {
    int productCount = 0;
    int select = 0;
    Product* products = NULL;

    printf("�ʱ� ��ǰ ���� �Է��ϼ���: ");
    if (scanf("%d", &productCount) != 1 || productCount < 0) {
        printf("�߸��� �Է��Դϴ�. ���α׷��� �����մϴ�.\n");
        return -1;
    }

    products = (Product*)malloc(sizeof(Product) * productCount);
    if (products == NULL) {
        perror("�޸� �Ҵ� ����");
        return -1;
    }

    for (int i = 0; i < productCount; i++) {
        products[i].id = i + 1;
        products[i].name = (char*)malloc(100 * sizeof(char));
        if (products[i].name == NULL) {
            perror("�޸� �Ҵ� ����");
            for (int j = 0; j < i; j++) {
                free(products[j].name); // ������ �Ҵ�� �޸� ����
            }
            free(products);
            return -1;
        }
        printf("��ǰ %d�� �̸��� �Է��ϼ���: ", i + 1);
        while (getchar() != '\n'); // �Է� ���� ����
        fgets(products[i].name, 100, stdin);
        strtok(products[i].name, "\n"); // ���� ���� ����
        printf("�԰� �Է�: ");
        scanf("%d", &products[i].stock);
        printf("�Ǹ� ���� �Է�: ");
        scanf("%d", &products[i].price);
        products[i].sales = 0;
        products[i].totalSalesAmount = 0;
    }

    while (1) {
        printf("\n�޴� ����: 1. �԰�, 2. �Ǹ�, 3. ������Ȳ, 4. ��ü��Ȳ, 5. ��ǰ�߰�, 6. ��ǰ����, 7. ��ǰ��������, 8. ��ǰ�����ҷ�����, 9. ����\n");
        if (scanf("%d", &select) != 1) {
            printf("�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (select) {
        case 1:
            InputStock(products, productCount);
            break;
        case 2:
            InputSales(products, productCount);
            break;
        case 3:
            ProductStatus(products, productCount);
            break;
        case 4:
            AllProductStatus(products, productCount);
            break;
        case 5:
            products = AddProduct(products, &productCount);
            break;
        case 6:
            products = RemoveProduct(products, &productCount);
            break;
        case 7:
            SaveProducts(products, productCount);
            break;
        case 8:
            products = LoadProducts(products, &productCount);
            break;
        case 9:
            for (int i = 0; i < productCount; i++) {
                free(products[i].name); // name �޸� ����
            }
            free(products);
            printf("���α׷��� �����մϴ�.\n");
            return 0;
        default:
            printf("�߸��� �����Դϴ�. �ٽ� �õ��ϼ���.\n");
            break;
        }
    }
}