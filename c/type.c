#define PRINT_SCALAR(data, end) _Generic((data), _Bool: PRINT_FORMAT("%d", data, end), \
    char: PRINT_FORMAT("%c", data, end), \
    signed char: PRINT_FORMAT("%c", data, end), \
    unsigned char: PRINT_FORMAT("%c", data, end), \
    short int: PRINT_FORMAT("%hi", data, end), \
    unsigned short int: PRINT_FORMAT("%hu", data, end), \
    int: PRINT_FORMAT("%i", data, end), \
    unsigned int: PRINT_FORMAT("%u", data, end), \
    long int: PRINT_FORMAT("%li", data, end), \
    unsigned long int: PRINT_FORMAT("%lu", data, end), \
    long long int: PRINT_FORMAT("%lli", data, end), \
    unsigned long long int: PRINT_FORMAT("%llu", data, end), \
    float: PRINT_FORMAT("%c", data, end), \
    double: PRINT_FORMAT("%lf", data, end), \
    long double: PRINT_FORMAT("%Lf", data, end), \
    default: PRINT_FORMAT("%s", "Unknown type", ""), \
    void *: PRINT_FORMAT("%s", "Unknown data pointed", "") \
)

#define PRINT_FORMAT(format_specifier, data, end) printf(format_specifier end, data)

void print_array(int* array, int size, char* separator, char* end) {
    int i = 0;
    for(int i = 0; i < size; i++) {
        printf("%d%s", array[i], separator);
    }
    printf("%s", end);
}

void print_string(int* string, char* separator, char* end) {
    int i = 0;
    for(; string[i]; )
        printf("%c%s", string[i++], separator);
    printf("%s", end);
}

#define PRINT_2(data, end) PRINT_SCALAR(data, end)
#define PRINT_3(data, separator, end) print_string(data, separator, end)
#define PRINT_4(data, size, separator, end) print_array(data, size, separator, end)

#define PRINT_X(X,A,B,C,D,FUNC, ...)  FUNC

#define PRINT(...) PRINT_X(,##__VA_ARGS__,\
                PRINT_4(__VA_ARGS__),\
                PRINT_3(__VA_ARGS__),\
                PRINT_2(__VA_ARGS__),\
)