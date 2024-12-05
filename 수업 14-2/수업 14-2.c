#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable: 4996)

typedef struct {
    int id;
    char* name; // 상품 이름 동적 할당
    int stock;
    int sales;
    int price;
    int totalSalesAmount;
} Product;

// 재고 계산 함수
void CalculateInventory(Product* products, int count) {
    for (int i = 0; i < count; i++) {
        products[i].totalSalesAmount = products[i].sales * products[i].price;
    }
}

// 상품 추가
Product* AddProduct(Product* products, int* count) {
    (*count)++;
    products = realloc(products, sizeof(Product) * (*count));
    if (products == NULL) {
        perror("메모리 재할당 실패");
        exit(EXIT_FAILURE);
    }

    Product* newProduct = &products[(*count) - 1];
    newProduct->id = *count;
    newProduct->name = (char*)malloc(100 * sizeof(char));
    if (newProduct->name == NULL) {
        perror("메모리 할당 실패");
        exit(EXIT_FAILURE);
    }

    printf("새 상품 추가 (ID: %d)\n", newProduct->id);
    printf("상품명 입력: ");
    while (getchar() != '\n'); // 입력 버퍼 비우기
    fgets(newProduct->name, 100, stdin);
    strtok(newProduct->name, "\n"); // 개행 문자 제거
    printf("입고량 입력: ");
    scanf("%d", &newProduct->stock);
    printf("판매 가격 입력: ");
    scanf("%d", &newProduct->price);
    newProduct->sales = 0;
    newProduct->totalSalesAmount = 0;

    printf("상품이 성공적으로 추가되었습니다.\n");
    return products;
}

// 상품 삭제
Product* RemoveProduct(Product* products, int* count) {
    if (*count == 0) {
        printf("삭제할 상품이 없습니다.\n");
        return products;
    }

    int id;
    printf("삭제할 상품 ID를 입력하세요: ");
    while (scanf("%d", &id) != 1 || id < 1 || id > *count) {
        printf("잘못된 입력입니다. 다시 입력하세요.\n");
        while (getchar() != '\n');
    }

    // 삭제 처리 (배열 요소 이동)
    free(products[id - 1].name); // 이름 메모리 해제
    for (int i = id - 1; i < (*count) - 1; i++) {
        products[i] = products[i + 1];
        products[i].id = i + 1; // ID 재정렬
    }

    (*count)--;
    products = realloc(products, sizeof(Product) * (*count));
    if (products == NULL && *count > 0) {
        perror("메모리 재할당 실패");
        exit(EXIT_FAILURE);
    }

    printf("상품이 성공적으로 삭제되었습니다.\n");
    return products;
}

// 상품 입고
void InputStock(Product* products, int count) {
    int id;
    printf("입고 메뉴 실행(상품 ID 입력): ");
    while (scanf("%d", &id) != 1 || id < 1 || id > count) {
        printf("잘못된 입력입니다. 다시 입력하세요.\n");
        while (getchar() != '\n');
    }

    printf("입고량 입력: ");
    int stockIncrease;
    scanf("%d", &stockIncrease);
    products[id - 1].stock += stockIncrease;
    printf("상품 ID %d의 입고량이 업데이트되었습니다.\n", id);
}

// 상품 판매
void InputSales(Product* products, int count) {
    int id;
    printf("판매 메뉴 실행(상품 ID 입력): ");
    while (scanf("%d", &id) != 1 || id < 1 || id > count) {
        printf("잘못된 입력입니다. 다시 입력하세요.\n");
        while (getchar() != '\n');
    }

    printf("판매량 입력: ");
    int salesAmount;
    scanf("%d", &salesAmount);

    if (salesAmount > products[id - 1].stock) {
        printf("오류: 판매량이 입고량을 초과할 수 없습니다.\n");
    }
    else {
        products[id - 1].stock -= salesAmount;
        products[id - 1].sales += salesAmount;
        printf("상품 ID %d의 판매가 완료되었습니다.\n", id);
    }
}

