#ifndef B_T_NODE
    #include "./node.h"
    #define B_T_NODE
#endif

#define sel_type b_t_node* // change int to your desirable type.
#define cli__sel_type_convertor(string) atoi(string)
#define cli__sel_type_default_value 1

#ifndef STDIO
    #include <stdio.h>
    #define STDIO 1
#endif
#ifndef STDLIB
    #include <stdlib.h>
    #define STDLIB 1
#endif
#ifndef STDBOOL
    #include <stdbool.h>
    #define STDBOOL 1
#endif
#ifndef STRING
    #include <string.h>
    #define STRING 1
#endif
#ifndef STRINGS
    #include <strings.h>
    #define STRINGS 1
#endif

#ifndef TYPE
    #include "/Users/chaitanyashinge/Desktop/data_structures/c/type.c"
    #define TYPE 1
#endif

#define ARE_STRINGS_EQUAL(s1, s2) (strcmp(s1, s2) ? 0 : 1)
#define ARE_STRING_SLICES_EQUAL(s1, s2, n) (strncmp(s1, s2, n) ? 0 : 1)

typedef struct q_node {
    sel_type info;
    struct q_node* next;
} q_node;

q_node* create_q_node() {
    q_node* n;
    if ( !(n = (q_node *) malloc(sizeof(q_node))) ) {
        puts("Retrying to allocate memory for q_node");
        return NULL;
    }
    n->info = 0;
    n->next = NULL;
    return n;
}

typedef struct queue {
    q_node* front;
    q_node* rear;
} queue;

queue qCreate() {
    queue* q;
    while( !(q = (queue *) malloc(sizeof(queue))) ) {
        puts("Retrying to allocate memory for queue");
    }
    q->front = NULL;
    q->rear = NULL;
    return *q;
}

bool enqueue(queue* q, sel_type data) {
    q_node *newQNode = create_q_node();
    newQNode->info = data;
    if (!q->rear) {
        q->rear = q->front = newQNode;
    } else {
        q->rear->next = newQNode;
        q->rear = q->rear->next;
    }
    return true;
}

bool is_empty(queue q) {
    return (bool) !(q.front);
}

bool print(queue q) {
    q_node* traverser = q.front;
    printf("|-> ");
    while(traverser) {
        PRINT(traverser->info, " -> ");
        traverser = traverser->next;
    }
    printf("nil\n");
    return true;
}

sel_type peek(queue q) {
    if (!is_empty(q))
        return q.front->info;
    return 0;
}

sel_type dequeue(queue* q) {
    sel_type data = peek(*q);
    if (q->front) {
        q_node* served = q->front;
        q->front = q->front->next;
        free(served);
    }
    return data;
}

bool delete(queue* q) {
    q_node* toRelease = q->front;
    while(toRelease != q->rear) {
        q->front = q->front->next;
        free(toRelease);
        toRelease = q->front;
    }
    q->rear = q->front = NULL;
    if (toRelease) free(toRelease);
    return true;
}

int cli() {
    int inputs;
    queue q = qCreate();
    puts("Creating a queue");
    char action[40], *operator, *afterOperator;
    sel_type operand;
    while(printf("> ")) {
        // Clean
        fflush(stdin);
        bzero(action, 40);
        // Scan
        inputs = scanf("%[^\n]%*c", action);
        // Scan handlers
        if ( !inputs ) continue;
        if ( inputs == -1 ) break;
        // printf("Scanned:%s|\n", action);
        // Parse
        operator = strtok(action, " ");
        // Action
        if (ARE_STRINGS_EQUAL(operator, "enqueue")) {
            afterOperator = strtok(NULL, " ");
            while(afterOperator) {
                operand = atoi(afterOperator);
                enqueue(&q, operand) ? printf("Enqueued %d\n", operand): printf("%d not Enqueued, try again!\n", operand);
                afterOperator = strtok(NULL, " ");
            }
        } else if (ARE_STRINGS_EQUAL(operator, "dequeue")) {
            afterOperator = strtok(NULL, " ");
            operand = afterOperator ? cli__sel_type_convertor(afterOperator) : cli__sel_type_default_value;
            while(operand-- && !is_empty(q))
                PRINT(dequeue(&q)->info);
            operand = 0;
        } else if (ARE_STRINGS_EQUAL(operator, "peek")) {
            printf("%d\n", peek(q));
        } else if (ARE_STRINGS_EQUAL(operator, "isEmpty")) {
            printf(is_empty(q) ? "true\n" : "false\n");
        // } else if (ARE_STRINGS_EQUAL(operator, "create")) {
        // } else if (ARE_STRINGS_EQUAL(operator, "delete")) {
        } else if (ARE_STRINGS_EQUAL(operator, "print")) {
            print(q);
        } else if (
            ARE_STRING_SLICES_EQUAL(operator, "finish", 6) ||
            ARE_STRING_SLICES_EQUAL(operator, "exit", 4) ||
            ARE_STRING_SLICES_EQUAL(operator, "quit", 4) ||
            *operator == 'q' || *operator == '\0' ) {
            break;
        } else if (ARE_STRINGS_EQUAL(operator, "\0")) {
            continue;
        } else {
            printf("Unknown operator\n");
        }
    }
    puts("Final Queue");
    if (!print(q)) {
        return 4;
    }
    puts("Deleting the Queue");
    delete(&q);
    return 0;
}

int main() {
    return cli();
}