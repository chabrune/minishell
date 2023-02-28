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

int ft_isspace(int c)
{
    if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v')
        return 1;
    else
        return 0;
}

t_lexer *ft_lexer(char *input)
{
    // Initialisation des variables et allocation du buffer
    t_lexer *head = NULL;
    t_lexer *tail = NULL;
    int i = 0;
    int j = 0;
    int len = ft_strlen(input);
    char *buffer = (char *)malloc(len + 1);
    int buffer_len = 0;
    // Boucle principale pour traiter chaque mot de la ligne d'entrée
    while (i < len)
    {
        // Ignorer les espaces blancs en début de mot
        if(ft_isspace(input[i]))
            i++;
        // Copier le mot dans le buffer
        buffer_len = 0;
        while (i < len && !ft_isspace(input[i]))
            buffer[buffer_len++] = input[i++];
        buffer[buffer_len] = '\0';
        // Déterminer le type de token
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
        // Créer un nouveau nœud avec le mot et le jeton associé, et l'ajouter à la liste chaînée
        t_lexer *new = new_token(ft_strdup(buffer), token, j);
        if (head == NULL)
        {
            head = new;
            tail = new;
        }
        else
        {
            tail->next = new; // on fait pointer le new element vers le next de la queue
            new->prev = tail; // on fait pointer la queue vers le prev de de new
            tail = new; // le nouveau devient la queue
        }
    }
    // Libérer le buffer et retourner la tête de la liste chaînée
    free(buffer);
    return (head);
}
