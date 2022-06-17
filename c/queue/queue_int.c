#ifndef STDIO
    #include <stdio.h>
#endif
#ifndef STDLIB
    #include <stdlib.h>
#endif
#ifndef STDBOOL
    #include <stdbool.h>
#endif
#ifndef STRING
    #include <string.h>
#endif

#define ARE_STRINGS_EQUAL(s1, s2) (strcmp(s1, s2) ? 0 : 1)
#define ARE_STRING_SLICES_EQUAL(s1, s2, n) (strncmp(s1, s2, n) ? 0 : 1)

typedef struct q_node {
    int info;
    struct q_node* next;
} q_node;

q_node* create_q_node() {
    q_node* n;
    while( !(n = (q_node *) malloc(sizeof(q_node))) ) {
        puts("Retrying to allocate memory for q_node");
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

bool enqueue(queue* q, int data) {
    q_node *newQNode = create_q_node();
    newQNode->info = data;
    if(!q->rear) {
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

int print(queue q) {
    q_node* traverser = q.front;
    printf("|-> ");
    while(traverser) {
        printf("%d -> ", traverser->info);
        traverser = traverser->next;
    }
    printf("nil\n");
    return true;
}

int peek(queue q) {
    if(!is_empty(q))
        return q.front->info;
    return 0;
}

int dequeue(queue* q) {
    int data = peek(*q);
    if(q->front) {
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
    if(toRelease) free(toRelease);
    return true;
}

int cli() {
    int inputs, operand;
    queue q = qCreate();
    puts("Creating a queue");
    char action[40], *operator, *afterOperator;
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
            operand = afterOperator ? atoi(afterOperator) : 1;
            while(operand-- && !is_empty(q))
                printf("%d\n", dequeue(&q));
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