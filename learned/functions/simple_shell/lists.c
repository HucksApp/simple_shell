#include "shell.h"

/**
 * add_nodeint - add a new node at the beggining of the list
 * @head: pointer to the beginning of the list
 * @str: the string to initialize
 * Return: address of newnode
 */
env_t *add_nodeint(env_t **head, const char *str)
{
	env_t *newnode;

	if (head == NULL)
		return (NULL);
	newnode = malloc(sizeof(env_t));
	if (newnode == NULL)
		return (NULL);
	if (str)
	{
		newnode->str = strdup(str);
		if (newnode->str == NULL)
		{
			free(newnode);
			return (NULL);
		}
	}
	newnode->next = *head;
	*head = newnode;
	return (newnode);
}

/**
 * add_nodeint_end -  adds a new node at the end of a env_t list.
 * @head: pointer to the head of the list
 * @str: string to initialize
 * Return: address of new node
 */
env_t *add_nodeint_end(env_t **head, const char *str)
{
	env_t *newnode;
	env_t *p = *head;

	newnode = malloc(sizeof(env_t));
	if (newnode == NULL)
		return (NULL);
	if (str)
	{
		newnode->str = strdup(str);
		if (newnode->str == NULL)
		{
			free(newnode);
			return (NULL);
		}
	}
	newnode->next = NULL;

	if (*head == NULL)
		*head = newnode;
	else
	{
		while (p->next != NULL)
		{
			p = p->next;
		}
		p->next = newnode;
	}
	return (newnode);
}
/**
 * delete_nodeint_at_index - deletes the node at index @index of
 * a env_t linked list
 * @head: the pointer to the header node of the list
 * @index: the index with which to delete the element of
 * Return: 1(Success) else -1
 */
int delete_nodeint_at_index(env_t **head, unsigned int index)
{
	unsigned int i = 0;
	env_t *p;
	env_t *temp;

	if (!head || *head == NULL)
		return (-1);
	p = *head;
	if (index == 0)
	{
		*head = p->next;
		free(p->str);
		free(p);
		return (1);
	}
	for (i = 0; p != NULL && i < (index - 1); i++)
		p = p->next;
	if (p == NULL)
		return (-1);
	if (index > 0)
	{
		temp = p->next;
		if (temp == NULL)
			return (-1);
		p->next = temp->next;
		free(temp->str);
		free(temp);
		return (1);
	}

	return (-1);
}
/**
 * free_listint2 - frees a listint_t list.
 * @head: pointer to the head node
 */
void free_listint2(env_t **head)
{
	env_t *p;

	if (!head)
		return;
	p = *head;
	while (*head != NULL)
	{
		p = *head;
		*head = (*head)->next;
		free(p->str);
		free(p);
	}
	*head = NULL;
}
