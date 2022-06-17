#include <stdlib.h>

#ifndef B_T_NODE
    #include "./node.h"
    #define B_T_NODE
#endif
#include "./queue_b_t_node.c"

#define PREORDER 1
#define INORDER 2
#define POSTORDER 3

b_t_node *create_b_t_node() {
    b_t_node *newNode;
    if (!(newNode = (b_t_node *) malloc(sizeof(b_t_node)))) {
        puts("Retry allocating tree");
        return NULL;
    }
    newNode->info = 0;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

b_t_node *locate(b_t_node *root, int info) {
    queue q = qCreate();
    b_t_node *currentNode;
    enqueue(&q, root);
    while (!is_empty(q)) {
        currentNode = dequeue(&q);
        if(currentNode->info == info) {
            break;
        }
        enqueue(&q, currentNode->left);
        enqueue(&q, currentNode->right);
    }
    delete(&q);
    return currentNode;
}

b_t_node *add(b_t_node** root, int locData, short pos, int newData) {
    b_t_node* newNode = create_b_t_node();
    if (*root) {
        b_t_node* locNode = locate(*root, locData);
        if(pos == '1')
            locNode->right = newNode;
        else if(pos == '0')
            locNode->left = newNode;
        else
            return NULL;
    } else
        *root = newNode;
    return newNode;
}

bool print_bfs(b_t_node* root) {
    queue q = qCreate();
    b_t_node *currentNode;
    enqueue(&q, root);
    while (!is_empty(q)) {
        currentNode = dequeue(&q);
        printf("%d", currentNode->info);
        enqueue(&q, currentNode->left);
        enqueue(&q, currentNode->right);
    }
    delete(&q);
    return true;
}

bool print_dfs(b_t_node* root, int order) {
    return ( order == 1 ? \
        print_dfs_preorder(root) : \
        ( order == 2 ? \
        print_dfs_inorder(root) : \
        ( order == 3 ? \
        print_dfs_postorder(root) : \
        false ) ) );
}

bool print_dfs_preorder(b_t_node* root) {
    if (root) {
        printf("%d", root->info);
        print_dfs_preorder(root->left);
        print_dfs_preorder(root->right);
    }
    return true;
}

bool print_dfs_postorder(b_t_node* root) {
    if (root) {
        print_dfs_postorder(root->left);
        print_dfs_postorder(root->right);
        printf("%d", root->info);
    }
    return true;
}

bool print_dfs_inorder(b_t_node* root) {
    if (root) {
        print_dfs_inorder(root->left);
        printf("%d", root->info);
        print_dfs_inorder(root->right);
    }
    return true;
}

bool mirror(b_t_node* root) {
    stack s = sCreate();
}