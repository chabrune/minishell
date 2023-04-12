#include <stdio.h>
#include <stdlib.h>

typedef struct s_node
{
	struct s_node	*next;
	struct s_node	*prev;
	int				data;
}					t_node;

t_node	*new_node(int x)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	insert_at_head(int x, t_node **head)
{
	t_node	*new;

	new = new_node(x);
	// 2 case -> list is empty / list inst empty
	if (head == NULL || !new)
		return ;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	(*head)->prev = new;
	new->next = *head;
	*head = new;
}

void	add_back(t_node **head, t_node *new)
{
	t_node	*tmp;

	if (!head || !new) // si head n'existe pas
		return ;
	new->next = NULL;
	if (!*head) // si *head est vide (si la chaine est vide)
	{
		new->prev = NULL;
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

int	main(void)
{
}