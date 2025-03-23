/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymoutaou <ymoutaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:33:38 by ymoutaou          #+#    #+#             */
/*   Updated: 2025/03/05 15:20:55 by ymoutaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <stdio.h>
#include "allocator.h"

// void free(void *ptr) {
//     if (!ptr) return;  // Ignore NULL pointers

//     BlockHeader *block = (BlockHeader *)ptr - 1;  // Retrieve metadata

//     // Ensure the block is valid
//     if (block->free) {
//         fprintf(stderr, "free(): double free detected!\n");
//         return;
//     }

//     block->free = 1;  // Mark as free
//     munmap(block, block->size + sizeof(BlockHeader));  // Unmap the memory
// }

// t_block heap_alloced_blocks[HEAP_ALLOCED_SIZE] = {0};
// size_t heap_alloced_size = 0;

void free(void *ptr) {
    // Do nothing
    (void)ptr;
   write(2, "free is not implemented\n", 25);
}