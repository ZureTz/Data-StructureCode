#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coe;
    int exp;
    struct Node* next;
}Node;

struct Node* createNode(int coe, int exp) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coe = coe;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}

struct Node* insertNode(struct Node* head, int coe, int exp) {
    struct Node* newNode = createNode(coe, exp);
    if (head == NULL) {
        return newNode;
    }
    struct Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    return head;
}

void printPol(struct Node* head) {
    struct Node* current = head;
    if (current != NULL && current->exp != 0 && current->coe != 0) printf("%d %d", current->coe, current->exp);
    current = current->next;
    while (current != NULL) {
        if (current->coe != 0) {
            if (current->exp != 0) {
                printf(",%d %d", current->coe, current->exp);
            }
            else {
                printf(",%d", current->coe);
            }
        }
        current = current->next;
    }
    printf("\n");
}

struct Node* addPol(struct Node* pol1, struct Node* pol2) {
    struct Node* result = NULL;
    struct Node* current1 = pol1;
    struct Node* current2 = pol2;

    while (current1 != NULL && current2 != NULL) {
        if (current1->exp > current2->exp) {
            result = insertNode(result, current1->coe, current1->exp);
            current1 = current1->next;
        }
        else if (current1->exp < current2->exp) {
            result = insertNode(result, current2->coe, current2->exp);
            current2 = current2->next;
        }
        else {
            int sum = current1->coe + current2->coe;
            if (sum != 0) {
                result = insertNode(result, sum, current1->exp);
            }
            current1 = current1->next;
            current2 = current2->next;
        }
    }

    while (current1 != NULL) {
        result = insertNode(result, current1->coe, current1->exp);
        current1 = current1->next;
    }

    while (current2 != NULL) {
        result = insertNode(result, current2->coe, current2->exp);
        current2 = current2->next;
    }

    return result;
}

struct Node* multiplyPol(struct Node* pol1, struct Node* pol2) {
    struct Node* result = NULL;
    struct Node* current1 = pol1;

    while (current1 != NULL) {
        struct Node* current2 = pol2;
        while (current2 != NULL) {
            int product_coe = current1->coe * current2->coe;
            int product_exp = current1->exp + current2->exp;
            result = insertNode(result, product_coe, product_exp);
            current2 = current2->next;
        }
        current1 = current1->next;
    }

    return result;
}

int main() {
    int size1, size2;
    scanf("%d %d", &size1, &size2);
    struct Node* pol1 = NULL;
    struct Node* pol2 = NULL;
    scanf("/n");
    for (int i = 0; i < size1; i++) {
        int coe, exp;
        scanf("%d %d,", &coe, &exp);
        pol1 = insertNode(pol1, coe, exp);
    }
    scanf("/n");
    for (int i = 0; i < size2; i++) {
        int coe, exp;
        scanf("%d %d,", &coe, &exp);
        pol2 = insertNode(pol2, coe, exp);
    }
    struct Node* sum = addPol(pol1, pol2);
    printPol(sum);

    return 0;
}