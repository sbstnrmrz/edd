// Participantes: 
// Sebastian Ramirez C.I: 31567908
// Angel Vivas       C.I: 30890743

#include "defs.h"

struct _node_t {
    std::string data;
    struct _node_t *left;
    struct _node_t *right;
};

typedef struct _node_t node_t;

typedef struct {
    node_t *root;
    int *node_size;
} tree_t;

tree_t tree_init() {
    return (tree_t) {
        .root = NULL,
        .node_size = new int,
    }; 
}

int tree_height(node_t *root) {
    if (root == NULL) {
        return 0;
    }

    int left = tree_height(root->left);
    int right = tree_height(root->right);

    return (left >= right ? left : right)+1; 
//  return max(left, right)+1;
}

void tree_insert(tree_t *tree, std::string data) {
    if (tree->root == NULL) {
        tree->root = new node_t;
        tree->root->data = data;
        (*tree->node_size)++;
        tree->root->left = NULL;
        tree->root->right = NULL;
        return;
    } 
    node_t *node = tree->root;

    int cmp = strcasecmp(data.c_str(), node->data.c_str()); 
    if (cmp <= 0) {
        if (node->left == NULL) {
            node->left = new node_t; 
            node->left->data = data;
            (*tree->node_size)++;
            return;
        }

        tree_t new_tree = {
            .root = node->left,
            .node_size = tree->node_size,
        };
        tree_insert(&new_tree, data);
    } 
    if (cmp > 0) {
        if (node->right == NULL) {
            node->right = new node_t; 
            node->right->data = data;
            (*tree->node_size)++;
            return;
        }
        
        tree_t new_tree = {
            .root = node->right,
            .node_size = tree->node_size,
        };
        tree_insert(&new_tree, data);
    }
}

bool tree_is_balanced(tree_t tree) {
    if (*tree.node_size == pow(2, tree_height(tree.root))-1 ) {
        return true;
    }
    return false;
}

void tree_print_post_order_traversal(tree_t tree) {
    if (tree.root == NULL) {
        return;
    }
    tree_t left = {
        .root = tree.root->left, 
        .node_size = tree.node_size,
    };
    tree_t right = {
        .root = tree.root->right, 
        .node_size = tree.node_size,
    };
    tree_print_post_order_traversal(left);
    tree_print_post_order_traversal(right);
    printf("%s ", tree.root->data.c_str());
} 
void tree_print_indented(node_t* root, int level) {
    if (root == NULL) {
        return;
    }
    level++;

    tree_print_indented(root->right, level);

    for (int i = 0; i < level; i++) {
        printf("  ");
    }

    printf("%s\n", root->data.c_str());

    tree_print_indented(root->left, level);
}

int main(int argc, char *argv[]) {
    fstream f;
    f.open("arbol.txt", ios::in);
    if (!f.is_open()) {
        printf("Error abriendo el archivo arbol.txt!\n");
        exit(1);
    }

    std::string line;
    int cnt = 0;
    while (std::getline(f, line)) {
        tree_t tree = tree_init();
        char str[128] = {0};
        strcpy(str, line.c_str());
        line.length()

        printf("Arbol %d:\n", cnt+1);

        printf("  Nodos: ");
        char *tokens = strtok(str, " ");
        while (tokens != NULL) {
            tree_insert(&tree, tokens); 
            printf("%s ", tokens);
            tokens = strtok(NULL, " ");
        }
        printf("\n\n");
        
        tree_print_indented(tree.root, 0);

        printf("\n  Cantidad de nodos: %d\n", *tree.node_size);
        printf("  Altura: %d\n", tree_height(tree.root));
        printf("  Post-Orden: ");
        tree_print_post_order_traversal(tree);
        printf("\n  Equilibrado: %s", tree_is_balanced(tree) ? "si" : "no");
        printf("\n\n");
        cnt++;
    }

    return 0;
}
