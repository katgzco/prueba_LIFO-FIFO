#include "file_extern.h"
#include "monty.h"

void push(stack_t **stack, unsigned int ln)
{
	stack_t *newNode;

	if (nodo_ini == NULL)
		return;

	newNode = malloc(sizeof(stack_t));
	if (!newNode)
		return;
	newNode->n = atoi(nodo_ini);
	newNode->next = NULL;
	newNode->prev = NULL;
	newNode->next = *stack;
	if (*stack)
		(*stack)->prev = newNode;
	*stack = newNode;
}

void pall(stack_t **stack, unsigned int ln)
{
	stack_t *current;

	if (!*stack)
		return;

	current = *stack;

	while (current->next)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
    printf("%d\n", current->n);
}