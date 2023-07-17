#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node
{
    int key;
    struct node* left;
    struct node* right;
    int height;
};

struct node* createNode(int key)
{
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

int getHeight(struct node* n)
 {
    if (n == NULL)
        return 0;
    return n->height;
}

int getBalanceFactor(struct node* n)
{
    if (n == NULL)
        return 0;
    return getHeight(n->left) - getHeight(n->right);
}

void updateHeight(struct node* n)
{
    int leftHeight = getHeight(n->left);
    int rightHeight = getHeight(n->right);
    n->height = (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
}

struct node* rightRotate(struct node* y)
{
    struct node* x = y->left;
    struct node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// Function to perform a left rotation
struct node* leftRotate(struct node* x) {
    struct node* y = x->right;
    struct node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// Function to find the minimum key node in a subtree rooted at 'node'
struct node* findMinKeyNode(struct node* node) {
    struct node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

struct node* insert(struct node* root, int key) {
    if (root == NULL)
        return createNode(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key && key == root->key)
        root->right = insert(root->right, key);
    else
        return root;

    updateHeight(root);

    int balanceFactor = getBalanceFactor(root);

    // Left Left Case
    if (balanceFactor > 1 && key < root->left->key)
        return rightRotate(root);

    // Right Right Case
    if (balanceFactor < -1 && key > root->right->key)
        return leftRotate(root);

    // Left Right Case
    if (balanceFactor > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Case
    if (balanceFactor < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to delete a key from the AVL tree
struct node* delete(struct node* root, int key) {
    if (root == NULL) {
        printf("Key %d not found.\n", key);
        return root;
    }

    if (key < root->key)
        root->left = delete(root->left, key);
    else if (key > root->key)
        root->right = delete(root->right, key);
    else {

        if (root->key == key) {

            if (root->left == NULL && root->right == NULL)
                {
                struct node* temp = root->left ? root->left : root->right;

                // No child case
                if (temp == NULL)
                {
                    temp = root;
                    root = NULL;
                } else // One child case
                    *root = *temp; // Copy the contents of the non-empty child

                free(temp);
                printf("Key %d deleted successfully.\n", key);
            } else {
                // Node with two children
                struct node* temp = findMinKeyNode(root->right); // Find the minimum key node in the right subtree
                root->key = temp->key; // Copy the minimum key to this node
                root->right = delete(root->right, temp->key); // Delete the minimum key node in the right subtree
                printf("Key %d deleted successfully.\n", key);
            }
        }
    }

    if (root == NULL)
        return root;

    updateHeight(root);

    int balanceFactor = getBalanceFactor(root);

    // Left Left Case
    if (balanceFactor > 1 && getBalanceFactor(root->left) >= 0)
        return rightRotate(root);
// Left Right Case
    if (balanceFactor > 1 && getBalanceFactor(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balanceFactor < -1 && getBalanceFactor(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balanceFactor < -1 && getBalanceFactor(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to perform inorder traversal of the AVL tree and write to file
void inorder(struct node* root, FILE* file) {
    if (root == NULL)
        return;
    inorder(root->left, file);
    fprintf(file, "%d ", root->key);
    inorder(root->right, file);
}

// Function to perform postorder traversal of the AVL tree and write to file
void postorder(struct node* root, FILE* file) {
    if (root == NULL)
        return;
    postorder(root->left, file);
    postorder(root->right, file);
    fprintf(file, "%d ", root->key);
}

// Function to perform preorder traversal of the AVL tree and write to file
void preorder(struct node* root, FILE* file) {
    if (root == NULL)
        return;
    fprintf(file, "%d ", root->key);
    preorder(root->left, file);
    preorder(root->right, file);
}

int main() {
    FILE* fp_random = fopen("random.txt", "w");
    struct node* root = NULL;
    int choice, key;

    srand(time(0)); // Seed the random number generator with the current time

    while (1) {
        printf("1. Insert (Random Key)\n");
        printf("2. Delete\n");
        printf("3. Display Preorder after balancing of avl\n");
        printf("4. Display Inorder \n");
        printf("5. Display Postorder\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                key = rand() % 100;
                root = insert(root, key);
                fprintf(fp_random, "%d\n", key);
                printf("Node (%d) inserted successfully.\n", key);
                break;


            case 2:
                printf("Enter the key to delete: ");
                scanf("%d", &key);
                root = delete(root, key);
                printf("\n");
                break;
            case 3: {
                FILE* preorderFile = fopen("preorder.txt", "w");
                if (preorderFile == NULL) {
                    printf("Error opening the file.\n");
                    return 1;
                }
                printf("Preorder Traversal:\n");
                preorder(root, preorderFile);
                fclose(preorderFile);
                printf("\n");
                break;
            }
            case 4: {
                FILE* inorderFile = fopen("inorder.txt", "w");
                if (inorderFile == NULL) {
                    printf("Error opening the file.\n");
                    return 1;
                }
                printf("Inorder Traversal:\n");
                inorder(root, inorderFile);
                fclose(inorderFile);
                printf("\n");
                break;
            }
            case 5: {
                FILE* postorderFile = fopen("postorder.txt", "w");
                if (postorderFile == NULL) {
                    printf("Error opening the file.\n");
                    return 1;
                }
                printf("Postorder Traversal:\n");
                postorder(root, postorderFile);
                fclose(postorderFile);
                printf("\n");
                break;
            }
            case 6:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
