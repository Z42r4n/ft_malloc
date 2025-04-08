/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarran <zarran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:21:04 by zarran            #+#    #+#             */
/*   Updated: 2025/04/08 22:16:41 by zarran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <allocator.h>

void set_value(char *node, int value)
{
    *(int *)(node + VALUE_OFFSET) = value; // set value
}

// set value of node
void set_color(char *node, int color)
{
    *(int *)(node + COLOR_OFFSET) = color; // set color
}

// set color of node
void set_ptr(char *node, char *ptr, size_t offset)
{
    *(char **)(node + offset) = ptr; // set pointer
}

// set parent of node
void set_parent(char *node, char *parent)
{
    *(char **)(node + PARENT_OFFSET) = parent; // set parent
}

// set left child of node
void set_left(char *node, char *left)
{
    *(char **)(node + LEFT_OFFSET) = left; // set left child
}

// set right child of node
void set_right(char *node, char *right)
{
    *(char **)(node + RIGHT_OFFSET) = right; // set right child
}

// set pointer of node
void *get_parent(char *node)
{
    return *(char **)(node + PARENT_OFFSET); // get parent
}

// get parent of node
void *get_left(char *node)
{
    return *(char **)(node + LEFT_OFFSET); // get left child
}

// get left child of node
void *get_right(char *node)
{
    return *(char **)(node + RIGHT_OFFSET); // get right child
}

// get right child of node
char *get_ptr(char *node, size_t offset)
{
    return *(char **)(node + offset); // get pointer
}

// get pointer of node
int get_value(char *node)
{
    return *(int *)(node + VALUE_OFFSET); // get value
}

// get value of node
int get_color(char *node)
{
    return *(int *)(node + COLOR_OFFSET); // get color
}

// init node
void init_node(char *node, int value, int color)
{
    set_left(node, NULL);
    set_right(node, NULL);
    set_parent(node, NULL);
    set_value(node, value);
    set_color(node, color);
}

// insert node into tree recursively
void* insert_node(char *root, char *node)
{
    if (root == NULL)
    {
        return node;  // return the newly inserted node
    }

    // Recursive case: traverse the tree
    if (get_value(node) < get_value(root))
    {
        // Insert the node into the left subtree
        char *left = insert_node(get_left(root), node);
        set_left(root, left);          // Attach the new node to the left
        set_parent(left, root);        // Set the parent of the new node
    }
    else
    {
        // Insert the node into the right subtree
        char *right = insert_node(get_right(root), node);
        set_right(root, right);        // Attach the new node to the right
        set_parent(right, root);       // Set the parent of the new node
    }
    
    return root;  // Return the root node after insertion
}

// left rotate
void left_rotate(char **tree_root, char *x)
{
    char *y = get_right(x);
    set_right(x, get_left(y));
    if (get_left(y) != NULL)
        set_parent(get_left(y), x);
    set_parent(y, get_parent(x));

    if (get_parent(x) == NULL)
        *tree_root = y;
    else if (x == get_left(get_parent(x)))
        set_left(get_parent(x), y);
    else
        set_right(get_parent(x), y);

    set_left(y, x);
    set_parent(x, y);
}

// right rotate
void right_rotate(char **tree_root, char *x)
{
    char *y = get_left(x);
    set_left(x, get_right(y));
    if (get_right(y) != NULL)
        set_parent(get_right(y), x);
    set_parent(y, get_parent(x));

    if (get_parent(x) == NULL)
        *tree_root = y;
    else if (x == get_right(get_parent(x)))
        set_right(get_parent(x), y);
    else
        set_left(get_parent(x), y);

    set_right(y, x);
    set_parent(x, y);
}

// fix tree after insertion
void fix_insert(char **root_ptr, char *node)
{
    while (node != *root_ptr && get_color(get_parent(node)) == RED)
    {
        printf("Fixing node: %d\n", get_value(node));
        char *parent = get_parent(node);
        char *grandparent = get_parent(parent);

        if (parent == get_left(grandparent))
        {
            char *uncle = get_right(grandparent);

            // Case 1: Uncle is red -> recolor
            if (uncle != NULL && get_color(uncle) == RED)
            {
                set_color(parent, BLACK);
                set_color(uncle, BLACK);
                set_color(grandparent, RED);
                node = grandparent;
            }
            else
            {
                // Case 2: node is right child -> rotate left
                if (node == get_right(parent))
                {
                    node = parent;
                    left_rotate(root_ptr, node);
                    parent = get_parent(node);
                    grandparent = get_parent(parent);
                }

                // Case 3: node is left child -> rotate right
                set_color(parent, BLACK);
                set_color(grandparent, RED);
                right_rotate(root_ptr, grandparent);
            }
        }
        else
        {
            char *uncle = get_left(grandparent);

            // Case 1: Uncle is red -> recolor
            if (uncle != NULL && get_color(uncle) == RED)
            {
                set_color(parent, BLACK);
                set_color(uncle, BLACK);
                set_color(grandparent, RED);
                node = grandparent;
            }
            else
            {
                // Case 2: node is left child -> rotate right
                if (node == get_left(parent))
                {
                    node = parent;
                    right_rotate(root_ptr, node);
                    parent = get_parent(node);
                    grandparent = get_parent(parent);
                }

                // Case 3: node is right child -> rotate left
                set_color(parent, BLACK);
                set_color(grandparent, RED);
                left_rotate(root_ptr, grandparent);
            }
        }
    }

    // Root is always black
    set_color(*root_ptr, BLACK);
}
