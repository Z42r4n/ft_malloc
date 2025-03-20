/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymoutaou <ymoutaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:20:20 by ymoutaou          #+#    #+#             */
/*   Updated: 2025/03/05 14:57:21 by ymoutaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator.h"

void dump_alloced_memory() {
    printf("Allocated memory blocks (%zu):\n", heap_alloced_size);
    for (size_t i = 0; i < heap_alloced_size; ++i) {
        t_block block = heap_alloced_blocks[i];
        printf("Start: %p, Size: %zu\n", block.start, block.size);
    }
}