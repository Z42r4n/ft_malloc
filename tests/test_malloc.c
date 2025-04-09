/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarran <zarran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:51:07 by ymoutaou          #+#    #+#             */
/*   Updated: 2025/04/09 15:27:15 by zarran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/allocator.h"

// Function to print node information in dot format
void print_dot_node(FILE *f, char *node)
{
    if (!node) return;

    int value = get_value(node);
    const char *color = get_color(node) == RED ? "red" : "black";
    const char *fontcolor = get_color(node) == RED ? "white" : "white";

    fprintf(f, "    \"%p\" [label=\"%d\", style=filled, fillcolor=%s, fontcolor=%s];\n", 
            (void *)node, value, color, fontcolor);
}

// Function to print edges between parent and children
void print_dot_edges(FILE *f, char *node)
{
    if (!node) return;

    char *left = get_left(node);
    char *right = get_right(node);

    if (left)
        fprintf(f, "    \"%p\" -> \"%p\";\n", (void *)node, (void *)left);
    if (right)
        fprintf(f, "    \"%p\" -> \"%p\";\n", (void *)node, (void *)right);

    print_dot_edges(f, left);
    print_dot_edges(f, right);
}

// Helper function to print nodes recursively
void print_nodes(FILE *f, char *n)
{
    if (!n) return;
    print_dot_node(f, n);
    print_nodes(f, get_left(n));
    print_nodes(f, get_right(n));
}

// Function to generate dot file
void generate_dot(char *root, const char *filename)
{
    if (root == NULL) {
        fprintf(stderr, "Error: root is NULL in generate_dot\n");
        return;
    }

    if (filename == NULL) {
        fprintf(stderr, "Error: filename is NULL\n");
        return;
    }

    printf("Attempting to open file: %s\n", filename);
    
    FILE *f = fopen(filename, "w");
    if (!f)
    {
        perror("fopen");
        return;
    }

    fprintf(f, "digraph RBTree {\n");
    fprintf(f, "    node [shape=circle, fontname=\"Arial\"];\n");

    // Print all nodes
    print_nodes(f, root);
    // Print edges
    print_dot_edges(f, root);

    fprintf(f, "}\n");
    fclose(f);
}

// void test_malloc_basic() {
//     printf("Test 1: Basic malloc allocation\n");
//     int *ptr = (int *)malloc(sizeof(int));
//     if (!ptr) {
//         printf("❌ malloc failed to allocate memory\n");
//         return;
//     }
//     *ptr = 42;
//     printf("✅ malloc allocated memory and stored value: %d\n", *ptr);
//     free(ptr);
// }

// void test_malloc_large() {
//     printf("Test 2: Large malloc allocation\n");
//     size_t size = 1024 * 1024 * 10; // 10MB
//     char *buffer = (char *)malloc(size);
//     if (!buffer) {
//         printf("❌ malloc failed to allocate large memory block\n");
//         return;
//     }
//     memset(buffer, 'A', size);
//     printf("✅ malloc successfully allocated and wrote to large block\n");
//     free(buffer);
// }

// void test_malloc_multiple() {
//     printf("Test 3: Multiple malloc allocations\n");
//     int *a = (int *)malloc(sizeof(int));
//     double *b = (double *)malloc(sizeof(double));
//     char *c = (char *)malloc(50 * sizeof(char));

//     if (!a || !b || !c) {
//         printf("❌ malloc failed to allocate multiple blocks\n");
//         return;
//     }

//     *a = 100;
//     *b = 3.14;
//     strcpy(c, "Hello, malloc!");

//     printf("✅ Allocated multiple blocks: %d, %.2f, %s\n", *a, *b, c);

//     free(a);
//     free(b);
//     free(c);
// }

int main() {
    // printf("Running malloc tests...\n\n");
    // test_malloc_basic();
    // printf("\n");
    // test_malloc_large();
    // printf("\n");
    // test_malloc_multiple();
    // printf("\nTests completed.\n");
    // char *root = (char *)malloc(26);
    // for (int i = 0; i < 26; i++) {
    //     root[i] = 'A' + i;
    //     write(1, &root[i], 1);
    // }

    // for (size_t i = 0; i < 100; ++i) {
    //    (void)malloc(i);
    // }

    // write(1, "\n", 1);
    // dump_alloced_memory();
    // free(root);


    char *tree = NULL;

    // Create nodes
    char node1[NODE_SIZE], node2[NODE_SIZE], node3[NODE_SIZE], node4[NODE_SIZE], node5[NODE_SIZE];
    char node6[NODE_SIZE], node7[NODE_SIZE], node8[NODE_SIZE], node9[NODE_SIZE], node10[NODE_SIZE];
    char node11[NODE_SIZE], node12[NODE_SIZE], node13[NODE_SIZE], node14[NODE_SIZE], node15[NODE_SIZE];

    // Initialize nodes with Red color
    init_node(node1, 10, RED);
    init_node(node2, 5, RED);
    init_node(node3, 15, RED);
    init_node(node4, 3, RED);
    init_node(node5, 7, RED);
    init_node(node6, 12, RED);
    init_node(node7, 18, RED);
    init_node(node8, 1, RED);
    init_node(node9, 4, RED);
    init_node(node10, 11, RED);
    init_node(node11, 10, RED);
    init_node(node12, 13, RED);
    init_node(node13, 14, RED);

    // Insert nodes into the tree (all nodes are red initially)
    tree = insert_node(tree, node1);  // Insert root
    // printf("%p\n", tree);
    // fix_insert(&tree, node1);
    insert_node(tree, node2);  // Insert left child of root
    // fix_insert(&tree, node2);
    insert_node(tree, node3);  // Insert right child of root
    // fix_insert(&tree, node3);
    insert_node(tree, node4);  // Insert left child of left child
    // fix_insert(&tree, node4);
    insert_node(tree, node5);  // Insert right child of left child
    // fix_insert(&tree, node5);
    insert_node(tree, node6);  // Insert left child of right child
    // fix_insert(&tree, node6);
    insert_node(tree, node7);  // Insert right child of right child
    // fix_insert(&tree, node7);
    insert_node(tree, node8);  // Insert left child of left child of left child
    // fix_insert(&tree, node8);
    insert_node(tree, node9);  // Insert right child of left child of left child
    // fix_insert(&tree, node9);
    insert_node(tree, node10); // Insert left child of left child of right child
    // fix_insert(&tree, node10);
    insert_node(tree, node11); // Insert duplicate value
    // fix_insert(&tree, node11); // Fix the tree after insertion
    insert_node(tree, node12); // Insert right child of left child of right child
    // fix_insert(&tree, node12);
    insert_node(tree, node13); // Insert left child of right child of right child
    // fix_insert(&tree, node13);

    // remove
    // delete_node(&tree, search_node(tree, 5));
    // delete_node(&tree, search_node(tree, 1));
    // delete_node(&tree, search_node(tree, 13));
    delete_node(&tree, search_node(tree, 15));
    // fix_delete(&tree, node1);

    // Generate the dot file for visualization
    generate_dot(tree, "tree.dot");

    // printf("Red-Black Tree generated in 'tree.dot'. Use Graphviz to visualize it.\n");


    
    return 0;
}
