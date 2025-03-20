/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymoutaou <ymoutaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:09:09 by ymoutaou          #+#    #+#             */
/*   Updated: 2025/03/05 15:22:08 by ymoutaou         ###   ########.fr       */
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

// Metadata structure to track memory blocks
typedef struct heap_block {
    void *start;
    size_t size;
} t_block;

#define CAPACITY 640000
#define HEAP_ALLOCED_SIZE 1024
#define HEAP_FREE_SIZE 1024

extern t_block heap_alloced_blocks[HEAP_ALLOCED_SIZE];
extern size_t heap_alloced_size;

t_block heap_free_blocks[HEAP_FREE_SIZE];
size_t heap_free_size;


extern char memory[CAPACITY];
extern size_t heap_size;

// Function prototypes
void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);

// src/utils.c
void dump_alloced_memory();

#endif //ALLOCATOR_H