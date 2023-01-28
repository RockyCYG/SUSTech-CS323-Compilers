#include "node.hpp"

void printAST(Node *node, int level) {
    for (int i = 0; i < level; i++) {
        printf("  ");
    }
    cout << node->name;
    if (!node->flag) {
        printf(" (%d)", node->line);
    }
    printf("\n");
    for (Node *child: node->children) {
        printAST(child, level + 1);
    }
}