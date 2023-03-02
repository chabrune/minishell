#include "minishell.h"

t_lexer *new_token(char *str, t_tokens token, int i)
{
    t_lexer *new = (t_lexer *)malloc(sizeof(t_lexer));
    new->str = str;
    new->token = token;
    new->i = i;
    new->next = NULL;
    new->prev = NULL;
    return (new);
}

void print_tokens(t_lexer *head)
{
    while (head != NULL)
    {
        printf("Token: %s\n", head->str);
        printf("Token type: %d\n", head->token);
        printf("Index: %d\n", head->i);
        head = head->next;
    }
}

t_lexer *ft_lexer(char *input)
{
    t_lexer *head = NULL;
    t_lexer *tail = NULL;
    int i = 0;
    int j = 0;
    int len = ft_strlen(input);
    char *buffer = (char *)malloc(len + 1);
    int buffer_len = 0;
    while (i < len)
    {
        while(input[i] == 32)
            i++;
        buffer_len = 0;
        while (i < len && input[i] != 32)
            buffer[buffer_len++] = input[i++];
        buffer[buffer_len] = '\0';
        t_tokens token = WORD;
        if (ft_strncmp(buffer, "|", 2) == 0)
            token = PIPE;
        else if (ft_strncmp(buffer, "<", 2) == 0)
            token = LESS;
        else if (ft_strncmp(buffer, "<<", 3) == 0)
            token = LESSLESS;
        else if (ft_strncmp(buffer, ">", 2) == 0)
            token = GREAT;
        else if (ft_strncmp(buffer, ">>", 3) == 0)
            token = GREATGREAT;
        j += 1;
        t_lexer *new = new_token(ft_strdup(buffer), token, j);
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
    }
    free(buffer);
    return (head);
}