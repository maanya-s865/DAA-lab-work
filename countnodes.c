
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 50000

struct Node {
    int data;
    struct Node *left, *right;
};

struct Node* createNode(int value) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));

    if (node == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    node->data = value;
    node->left = NULL;
    node->right = NULL;

    return node;
}

struct Node* buildCompleteTree(int a[], int n, int i) {
    struct Node* root;

    if (i >= n)
        return NULL;

    root = createNode(a[i]);

    root->left = buildCompleteTree(a, n, 2 * i + 1);
    root->right = buildCompleteTree(a, n, 2 * i + 2);

    return root;
}

int leftHeight(struct Node* root) {
    int h = 0;

    while (root != NULL) {
        h++;
        root = root->left;
    }

    return h;
}

int rightHeight(struct Node* root) {
    int h = 0;

    while (root != NULL) {
        h++;
        root = root->right;
    }

    return h;
}

int countNodes(struct Node* root) {
    int lh, rh;

    if (root == NULL)
        return 0;

    lh = leftHeight(root);
    rh = rightHeight(root);

    if (lh == rh)
        return (1 << lh) - 1;

    return 1 + countNodes(root->left)
             + countNodes(root->right);
}

int main() {
    static int a[MAX];
    struct Node* root;
    int n, i, result;
    clock_t start, end;
    double time_taken;

    printf("Enter number of nodes (max %d): ", MAX);
    scanf("%d", &n);

    if (n < 1 || n > MAX) {
        printf("Invalid size!\n");
        return 1;
    }

    for (i = 0; i < n; i++)
        a[i] = i + 1;

    root = buildCompleteTree(a, n, 0);

    start = clock();
    result = countNodes(root);
    end = clock();

    time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Number of nodes = %d\n", result);
    printf("Execution Time = %f seconds\n", time_taken);

    return 0;
}
