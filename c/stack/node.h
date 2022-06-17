#ifndef STDBOOL
    #include <stdbool.h>
#endif

#ifndef STDLIB
    #include <stdlib.h>
#endif

typedef struct s_node {
    int info;
    struct s_node* next;
} s_node;
