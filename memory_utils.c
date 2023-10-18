#include "shell.h"

/**
* buffer_free - Frees a pointer and sets the address to NULL.
* @ptr: Address of the pointer to free.
*
* Return: 1 if successfully freed, otherwise 0.
*/
int buffer_free(void **ptr)
{
if (ptr && *ptr)
{
free(*ptr);
*ptr = NULL;
return (1);
}
return (0);
}
