#include "minishell.h"

static void	add_node(t_lexer **lexer, char *str, t_tokens token, int i)
{
	t_lexer *node;

	node = malloc(sizeof(t_lexer));
	if (!node)
		return ;
	node->str = str;
	node->token = token;
	node->i = i;
	node->next = NULL;
	if (!(*lexer))
	{
		node->prev = NULL;
		*lexer = node;
	}
	else
	{
		node->prev = (*lexer);
		while ((*lexer)->next)
			(*lexer) = (*lexer)->next;
		(*lexer)->next = node;
		*lexer = node->prev;
	}
}

t_lexer		*lexer(char *line)
{
	char	**words;
	t_lexer	*lexer;
	int		i;

	lexer = NULL;
	i = 0;
	words = ft_split(line, ' ');
	if (!words)
		return (NULL);
	while (words[i])
	{
		if (!ft_strcmp(words[i], "|"))
			add_node(&lexer, NULL, PIPE, i);
		else if (!ft_strcmp(words[i], "<"))
			add_node(&lexer, NULL, INPUT, i);
		else if (!ft_strcmp(words[i], "<<"))
			add_node(&lexer, NULL, HEREDOC, i);
		else if (!ft_strcmp(words[i], ">"))
			add_node(&lexer, NULL, OUTPUT, i);
		else if (!ft_strcmp(words[i], ">>"))
			add_node(&lexer, NULL, APPEND, i);
		else
			add_node(&lexer, words[i], WORD, i);
		i++;
	}
	ft_free_strs(words);
	return (lexer);
}