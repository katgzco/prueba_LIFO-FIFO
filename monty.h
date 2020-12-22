#ifndef MONTY
#define MONTY

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>

extern char *nodo_ini;

typedef unsigned int positive;

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO Holberton project
 */
typedef struct stack_s
{
        int n;
        struct stack_s *prev;
        struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO Holberton project
 */
typedef struct instruction_s
{
        char *opcode;
        void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

typedef struct check
{
	char *arg;
	char *opcode;
} check;

void file_manage(char *file_name);
void man_er(int size, const char *mesge, ...);
char *copy_string(char *dest);
void opc_f(int idx, bool exec, check *array, stack_t **s, positive ln, char *l);
void divide_file(FILE *check_file, check *array, int *count_line);
void push(stack_t **stack, unsigned int ln);
void pall(stack_t **stack, unsigned int ln);
int count_digits(int number);
char *_itoa(int number);
bool check_opcode(check *a, instruction_t *opc);
#endif