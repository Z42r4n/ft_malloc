/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymoutaou <ymoutaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:51:07 by ymoutaou          #+#    #+#             */
/*   Updated: 2025/03/05 15:03:08 by ymoutaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/allocator.h"

// void test_malloc_basic() {
//     printf("Test 1: Basic malloc allocation\n");
//     int *ptr = (int *)malloc(sizeof(int));
//     if (!ptr) {
//         printf("❌ malloc failed to allocate memory\n");
//         return;
//     }
//     *ptr = 42;
//     printf("✅ malloc allocated memory and stored value: %d\n", *ptr);
//     free(ptr);
// }

// void test_malloc_large() {
//     printf("Test 2: Large malloc allocation\n");
//     size_t size = 1024 * 1024 * 10; // 10MB
//     char *buffer = (char *)malloc(size);
//     if (!buffer) {
//         printf("❌ malloc failed to allocate large memory block\n");
//         return;
//     }
//     memset(buffer, 'A', size);
//     printf("✅ malloc successfully allocated and wrote to large block\n");
//     free(buffer);
// }

// void test_malloc_multiple() {
//     printf("Test 3: Multiple malloc allocations\n");
//     int *a = (int *)malloc(sizeof(int));
//     double *b = (double *)malloc(sizeof(double));
//     char *c = (char *)malloc(50 * sizeof(char));

//     if (!a || !b || !c) {
//         printf("❌ malloc failed to allocate multiple blocks\n");
//         return;
//     }

//     *a = 100;
//     *b = 3.14;
//     strcpy(c, "Hello, malloc!");

//     printf("✅ Allocated multiple blocks: %d, %.2f, %s\n", *a, *b, c);

//     free(a);
//     free(b);
//     free(c);
// }

int main() {
    // printf("Running malloc tests...\n\n");
    // test_malloc_basic();
    // printf("\n");
    // test_malloc_large();
    // printf("\n");
    // test_malloc_multiple();
    // printf("\nTests completed.\n");
    // char *root = (char *)malloc(26);
    // for (int i = 0; i < 26; i++) {
    //     root[i] = 'A' + i;
    //     write(1, &root[i], 1);
    // }

    for (size_t i = 0; i < 100; ++i) {
       (void)malloc(i);
    }

    write(1, "\n", 1);
    dump_alloced_memory();
    // free(root);
    return 0;
}
