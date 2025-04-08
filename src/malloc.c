/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarran <zarran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:49:24 by ymoutaou          #+#    #+#             */
/*   Updated: 2025/04/08 19:12:43 by zarran           ###   ########.fr       */
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


void *malloc(size_t size) {
    // size = ALIGN_16(size);

    // if (size < MINIMAL_SIZE)
    //     size = MINIMAL_SIZE;

    // void *mem_pool_ptr = get_or_allocate_mem_pool();
    // if (!mem_pool_ptr)
    //     return NULL;
}