// 개별 상품 현황
void ProductStatus(Product* products, int count) {
    int id;
    CalculateInventory(products, count);

    printf("개별 상품 정보 입력(상품 ID 입력): ");
    while (scanf("%d", &id) != 1 || id < 1 || id > count) {
        printf("잘못된 입력입니다. 다시 입력하세요.\n");
        while (getchar() != '\n');
    }

    Product* p = &products[id - 1];
    printf("상품명: %s, 가격: %d, 입고량: %d, 판매량: %d, 총 판매 금액: %d\n",
        p->name, p->price, p->stock, p->sales, p->totalSalesAmount);
}

// 전체 상품 현황
void AllProductStatus(Product* products, int count) {
    CalculateInventory(products, count);

    printf("전체 상품 현황:\n");
    for (int i = 0; i < count; i++) {
        Product* p = &products[i];
        printf("ID: %d, 상품명: %s, 가격: %d, 입고량: %d, 판매량: %d, 총 판매 금액: %d\n",
            p->id, p->name, p->price, p->stock, p->sales, p->totalSalesAmount);
    }
}


// 상품 저장
void SaveProducts(Product* products, int count) {
    FILE* file = fopen("products.dat", "wb");
    if (file == NULL) {
        printf("파일을 저장하는데 실패했습니다.\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        // 상품 이름의 길이 저장
        int nameLength = strlen(products[i].name) + 1;
        fwrite(&nameLength, sizeof(int), 1, file);
        fwrite(products[i].name, sizeof(char), nameLength, file);
        fwrite(&products[i], sizeof(Product) - sizeof(char*), 1, file);
    }
    fclose(file);
    printf("상품 정보가 파일에 저장되었습니다.\n");
}

// 상품 불러오기
Product* LoadProducts(Product* products, int* count) {
    FILE* file = fopen("products.dat", "rb");
    if (file == NULL) {
        printf("저장된 파일이 없습니다.\n");
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
            perror("메모리 재할당 실패");
            fclose(file);
            return products;
        }

        Product* current = &tempProducts[tempCount - 1];
        current->name = (char*)malloc(nameLength * sizeof(char));
        if (current->name == NULL) {
            perror("메모리 할당 실패");
            fclose(file);
            return products;
        }

        fread(current->name, sizeof(char), nameLength, file);
        fread(current, sizeof(Product) - sizeof(char*), 1, file);
    }

    fclose(file);
    free(products); // 기존 데이터를 해제
    *count = tempCount;
    printf("상품 정보가 파일에서 불러와졌습니다.\n");
    return tempProducts;
}

// 메인 함수
int main(void) {
    int productCount = 0;
    int select = 0;
    Product* products = NULL;

    printf("초기 상품 수를 입력하세요: ");
    if (scanf("%d", &productCount) != 1 || productCount < 0) {
        printf("잘못된 입력입니다. 프로그램을 종료합니다.\n");
        return -1;
    }

    products = (Product*)malloc(sizeof(Product) * productCount);
    if (products == NULL) {
        perror("메모리 할당 실패");
        return -1;
    }

    for (int i = 0; i < productCount; i++) {
        products[i].id = i + 1;
        products[i].name = (char*)malloc(100 * sizeof(char));
        if (products[i].name == NULL) {
            perror("메모리 할당 실패");
            for (int j = 0; j < i; j++) {
                free(products[j].name); // 이전에 할당된 메모리 해제
            }
            free(products);
            return -1;
        }
        printf("상품 %d의 이름을 입력하세요: ", i + 1);
        while (getchar() != '\n'); // 입력 버퍼 비우기
        fgets(products[i].name, 100, stdin);
        strtok(products[i].name, "\n"); // 개행 문자 제거
        printf("입고량 입력: ");
        scanf("%d", &products[i].stock);
        printf("판매 가격 입력: ");
        scanf("%d", &products[i].price);
        products[i].sales = 0;
        products[i].totalSalesAmount = 0;
    }

    while (1) {
        printf("\n메뉴 선택: 1. 입고, 2. 판매, 3. 개별현황, 4. 전체현황, 5. 상품추가, 6. 상품삭제, 7. 상품정보저장, 8. 상품정보불러오기, 9. 종료\n");
        if (scanf("%d", &select) != 1) {
            printf("잘못된 입력입니다. 다시 시도하세요.\n");
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
                free(products[i].name); // name 메모리 해제
            }
            free(products);
            printf("프로그램을 종료합니다.\n");
            return 0;
        default:
            printf("잘못된 선택입니다. 다시 시도하세요.\n");
            break;
        }
    }
}