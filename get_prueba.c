#include "monty.h"

/* funciones*/
// Funcion que abra el archivo y lo lea
// funcion para hacer el strok
// funcion para checkear la existencia del opcode
// funcion para el atoi
// funcion para manejar errores, just text(no arguments)  open(file) - unknow instru (#line, opcode) -

char *nodo_ini;
int main(int argc, char *argv[])
{
/*check existing file*/
	if (argc !=  2)
	{
		man_er(0, "USAGE: monty file");
		exit(EXIT_FAILURE);
	}

/*open file*/
	file_manage(argv[1]);

	return (0);
}

void divide_file(FILE *check_file, check *array, int *count_line)
{
	char *nodo_ini = NULL;
	char *line = NULL, *token = NULL;
	size_t size = 0;
	positive control = 0, temp = 0, ln = 0, idx = 0;
	ssize_t check_get = 0;
	const char *delim = " \n";
	stack_t *head = NULL;

	while ((check_get = getline(&line, &size, check_file)) != -1)
	{
		control = 0, ln++;
		array[idx].opcode = NULL;
		array[idx].arg = NULL;
		token = strtok(line, delim);
		while (token)
		{
			control++;
			if (control >= 2)
				break;
			array[idx].opcode = copy_string(token);
			token = strtok(NULL, delim);
			array[idx].arg = copy_string(token);
			array[idx + 1].opcode = NULL;
			array[idx + 1].arg = NULL;
		}
		if (array[idx].opcode != NULL)
		{
			opc_f(idx, false, array, &head, ln, line);
			idx++;
		}
	}
	array[idx].opcode = NULL;
	array[idx].arg = NULL;
	opc_f(0, true, array, &head, ln, "");
	free(line);
	fclose(check_file);
/*	opc_f(NULL, ln, true, array, &head, ln);
	array[i] = NULL;
	*count_line = i;
	free(line);*/
}

void file_manage(char *file_name)
{
	//pasarla al header extern
	FILE *check_file = NULL;
	check array[BUFSIZ];
	int count_line = 0;

	check_file = fopen(file_name, "r");
	/*check succes or not of the open file*/
	if (check_file == NULL)
	{
		man_er(1, "Can't open file", file_name);
		exit(EXIT_FAILURE);
	}
	/*read line per line of the  file*/
	divide_file(check_file, array, &count_line);
/*	while (array[i].opcode != NULL)
	{
		printf("fileman: %s\n", array[i].opcode);
		i++;
	}*/
}

/**
 * free_dlistint - frees a list
 * @head: head of the list
 * Return: void
*/
void free_dlistint(stack_t *head)
{
	if (!head)
		return;

	while (head->next)
	{
		head = head->next;
		free(head->prev);
	}
	free(head);
	head = NULL;
}

/**
 * free_arr - frees a double pointer
 * @array: array to be freed
 * Return: void
*/
void free_arr(check *array)
{
	int i = 0;

	while (array[i].opcode)
	{
		free(array[i].opcode);
		if (array[i].arg)
			free(array[i].arg);
		i++;
	}
}

bool check_opcode(check *element, instruction_t *opc)
{
	int i = 0;
	while (opc[i].opcode != NULL)
	{
		if (strcmp(opc[i].opcode, element->opcode) == 0)
		{
			if (strcmp(element->opcode, "push") == 0)
			{
				if (element->arg == NULL)
					return (false);
				if (atoi(element->arg) == 0 && strcmp(element->arg, "0") != 0)
					return (false);
			}
			return (true);
		}
		i++;
	}
	return (false);
}

void opc_f(int idx, bool exec, check *array, stack_t **s, positive ln, char *l)
{
	int i = 0, j = 0;
	char *msg = NULL;
	instruction_t opc[] = {
		{"push", push},
		{"pall", pall},
		/*{"pint", pint},
		{"swap", swap},
		{"add"}, add},*/
		{NULL, NULL}};

	if (exec == false)
	{
		if (check_opcode(&array[idx], opc) == false)
		{
			msg = _itoa(ln);
			man_er(3, "L", msg, ": unknown instruction ", array[idx].opcode);
			free(msg);
			free(l);
			free_arr(array);
			free_dlistint(*s);
			/*
			push
			*/
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		while (array[i].opcode)
		{
			j = 0;
			while (opc[j].opcode)
			{
				if ((strcmp(opc[j].opcode, array[i].opcode)) == 0)
				{
					nodo_ini = array[i].arg;
					opc[j].f(s, ln);
					break;
				}
				j++;
			}
			i++;
		}
		free_arr(array);
		free_dlistint(*s);
	}
}

void man_er(int size, const char *mesge, ...)
{
	va_list args;
	va_start(args, mesge);
	char *str;
	int i = 0;

	fprintf(stderr, "%s", mesge );
	while (i < size)
	{
		str = va_arg(args, char *);
		fprintf(stderr,"%s", str);
		i++;
	}
	fprintf(stderr,"\n");
	va_end(args);
}

/*copies a string*/
char *copy_string(char *dest)
{
	char *str = NULL;
	size_t size = 0;

	if (dest == NULL)
		return (NULL);
	size = strlen(dest);
	/*Hacer un free*/
	str = malloc(size + 1);
	if (str == NULL)
		man_er(0, "Error: malloc failed");
	strcpy(str, dest);
	return (str);
}
