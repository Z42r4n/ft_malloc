/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarran <zarran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:44:19 by zarran            #+#    #+#             */
/*   Updated: 2025/04/09 21:41:48 by zarran           ###   ########.fr       */
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

// get size of block
size_t get_size(void *block) {
	return *(size_t *)((char *)block + SIZE_OFFSET);
}

// get size of block
void set_size(void *block, size_t size) {
	*(size_t *)((char *)block + SIZE_OFFSET) = size;
}

// get user data pointer
void *get_prev(void *block) {
	return *(void **)((char *)block + PREV_OFFSET);
}

// get user data pointer
void set_prev(void *block, void *prev) {
	*(void **)((char *)block + PREV_OFFSET) = prev;
}

// get user data pointer
void *get_data(void *block) {
	return (void *)((char *)block + DATA_OFFSET);
}

// Rarely needed but useful for sanity/debug
void set_data(void *block, void *data_src, size_t size) {
    // change this to ft_memcpy
	memcpy((char *)block + DATA_OFFSET, data_src, size);
}

