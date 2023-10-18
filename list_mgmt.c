#include "shell.h"

/**
* create_node - creates a new node and adds it to the start of the list.
* @head: address of pointer to head node.
* @str: str field of the node.
* @num: node index used by history.
* Return: pointer to the newly created node.
*/
list_str_t *create_node(list_str_t **head, const char *str, int num)
{
list_str_t *new_head;

if (!head)
return (NULL);

new_head = malloc(sizeof(list_str_t));
if (!new_head)
return (NULL);

_memset((void *)new_head, 0, sizeof(list_str_t));
new_head->num = num;

if (str)
{
new_head->str = _strdup(str);
if (!new_head->str)
{
free(new_head);
return (NULL);
}
}

new_head->next = *head;
*head = new_head;

return (new_head);
}

/**
* append_node - appends a node to the end of the list.
* @head: address of pointer to head node.
* @str: str field of the node.
* @num: node index used by history.
* Return: pointer to the newly appended node.
*/
list_str_t *append_node(list_str_t **head, const char *str, int num)
{
list_str_t *new_node, *node;

if (!head)
return (NULL);

node = *head;
new_node = malloc(sizeof(list_str_t));
if (!new_node)
return (NULL);

_memset((void *)new_node, 0, sizeof(list_str_t));
new_node->num = num;

if (str)
{
new_node->str = _strdup(str);
if (!new_node->str)
{
free(new_node);
return (NULL);
}
}

if (node)
{
while (node->next)
node = node->next;
node->next = new_node;
}
else
*head = new_node;

return (new_node);
}

/**
* display_list_string - displays only the str element of the linked list.
* @h: pointer to the first node.
* Return: size of the list.
*/
size_t display_list_string(const list_str_t *h)
{
size_t i = 0;

while (h)
{
_puts(h->str ? h->str : "(nil)");
_puts("\n");
h = h->next;
i++;
}

return (i);
}

/**
* remove_node_by_index - removes a node by its index.
* @head: address of pointer to first node.
* @index: index of the node to remove.
* Return: 1 on success, 0 on failure.
*/
int remove_node_by_index(list_str_t **head, unsigned int index)
{
list_str_t *node, *prev_node;
unsigned int i = 0;

if (!head || !*head)
return (0);

if (!index)
{
node = *head;
*head = (*head)->next;
free(node->str);
free(node);
return (1);
}

node = *head;
while (node)
{
if (i == index)
{
prev_node->next = node->next;
free(node->str);
free(node);
return (1);
}
i++;
prev_node = node;
node = node->next;
}

return (0);
}

/**
* dispose_list - frees all nodes of a list.
* @head_ptr: address of pointer to head node.
*/
void dispose_list(list_str_t **head_ptr)
{
list_str_t *node, *next_node;

if (!head_ptr || !*head_ptr)
return;

node = *head_ptr;
while (node)
{
next_node = node->next;
free(node->str);
free(node);
node = next_node;
}

*head_ptr = NULL;
}
