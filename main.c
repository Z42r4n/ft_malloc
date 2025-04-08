// +-----------+-----------+-----------+-----------+-----------+-----------+-------+
// |  size     |  prev     |  left     |  right    |  parent   |  padding  | color |
// | (size_t)  | (void*)   | (block*)  | (block*)  | (block*)  |           | (int) |
// +-----------+-----------+-----------+-----------+-----------+-----------+-------+

#include <stdio.h>
enum { RED, BLACK }; // color of node
#define NODE_SIZE sizeof(void *) * 3 + sizeof(int) * 2 // size of node
#define LEFT_OFFSET 0 // offset of left child
#define RIGHT_OFFSET sizeof(void *) // offset of right child
#define PARENT_OFFSET sizeof(void *) * 2 // offset of parent
#define VALUE_OFFSET sizeof(void *) * 3 // value offset
#define COLOR_OFFSET sizeof(void *) * 3 + sizeof(int)// color offset

void set_value(char *node, int value)
{
    *(int *)(node + VALUE_OFFSET) = value; // set value
}
void set_color(char *node, int color)
{
    *(int *)(node + COLOR_OFFSET) = color; // set color
}
void set_ptr(char *node, char *ptr, size_t offset)
{
    *(char **)(node + offset) = ptr; // set pointer
}

void *get_parent(char *node)
{
    return *(char **)(node + PARENT_OFFSET); // get parent
}

void *get_left(char *node)
{
    return *(char **)(node + LEFT_OFFSET); // get left child
}

void *get_right(char *node)
{
    return *(char **)(node + RIGHT_OFFSET); // get right child
}

char *get_ptr(char *node, size_t offset)
{
    return *(char **)(node + offset); // get pointer
}

int get_value(char *node)
{
    return *(int *)(node + VALUE_OFFSET); // get value
}

int get_color(char *node)
{
    return *(int *)(node + COLOR_OFFSET); // get color
}

int main()
{
    // red black tree node without malloc
    char root[NODE_SIZE]; // root node

    // set left child of root to 5
    char left_child[NODE_SIZE]; // left child node
    char right_child[NODE_SIZE]; // right child node

    // init the root node
    set_value(root, 10); // set value of root to 10
    set_color(root, BLACK); // set color of root to black
    set_ptr(root, left_child, LEFT_OFFSET); // set left child of root to left_child
    set_ptr(root, right_child, RIGHT_OFFSET); // set right child of root to right_child
    set_ptr(root, NULL, PARENT_OFFSET); // set parent of left_child to NULL

    // init the left child node
    set_value(left_child, 5); // set value of left child to 5
    set_color(left_child, RED); // set color of left child to red
    set_ptr(left_child, NULL, LEFT_OFFSET); // set left child of left_child to NULL
    set_ptr(left_child, NULL, RIGHT_OFFSET); // set right child of left_child to NULL
    set_ptr(left_child, root, PARENT_OFFSET); // set parent of left_child to root

    // init the right child node
    set_value(right_child, 15); // set value of right child to 15
    set_color(right_child, RED); // set color of right child to red
    set_ptr(right_child, NULL, LEFT_OFFSET); // set left child of right_child to NULL
    set_ptr(right_child, NULL, RIGHT_OFFSET); // set right child of right_child to NULL
    set_ptr(right_child, root, PARENT_OFFSET); // set parent of right_child to root

    // print the values of the nodes root, value: int, color: int
    printf("root: %d, color: %d\n", *(int *)(root + VALUE_OFFSET), *(int *)(root + COLOR_OFFSET));
    printf("left child: %d, color: %d\n", *(int *)(left_child + VALUE_OFFSET), *(int *)(left_child + COLOR_OFFSET));
    printf("right child: %d, color: %d\n", *(int *)(right_child + VALUE_OFFSET), *(int *)(right_child + COLOR_OFFSET));

    return(0);
}