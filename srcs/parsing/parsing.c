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

char     *get_token(char *cmd, int *start, t_envp *envp_list)
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
    free_in_parcer(&envp_list->allocation,token,NULL);
    token[len] = '\0';
    while (i < len)
    {
        token[i] = cmd[*start];
        *start = *start + 1;
        i++;
    }
    return(token);
}

int     end_str(char *cmd)
{
    int i;

    i = (int)ft_strlen(cmd) - 1;
    if(i < 0)
        return(0);
    while (cmd[i])
    {
        if (cmd[i] != ' ')
            break;
        i--;
    }
    return(i);
}

int    multi_couts(int *i, char *cmd,int ele)
{
    *i = *i + 1;
    if(!check_close(cmd,*i,ele))
        return(1);
    while (cmd[*i])
    {
        if(cmd[*i] == ele)
        {
            *i = *i + 1;
            break;
        }
        *i = *i + 1;
    }
    return(0);
}

int     first_pipe(char *cmd, int start)
{
    if(cmd[start] == '|' && cmd[start + 1] != '|')
    {
        write(1,"minishell: syntax error near unexpected token `|'\n",50);
        return(1);
    }
    if(cmd[start] == '|' && cmd[start + 1] == '|')
    {
        write(1,"minishell: syntax error near unexpected token `||'\n",51);
        return(1);
    }
    return(0);
}

int    middle_pipe(char *cmd, int *i)
{
    if(cmd[*i] == '|')
    {
        *i = *i + 1;
        while (cmd[*i])
        {
            if(cmd[*i] == ' ')
                *i = *i + 1;
            else if(cmd[*i] == '|')
            {
                write(1,"minishell: syntax error near unexpected token `|'\n",51);
                return(1);
             }
             else
                break;
        }
        *i = *i - 1;
    }
    return(0);
}

int     end_pipe(char *cmd, int end)
{
    if(cmd[end] == '|')
    {
        write(1,"minishell: syntax error near unexpected token `|'\n",51);
        return(1);
    }
    return (0);
}

int     check_pipe(char *cmd, int start)
{
    t_init var;

    var.end = end_str(cmd);
    var.i = start;
    if(first_pipe(cmd,start))
        return(258);
    while (cmd[var.i])
    {
        if(cmd[var.i] == '\"')
        {
            if(multi_couts(&var.i,cmd,'\"'))
                return(1);
        }
        if(cmd[var.i] == '\'')
        {
            if(multi_couts(&var.i,cmd,'\''))
                return(1);
        }
        if (middle_pipe(cmd,&var.i))
            return(258);
        var.i++;
    }
    if(end_pipe(cmd,var.end))
        return(258);
    return(0);
}

int     continue_error(t_list *head,int error,t_envp *env_list,t_data **data)
{
    if(error != -1)
        error = check_tokens(head,error,env_list,data);
    return(error);
}

int    parsing(char *cmd, int *error,t_envp *env_list, t_data **data)
{
    t_init var;

    env_list->allocation = NULL;
    var.head = NULL;
    var.start = skip_spaces(cmd);
    var.token = NULL;
    *error = check_pipe(cmd,var.start);
    if(*error)
        return(0);
    while (var.start < (int)ft_strlen(cmd))
    {
        if(cmd[var.start] != ' ')
        {
            var.token = get_token(cmd,&var.start,env_list);
            if(var.start == -1)
            {
                *error = 1;
                break;
            }
            list_tokens(&var.head,var.token,env_list);
        }
        var.start++;
    }
    *error = continue_error(var.head,*error,env_list,data);
    return(0);
}