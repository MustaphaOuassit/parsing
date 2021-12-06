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

int check_close(char *value, int i, int ele)
{
    while (value[i])
    {
        if(value[i] == ele)
            return(1);
        i++;
    }
    return(0);
}

int   check_double_couts(char *value, int *i, int *len, int *close)
{
    *i = *i + 1;
    *close = check_close(value, *i,'\"');
	if(!*close)
    {
        *len = -1;
        return(*len);
    }
    *len = *len + 1;
    while (value[*i])
    {
        if(value[*i] == '\"')
            break;
        *len = *len + 1;
        *i = *i + 1;
    }
    return(*len);
}

int check_single_couts(char *value, int *i, int *len, int *close)
{
    *i = *i + 1;
    *close = check_close(value, *i,'\'');
	if(!*close)
    {
        *len = -1;
        return(*len);
    }
    *len = *len + 1;
    while (value[*i])
    {
        if(value[*i] == '\'')
            break;
        *len = *len + 1;
        *i = *i + 1;
    }
    return(*len);
}

int len_token(char *cmd, int start)
{
    t_init var;

    var.i = start;
    var.len = 0;
    var.close = 0;
    while (cmd[var.i])
    {
        if(cmd[var.i] == '\"')
        {
            var.len = check_double_couts(cmd, &var.i, &var.len, &var.close);
            if(var.len == -1)
                return(var.len);
        }
        else if(cmd[var.i] == '\'')
        {
            var.len = check_single_couts(cmd, &var.i,&var.len,&var.close);
            if(var.len == -1)
                return(var.len);
        }
        var.i++;
        var.len++;
        if(cmd[var.i] == ' ')
            break;
    }
   return(var.len); 
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

void    parsing(char *cmd, int *error,t_envp *env_list, t_data **data)
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
                *error = 1;
                break;
            }
            list_tokens(&head,token);
        }
        start++;
    }
    if(*error != -1)
        *error = check_tokens(head,*error,env_list,data);
}