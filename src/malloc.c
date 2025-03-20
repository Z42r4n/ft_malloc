/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymoutaou <ymoutaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:49:24 by ymoutaou          #+#    #+#             */
/*   Updated: 2025/03/05 15:20:46 by ymoutaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator.h"

// #define ALIGNMENT 8  // Ensure proper memory alignment
// #define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))

// void *malloc(size_t size) {
//     if (size == 0) {
//         return NULL;
//     }

//     size = ALIGN(size);  // Align size to the nearest multiple of 8
//     size_t total_size = size + sizeof(BlockHeader);  // Include space for metadata

//     BlockHeader *block = mmap(NULL, total_size, PROT_READ | PROT_WRITE,
//                               MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    
//     if (block == MAP_FAILED) {
//         return NULL;
//     }

//     block->size = size;
//     block->free = 0;  // Mark as allocated

//     return (void *)(block + 1);  // Return pointer after the metadata block
// }

char memory[CAPACITY] = {0};
size_t heap_size = 0;

void *malloc(size_t size) {
    if (size == 0) {
        return NULL;
        // chane it later
    }
    if (heap_size + size > CAPACITY) {
        write(2, "malloc: failed to allocate memory 1\n", 37);
        return NULL;
    }
    void *ptr = memory + heap_size;
    heap_size += size;
    t_block block = {
        .start = ptr,
        .size = size
    };
    if (heap_alloced_size >= HEAP_ALLOCED_SIZE) {
        write(2, "malloc: failed to allocate memory 2\n", 37);
        return NULL;
    }
    heap_alloced_blocks[++heap_alloced_size] = block;
    return ptr;
}