/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarran <zarran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:21:04 by zarran            #+#    #+#             */
/*   Updated: 2025/04/09 15:37:07 by zarran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <allocator.h>


// insert node into tree
void* insert_node(char *root, char *node)
{
    // Insert the node into the tree
    root = insert_node_rec(root, node);

    // Fix the tree properties after insertion
    fix_insert(&root, node);

    return root;  // Return the updated root of the tree
}

// insert node into tree recursively
void* insert_node_rec(char *root, char *node)
{
    if (root == NULL)
    {
        return node;  // return the newly inserted node
    }

    // Recursive case: traverse the tree
    if (get_value(node) < get_value(root))
    {
        // Insert the node into the left subtree
        char *left = insert_node_rec(get_left(root), node);
        set_left(root, left);          // Attach the new node to the left
        set_parent(left, root);        // Set the parent of the new node
    }
    else
    {
        // Insert the node into the right subtree
        char *right = insert_node_rec(get_right(root), node);
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

// search for node
char* search_node(char *root, int value)
{
    if (root == NULL || get_value(root) == value)
        return root;

    if (value < get_value(root))
        return search_node(get_left(root), value);
    else
        return search_node(get_right(root), value);
}

// Case	    Description	                                Action
// 1	    Sibling is red	                            Rotate & recolor
// 2	    Sibling is black, both children black	    Recolor sibling and move up
// 3	    Sibling is black, one red child (inner)	    Rotate sibling to prepare Case 4
// 4	    Sibling is black, outer red child	        Rotate parent & recolor


// Replaces one subtree (u) with another (v)
void transplant(char **root, char *u, char *v)
{
    if (get_parent(u) == NULL)
        *root = v; // If u is the root, make v the new root
    else if (u == get_left(get_parent(u)))
        set_left(get_parent(u), v); // If u is a left child
    else
        set_right(get_parent(u), v); // If u is a right child

    if (v != NULL)
        set_parent(v, get_parent(u)); // Set v's parent to u's parent
}

// Finds the leftmost (smallest) node in a subtree
char* minimum(char *node)
{
    while (get_left(node) != NULL)
        node = get_left(node);
    return node;
}

// delete node from tree
void delete_node(char **root, char *z)
{
    if (z == NULL)
        return;
    char *y = z; // y is the node that will be removed or moved
    int y_original_color = get_color(y); // Save original color
    char *x; // x is the node that replaces y and may need fixing
    if (get_left(z) == NULL)
    {
        // Case 1: z has no left child — replace with right child
        x = get_right(z);
        transplant(root, z, get_right(z));
    }
    else if (get_right(z) == NULL)
    {
        // Case 2: z has no right child — replace with left child
        x = get_left(z);
        transplant(root, z, get_left(z));
    }
    else
    {
        // Case 3: z has two children — find successor
        y = minimum(get_right(z)); // y is successor
        y_original_color = get_color(y);
        x = get_right(y);

        if (get_parent(y) == z)
        {
            // If y is direct child of z
            if (x != NULL)
                set_parent(x, y);
        }
        else
        {
            // Move y's right child up, then y replaces z
            transplant(root, y, get_right(y));
            set_right(y, get_right(z));
            if (get_right(y) != NULL)
                set_parent(get_right(y), y);
        }

        transplant(root, z, y);
        set_left(y, get_left(z));
        if (get_left(y) != NULL)
            set_parent(get_left(y), y);
        set_color(y, get_color(z)); // Keep z's original color
    }

    // If we removed a black node, we may have broken the RB properties
    if (y_original_color == BLACK)
        fix_delete(root, x);
}

// Fix the tree after deletion
void fix_delete(char **root, char *x)
{
    if (x == NULL)
        return;
    while (x != *root && (x == NULL || get_color(x) == BLACK))
    {
        if (x == get_left(get_parent(x)))
        {
            char *w = get_right(get_parent(x)); // x's sibling

            // Case 1: Sibling is red
            if (get_color(w) == RED)
            {
                set_color(w, BLACK);
                set_color(get_parent(x), RED);
                left_rotate(root, get_parent(x));
                w = get_right(get_parent(x));
            }

            // Case 2: Sibling and its children are black
            if ((get_left(w) == NULL || get_color(get_left(w)) == BLACK) &&
                (get_right(w) == NULL || get_color(get_right(w)) == BLACK))
            {
                set_color(w, RED);
                x = get_parent(x);
            }
            else
            {
                // Case 3: Sibling is black, left child is red, right is black
                if (get_right(w) == NULL || get_color(get_right(w)) == BLACK)
                {
                    if (get_left(w) != NULL)
                        set_color(get_left(w), BLACK);
                    set_color(w, RED);
                    right_rotate(root, w);
                    w = get_right(get_parent(x));
                }

                // Case 4: Sibling is black and right child is red
                set_color(w, get_color(get_parent(x)));
                set_color(get_parent(x), BLACK);
                if (get_right(w) != NULL)
                    set_color(get_right(w), BLACK);
                left_rotate(root, get_parent(x));
                x = *root;
            }
        }
        else
        {
            // Symmetric cases for right child
            char *w = get_left(get_parent(x));

            if (get_color(w) == RED)
            {
                set_color(w, BLACK);
                set_color(get_parent(x), RED);
                right_rotate(root, get_parent(x));
                w = get_left(get_parent(x));
            }

            if ((get_right(w) == NULL || get_color(get_right(w)) == BLACK) &&
                (get_left(w) == NULL || get_color(get_left(w)) == BLACK))
            {
                set_color(w, RED);
                x = get_parent(x);
            }
            else
            {
                if (get_left(w) == NULL || get_color(get_left(w)) == BLACK)
                {
                    if (get_right(w) != NULL)
                        set_color(get_right(w), BLACK);
                    set_color(w, RED);
                    left_rotate(root, w);
                    w = get_left(get_parent(x));
                }

                set_color(w, get_color(get_parent(x)));
                set_color(get_parent(x), BLACK);
                if (get_left(w) != NULL)
                    set_color(get_left(w), BLACK);
                right_rotate(root, get_parent(x));
                x = *root;
            }
        }
    }

    if (x != NULL)
        set_color(x, BLACK); // Ensure x is black at the end
}
