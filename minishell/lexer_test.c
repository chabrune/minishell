#include "minishell.h"

t_lexer *new_token(char *str, t_tokens token, int i) 
{
    t_lexer *new = ft_calloc(1, sizeof(t_lexer));
    if(!new)
        return(NULL);
    new->str = str;
    new->token = token;
    new->i = i;
    new->next = NULL;
    new->prev = NULL;
    return (new);
}

void print_tokens(t_lexer *head) 
{
    t_lexer *tmp;
    tmp = head;
    while (tmp)
    {
        printf("=================\n");
        printf("Token: %s\n", tmp->str);
        printf("Token type: %d\n", tmp->token);
        printf("Index: %d\n", tmp->i);
        printf("=================\n");
        tmp = tmp->next;
    }
}

int ft_isspace(int c)
{
    if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v')
        return 1;
    else
        return 0;
}

int ft_istoken(int c)
{
    if(!c)
        return(0);
    if(c == '>' || c == '<' || c == '|')
        return (1);
    else
        return(0);
}

t_tokens chose_token(char *str)
{
	t_tokens token = 0;

    if (ft_strncmp(str, "|", 2) == 0)
        token = PIPE;
    else if (ft_strncmp(str, "<", 2) == 0)
        token = LESS;
    else if (ft_strncmp(str, "<<", 3) == 0)
        token = LESSLESS;
    else if (ft_strncmp(str, ">", 2) == 0)
        token = GREAT;
    else if (ft_strncmp(str, ">>", 3) == 0)
        token = GREATGREAT;
	return (token);
}

t_lexer *ft_lexer(char *input, t_tools *tools)
{
    t_lexer *head;
    t_lexer *tail;
    t_lexer *new;
	t_tokens token;
    char *buffer;
    int i;
	int	j;
	int	k;
	
    head = 0;
    tail = 0;
    i = 0;
	k = 1;
    if (check_closed_quotes(input) == 1)
        return (0);
    input = expander(tools, input);
    while (input[i])
    {
        while (ft_isspace(input[i]) && input[i])
            i++;
        // printf("INPUT ::::: %s\n", input);
        if (input[i] == '\'')
        {
        	j = 0;
			while (input[i] && input[i] != '\'')
			{
				j++;
				i++;
			}
            i++;
			buffer = ft_calloc(j, sizeof(char));
			i = i - j;
			j = 0;
			while (input[i] && input[i] != '\'')
				buffer[j++] = input[i++];
            // i++;
			token = WORD;
        }
        else if (input[i] == '\"')
        {
        	j = 0;
			while (input[i] && input[i] != '\"')
			{
				j++;
				i++;
			}
            j += 2;
			buffer = ft_calloc(j, sizeof(char));
			i = i - j;
            printf("tessssssst ::: %c\n", input[i]);
			j = 0;
			while (input[i] && input[i] != '\"')
				buffer[j++] = input[i++];
            i++;
			token = WORD;
        }
		else if (ft_istoken(input[i]) == 0)
		{
        	j = 0;
			while (input[i] && !ft_isspace(input[i]) && ft_istoken(input[i]) == 0)
			{
				j++;
				i++;
			}
			buffer = ft_calloc(j + 1, sizeof(char));
			i = i - j;
			j = 0;
			while (input[i] && !ft_isspace(input[i]) && ft_istoken(input[i]) == 0)
				buffer[j++] = input[i++];
			token = WORD;
		}
		else 
		{
			j = 0;
			while (input[i] && ft_istoken(input[i]) == 1)
			{
				j++;
				i++;
			}
			buffer = ft_calloc(j + 1, sizeof(char));
			i = i - j;
			j = 0;
			while (input[i] && ft_istoken(input[i]) == 1)
				buffer[j++] = input[i++];
			token = chose_token(buffer);
			if (token == 0)
				printf("Erreur a faire bien plus tard\n");
		}
		while (ft_isspace(input[i]) && input[i])
            i++;
        new = new_token(ft_strdup(buffer), token, k++);
        if (head == NULL)
        {
            head = new;
            tail = new;
        }
        else
        {
            tail->next = new;
            new->prev = tail;
            tail = new;
        }
		free(buffer);
    }
	return(head);
}
