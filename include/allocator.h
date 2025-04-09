/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarran <zarran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:09:09 by ymoutaou          #+#    #+#             */
/*   Updated: 2025/04/09 21:43:47 by zarran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOCATOR_H
# define ALLOCATOR_H


// Include necessary headers
#include <stddef.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stddef.h>
#include <stdio.h>

// DEFINE MACROS

// Alingment to 16
# define ALIGN_16(x) ((x + 15) & ~15)
// x	    x + 15	    Binary (x + 15)	    & ~15 Result	    Aligned Value
// 0	    15	        00001111	        00000000	        0
// 1	    16	        00010000	        00010000	        16
// 8	    23	        00010111	        00010000	        16
// 15	    30	        00011110	        00010000	        16
// 16	    31	        00011111	        00010000	        16
// 17	    32	        00100000	        00100000	        32
// 31	    46	        00101110	        00100000	        32

// Minimum size to hold Red-Black tree node
# define MINIMAL_SIZE ALIGN_16((sizeof(void *) * 3) + sizeof(size_t))
// Field	            Size
// Left pointer	        sizeof(void *)
// Right pointer	    sizeof(void *)
// Parent pointer	    sizeof(void *)
// Color	            sizeof(int)

# define TINY_MAX_SIZE 64
# define SMALL_MAX_SIZE 512

// [ size (8B) ][ prev ptr (8B) ][ user data (up to 64B) ]
# define TINY_CAPACITY (TINY_MAX_SIZE * TINY_MAX_SIZE + (sizeof(void *) + sizeof(size_t)) * TINY_MAX_SIZE)
// [ size (8B) ][ prev ptr (8B) ][ user data (up to 512B) ]
# define SMALL_CAPACITY (SMALL_MAX_SIZE * SMALL_MAX_SIZE + (sizeof(void *) + sizeof(size_t)) * SMALL_MAX_SIZE)
# define TOTAL_CAPACITY (TINY_CAPACITY + SMALL_CAPACITY)

// area setup
# define SIZE_OFFSET 0 // offset of size
# define PREV_OFFSET sizeof(size_t) // offset of previous pointer
# define DATA_OFFSET sizeof(void *) + sizeof(size_t) // offset of user data


// red-black tree node setup
enum { RED, BLACK }; // color of node
#define NODE_SIZE sizeof(void *) * 3 + sizeof(int) * 2 // size of node
#define LEFT_OFFSET 0 // offset of left child
#define RIGHT_OFFSET sizeof(void *) // offset of right child
#define PARENT_OFFSET sizeof(void *) * 2 // offset of parent
#define VALUE_OFFSET sizeof(void *) * 3 // value offset
#define COLOR_OFFSET sizeof(void *) * 3 + sizeof(int)// color offset

// Function prototypes
void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);

// src/access.c
void set_value(char *node, int value); // set value
void set_color(char *node, int color); // set color
void set_ptr(char *node, char *ptr, size_t offset); // set pointer
void set_parent(char *node, char *parent); // set parent
void set_left(char *node, char *left); // set left child
void set_right(char *node, char *right); // set right child
void *get_parent(char *node); // get parent
void *get_left(char *node); // get left child
void *get_right(char *node); // get right child
char *get_ptr(char *node, size_t offset); // get pointer
int get_value(char *node); // get value
int get_color(char *node); // get color
void init_node(char *node, int value, int color);
size_t get_size(void *block);
void set_size(void *block, size_t size);
void *get_prev(void *block);
void set_prev(void *block, void *prev);
void *get_data(void *block);
void set_data(void *block, void *data_src, size_t size);

// src/rbtree.c
void* insert_node(char *root, char *node);
void* insert_node_rec(char *root, char *node);
void left_rotate(char **tree_root, char *x);
void right_rotate(char **tree_root, char *x);
void fix_insert(char **root_ptr, char *node);
char* search_node(char *root, int value);
char* minimum(char *node);
void transplant(char **root, char *u, char *v);
void delete_node(char **root, char *z);
void fix_delete(char **root, char *x);

// src/utils.c

#endif //ALLOCATOR_H