/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 10:26:07 by mouassit          #+#    #+#             */
/*   Updated: 2021/11/21 10:26:09 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../includes/minishell.h"

int     skip_spaces(char *cmd)
{
    int i;

    i = 0;
    while (cmd[i])
    {
        if (cmd[i] != ' ')
            break;
        i++;
    }
    return(i);
}

int check_close(char *value, int i)
{
    while (value[i])
    {
        if(value[i] == '\"')
            return(1);
        i++;
    }
    return(0);
}

int len_token(char *cmd, int start)
{
    int i;
    int len;
    int close;

    i = start;
    len = 0;
    close = 0;
    while (cmd[i])
    {
        if(cmd[i] == '\"')
        {
            i++;
            close = check_close(cmd, i);
			if(!close)
            {
                len = -1;
                return(len);
            }
            len++;
            while (cmd[i])
            {
                if(cmd[i] == '\"')
                    break;
                len++;
                i++;
            }
        }
        i++;
        len++;
        if(cmd[i] == ' ')
            break;
    }
   return(len); 
}

char     *get_token(char *cmd, int *start)
{
    int len;
    int i;
    char *token;

    i = 0;
    token = NULL;
    len = len_token(cmd,*start);
    if(len == -1)
    {
        *start = -1;
        return(NULL);
    }
    token = (char *)malloc(sizeof(char) * (len + 1));
    token[len] = '\0';
    while (token[i])
    {
        token[i] = cmd[*start];
        *start = *start + 1;
        i++;
    }
    return(token);
}

void    parsing(char *cmd, int *error)
{
    int start;
    char *token;
    t_list *head;

    head = NULL;
    start = skip_spaces(cmd);
    token = NULL;
    while (cmd[start])
    {
        if(cmd[start] != ' ')
        {
            token = get_token(cmd,&start);
            if(start == -1)
            {
                *error = -1;
                break;
            }
            list_tokens(&head,token);
        }
        start++;
    }
    if(*error != -1)
    {
        *error = check_tokens(head,*error);
    }
    *error = 1;
}