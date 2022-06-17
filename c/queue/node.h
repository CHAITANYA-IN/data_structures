#ifndef STDBOOL
    #include <stdbool.h>
#endif

#ifndef STDLIB
    #include <stdlib.h>
#endif

typedef struct q_node {
    int info;
    struct q_node* next;
} q_node;

bool create_q_node(q_node* n) {
    if( !(n = (q_node *) malloc(sizeof(q_node))) ) {
        return false;
    }
    n->info = 0;
    n->next = NULL;
    return true;
}