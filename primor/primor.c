#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node {
    long val;
    struct Node* next;
} Node;

Node* inserirDivisor(long divisor, Node* divisores);
int imprimirDivisores(Node* divisores, int dividendo);
void destruirDivisores(Node* divisores);

/* Verifica se um número é primo */
int main() {
	long n;
    printf("Primo?: ");
    scanf("%ld", &n);

    Node* divisores = (Node*) malloc(sizeof(Node));
    divisores->val = 1;
    divisores->next = NULL;
	for (int i = 2; i < sqrt(n); i++) {
		if (n % i == 0) {
            inserirDivisor(i, divisores);
		}
	}

    int len = imprimirDivisores(divisores, n);
    if (len <= 2)
        printf("%ld é primo\n", n);
    else
        printf("%ld não é primo\n", n);

    destruirDivisores(divisores);
    return 0;
}

Node* inserirDivisor(long val, Node* head) {
    Node* cur = head;
    while (cur->next != NULL && cur->next->val < val) {
        cur = cur->next;
    }
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->val = val;
    if (cur->next != NULL && cur->next->val > val)
        newNode->next = cur->next;
    else
        newNode->next = NULL;
    cur->next = newNode;

    return newNode;
}

int imprimirDivisores(Node* head, int a) {
    int n = 0;
    Node* cur = head;
    printf("Divisores: ");
    while (cur != NULL) {
        ++n;
        if (cur->val < sqrt(a)) {
            inserirDivisor(a/cur->val, head);
        }
        printf("%ld, ", cur->val);
        cur = cur->next;
    }
    printf("\b\b.\n");

    return n;
}

void destruirDivisores(Node* node) {
    if (node->next != NULL)
        destruirDivisores(node->next);
    free(node);
}
