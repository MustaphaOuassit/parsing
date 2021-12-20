/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dlm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 02:06:23 by mouassit          #+#    #+#             */
/*   Updated: 2021/12/20 10:52:05 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_dlm(int c)
{
	if (c != '\'' && c != '\"' && c != ' ' && c != '$'
		&& c != '|' && c != '<' && c != '>' && c != '\0')
		return (1);
	return (0);
}

int	allocation_expand(char *value, int *i)
{
	int	len;

	len = 0;
	*i = *i + 1;
	if (value[*i] == '?')
	{
		*i = *i + 1;
		return (1);
	}
	while (value[*i])
	{
		if (value[*i] == '\'' || value[*i] == '\"' || value[*i] == ' '
			|| value[*i] == '$' || value[*i] == '|' || value[*i] == '<'
			|| value[*i] == '>' || value[*i] == '\0')
			break ;
		*i = *i + 1;
		len++;
	}
	return (len);
}

char	*get_env_hrd(char *value, t_envp *env_list)
{
	t_envp	*tmp;
	char	*str;

	str = NULL;
	tmp = env_list;
	if (value[0] == '?')
	{
		if (g_signal_flag)
			return ("1");
		str = ft_itoa(env_list->exit_status);
		free_in_parcer(&env_list->allocation, str, NULL);
		return (str);
	}
	while (tmp != NULL)
	{
		if (!ft_strcmp(tmp->key, value))
			return (tmp->value);
		tmp = tmp->next;
	}
	tmp = NULL;
	return ("\0");
}

void	get_dollar_expand(char *value, t_init *var, t_envp *env_list)
{
	t_init	vr;
	char	*dollar;

	vr.tmp = var->i;
	vr.i = 0;
	vr.len = allocation_expand(value, &var->i);
	dollar = (char *)malloc(sizeof(char) * (vr.len + 1));
	free_in_parcer(&env_list->allocation, dollar, NULL);
	dollar[vr.len] = '\0';
	vr.tmp++;
	while (vr.i < vr.len)
	{
		dollar[vr.i] = value[vr.tmp];
		vr.tmp++;
		vr.i++;
	}
	var->len = var->len + (int)ft_strlen(get_env_hrd(dollar, env_list));
}

int	len_expand(char *value, t_envp *env_list)
{
	t_init	var;

	var.len = 0;
	var.i = 0;
	while (value[var.i])
	{
		if (value[var.i] == '$' && check_dlm(value[var.i + 1]))
			get_dollar_expand(value, &var, env_list);
		else
		{
			var.len++;
			var.i++;
		}
	}
	return (var.len);
}
