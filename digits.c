#include "monty.h"

/**
 * count_digits - Counter arrays
 * @number: value have counted
 * Return: size
 */

int count_digits(int number)
{
	int size = 0;

	while (number != 0)
	{
		number /= 10;
		size++;
	}

	return (size);
}

/**
 * trans_number - Pointer that contain the revert numbers
 * @number: to revert
 * Return: pointer revert
 */

char *_itoa(int number)
{
	char *ptr, *ptrRev;
	int i = 0, j = 0, size = 0;

	size = count_digits(number);
	size == 0 ? size++ : size;
	ptr = malloc(size * sizeof(char) + 1);
	if (ptr == NULL)
	{
		free(ptr);
		return (NULL);
	}
	if (number == 0)
	{
		ptr[0] = '0';
		ptr[1] = '\0';
		return (ptr);
	}
	ptrRev = malloc(size * sizeof(char) + 1);
	if (ptrRev == NULL)
	{
		free(ptr);
		free(ptrRev);
		return (NULL);
	}
	while (i < size)
	{
		ptr[i] = (number % 10) + '0';
		number /= 10;
		i++;
	}
	ptr[i] = '\0';
	while (ptr[j] != '\0')
	{
		ptrRev[j] = ptr[i - 1];
		i--;
		j++;
	}
	ptrRev[j] = '\0';
	free(ptr);
	return (ptrRev);
}
