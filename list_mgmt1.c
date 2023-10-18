#include "shell.h"

/**
* count_nodes - Determines the length of linked list.
* @h: Pointer to first node.
*
* Return: Size of list.
*/
size_t count_nodes(const list_str_t *h)
{
size_t i = 0;

while (h)
{
h = h->next;
i++;
}
return (i);
}

/**
* convert_list_to_strings - Converts the list to an array of strings.
* @head: Pointer to the first node.
*
* Return: Array of strings.
*/
char **convert_list_to_strings(list_str_t *head)
{
list_str_t *node = head;
size_t i = count_nodes(head), j;
char **strs;

if (!head || !i)
return (NULL);

strs = malloc(sizeof(char *) * (i + 1));
if (!strs)
return (NULL);

for (i = 0; node; node = node->next, i++)
{
strs[i] = strdup(node->str);
if (!strs[i])
{
for (j = 0; j < i; j++)
free(strs[j]);
free(strs);
return (NULL);
}
}
strs[i] = NULL;
return (strs);
}

/**
* print_list_items - Displays all elements of a linked list.
* @h: Pointer to first node.
*
* Return: Size of list.
*/
size_t print_list_items(const list_str_t *h)
{
size_t i = 0;

while (h)
{
_puts(convert_number(h->num, 10, 0));
_putchar(':');
_putchar(' ');
_puts(h->str ? h->str : "(nil)");
_puts("\n");
h = h->next;
i++;
}
return (i);
}

/**
* locate_node_start - Returns node whose string starts with prefix.
* @node: Pointer to list head.
* @prefix: String to match.
* @c: The next character after prefix to match.
*
* Return: Matched node or NULL.
*/
list_str_t *locate_node_start(list_str_t *node, char *prefix, char c)
{
char *p = NULL;

while (node)
{
p = strstr(node->str, prefix);
if (p && ((c == -1) || (*p == c)))
return (node);
node = node->next;
}
return (NULL);
}

/**
* determine_node_index - Gets the index of a node.
* @head: Pointer to list head.
* @node: Pointer to the node.
*
* Return: Index of node or -1.
*/
ssize_t determine_node_index(list_str_t *head, list_str_t *node)
{
size_t i = 0;

while (head)
{
if (head == node)
return (i);
head = head->next;
i++;
}
return (-1);
}
