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

// Function prototypes
void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);

// src/utils.c

#endif //ALLOCATOR_H