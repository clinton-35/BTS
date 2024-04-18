//SCT221-0280/2023
//SCT221-0437/2023

#include <stdio.h>
#include <stdlib.h>

// Structure for a node of the binary search tree
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Function to create a new node
TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to find the index of a value in an array
int findIndex(int arr[], int start, int end, int value) {
    int i;
    for (i = start; i <= end; i++) {
        if (arr[i] == value)
            return i;
    }
    return -1;
}

// Function to construct BST from in-order and post-order traversals
TreeNode* bst_construct(int inorder[], int postorder[], int inStart, int inEnd, int* postIndex) {
    if (inStart > inEnd)
        return NULL;

    // Create a new node with the current postorder element
    TreeNode* root = createNode(postorder[*postIndex]);
    (*postIndex)--;

    // If this node has no children, return it
    if (inStart == inEnd)
        return root;

    // Find the index of this node in the in-order traversal
    int inIndex = findIndex(inorder, inStart, inEnd, root->data);

    // Recursively construct right subtree
    root->right = bst_construct(inorder, postorder, inIndex + 1, inEnd, postIndex);
    // Recursively construct left subtree
    root->left = bst_construct(inorder, postorder, inStart, inIndex - 1, postIndex);

    return root;
}

// Function to traverse the BST in breadth-first search order and print elements
void BFS_traversal(TreeNode* root) {
    if (root == NULL)
        return;

    // Create a queue for BFS
    TreeNode* queue[100];
    int front = -1, rear = -1;
    queue[++rear] = root;

    while (front != rear) {
        TreeNode* temp = queue[++front];
        printf("%d ", temp->data);

        if (temp->left != NULL)
            queue[++rear] = temp->left;
        if (temp->right != NULL)
            queue[++rear] = temp->right;
    }
}

int main() {
    // Provided in-order and post-order traversal outputs
    int inorder[] = {5, 10, 15, 20, 25, 30, 45};
    int postorder[] = {5, 15, 10, 25, 45, 30, 20};
    int n = sizeof(inorder) / sizeof(inorder[0]);

    // Index to traverse post-order array
    int postIndex = n - 1;

    // Construct the binary search tree
    TreeNode* root = bst_construct(inorder, postorder, 0, n - 1, &postIndex);

    // Traverse the BST in BFS order and print elements
    printf("BFS Traversal: ");
    BFS_traversal(root);

    return 0;
}