#define sel_type int // change sel_type to your desirable type.
#define cli__sel_type_convertor(string) atoi(string)
#define cli__sel_type_default_value 1

#ifndef STDBOOL
    #include <stdbool.h>
    #define STDBOOL 1
#endif
#ifndef STDLIB
    #include <stdlib.h>
    #define STDLIB 1
#endif
#ifndef STRING
    #include <string.h>
    #define STRING 1
#endif
#ifndef STRINGS
    #include <strings.h>
    #define STRINGS 1
#endif
#ifndef STDIO
    #include <stdio.h>
    #define STDIO 1
#endif

#ifndef TYPE
    #include "/Users/chaitanyashinge/Desktop/data_structures/c/type.c"
    #define TYPE 1
#endif

#define ARE_STRINGS_EQUAL(s1, s2) (strcmp(s1, s2) ? 0 : 1)
#define ARE_STRING_SLICES_EQUAL(s1, s2, n) (strncmp(s1, s2, n) ? 0 : 1)

typedef struct s_node {
    sel_type info;
    struct s_node* next;
} s_node;

s_node* create_s_node() {
    s_node* n;
    while( !(n = (s_node *) malloc(sizeof(s_node))) ) {
        puts("Retrying to allocate memory for s_node");
    }
    n->info = 0;
    n->next = NULL;
    return n;
}

typedef struct stack {
    s_node* base;
    s_node* top;
} stack;

stack sCreate() {
    stack* s;
    while( !(s = (stack *) malloc(sizeof(stack))) ) {
        puts("Retrying to allocate memory for stack");
    }
    s->base = NULL;
    s->top = NULL;
    return *s;
}

bool push(stack* s, sel_type data) {
    s_node *newQNode = create_s_node();
    newQNode->info = data;
    if(!s->top) {
        s->top = s->base = newQNode;
    } else {
        newQNode->next = s->top;
        s->top = newQNode;
    }
    return true;
}

bool is_empty(stack s) {
    return (bool) !(s.base);
}

bool print(stack s) {
    s_node* traverser = s.top;
    puts("    top");
    printf("|-> ");
    while(traverser) {
        printf("%d -> ", traverser->info);
        traverser = traverser->next;
    }
    printf("nil\n");
    return true;
}

sel_type peek(stack s) {
    if(!is_empty(s))
        return s.top->info;
    return 0;
}

sel_type pop(stack* s) {
    sel_type data = peek(*s);
    if(s->top) {
        s_node* served = s->top;
        s->top = s->top->next;
        free(served);
    }
    return data;
}

bool delete(stack* s) {
    s_node* toRelease = s->top;
    while(toRelease != s->base) {
        s->top = s->top->next;
        free(toRelease);
        toRelease = s->top;
    }
    s->top = s->base = NULL;
    if(toRelease) free(toRelease);
    return true;
}

int cli() {
    int inputs;
    sel_type operand;
    stack s = sCreate();
    puts("Creating a stack");
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
        if(ARE_STRINGS_EQUAL(operator, "push")) {
            afterOperator = strtok(NULL, " ");
            while(afterOperator) {
                operand = atoi(afterOperator);
                push(&s, operand) ? printf("Pushed %d\n", operand): printf("%d not Pushed, try again!\n", operand);
                afterOperator = strtok(NULL, " ");
            }
        } else if(ARE_STRINGS_EQUAL(operator, "pop")) {
            afterOperator = strtok(NULL, " ");
            operand = afterOperator ? cli__sel_type_convertor(afterOperator) : cli__sel_type_default_value;
            while(operand-- && !is_empty(s))
                printf("%d\n", pop(&s));
            operand = 0;
        } else if(ARE_STRINGS_EQUAL(operator, "peek")) {
            printf("%d\n", peek(s));
        } else if(ARE_STRINGS_EQUAL(operator, "isEmpty")) {
            printf(is_empty(s) ? "true\n" : "false\n");
        // } else if(ARE_STRINGS_EQUAL(operator, "create")) {
        // } else if(ARE_STRINGS_EQUAL(operator, "delete")) {
        } else if(ARE_STRINGS_EQUAL(operator, "print")) {
            print(s);
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
    puts("Final stack");
    if(!print(s)) {
        return 4;
    }
    puts("Deleting the stack");
    delete(&s);
    return 0;
}

int main() {
    return cli();
}