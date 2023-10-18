#include "shell.h"

/**
 * set_memory - Fills memory with a constant byte.
 * @s: The pointer to the memory area.
 * @b: The byte to fill *s with.
 * @n: The number of bytes to be filled.
 *
 * Return: Pointer to the memory area s.
 */
char *set_memory(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * free_double_pointer - Frees an array of strings.
 * @pp: Array of strings.
 */
void free_double_pointer(char **pp)
{
	char **temp = pp;

	if (!pp)
		return;

	while (*pp)
		free(*pp++);

	free(temp);
}

/**
 * resize_memory - Resizes a block of memory.
 * @ptr: Pointer to the previous allocated block.
 * @old_size: Byte size of the previous block.
 * @new_size: Byte size of the new block.
 *
 * Return: Pointer to the adjusted memory block.
 */
void *resize_memory(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *resized_memory;

	if (!ptr)
		return (malloc(new_size));

	if (!new_size)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	resized_memory = malloc(new_size);
	if (!resized_memory)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		resized_memory[old_size] = ((char *)ptr)[old_size];

	free(ptr);
	return (resized_memory);
}
