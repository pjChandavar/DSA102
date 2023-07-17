#include<stdio.h>
#include<stdlib.h>
struct Node
{
  int data;
  struct Node *left;
  struct Node *right;
};
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
struct Node* insert(struct Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    } else {
        if (data <= root->data) {
            root->left = insert(root->left, data);
        } else {
            root->right = insert(root->right, data);
        }
        return root;
    }
}
void displayTree(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        displayTree(root->left);
        displayTree(root->right);
    }
}
int main() {
    struct Node* root = NULL;

    // Inserting elements into the binary tree
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 8);
    root = insert(root, 12);

    // Printing the elements in the binary tree (inorder traversal)
    /*printf("Inorder traversal: ");
    inorderTraversal(root);
    printf("\n");*/
    displayTree(root);
    return 0;
}
