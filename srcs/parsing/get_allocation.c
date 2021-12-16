/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_allocation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 02:58:20 by mouassit          #+#    #+#             */
/*   Updated: 2021/12/17 00:20:48 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_allocation(char *value, t_envp *env_list)
{
	t_init	var;

	initialisation_get(&var, value);
	while (value[var.i])
	{
		if (value[var.i] != '\"' && value[var.i] != '\''
			&& value[var.i] != ' ' && value[var.i + 1] == '\"'
			&& value[var.i + 1] == '\'')
			skip_dlm(&var.nb, &var.len);
		else if (value[var.i] == ' ' && ((value[var.i + 1] == '\"')
				|| (value[var.i + 1] == '\'')))
			var.len++;
		if (value[var.i] == '\"')
			fill_space(value, &var.i, &var.len, '\"');
		else if (value[var.i] == '\'')
			fill_space(value, &var.i, &var.len, '\'');
		else if (value[var.i] == '$' && delimiter_skip(value, &var.i))
		{
			var.nb++;
			skip_value(value, &var.i);
		}
		var.i++;
	}
	var.split = check_len_values(value, &var.len, var.nb, env_list);
	return (var.len);
}

void	fill_dollar_args(char *value, int *start, t_init *var)
{
	if (value[*start] == '$' && delimiter_skip(value, start))
		skip_value(value, start);
	else
	{
		var->check = 1;
		var->len++;
	}
}

void	file_len_args(int *start, char *value, int *len, int ele)
{
	*start = *start + 1;
	while (value[*start])
	{
		if (value[*start] == ele)
			break ;
		*len = *len + 1;
		*start = *start + 1;
	}
}

int	len_args(char *value, int *start)
{
	t_init	var;

	var.len = 0;
	var.check = 0;
	while (value[*start])
	{
		if (value[*start] == '\"')
			file_len_args(start, value, &var.len, '\"');
		else if (value[*start] == '\'')
			file_len_args(start, value, &var.len, '\'');
		else if (value[*start] != ' ')
		{
			if (value[*start] != '\"')
				fill_dollar_args(value, start, &var);
		}
		else if (value[*start] == ' ' && var.check == 1)
			break ;
		*start = *start + 1;
	}
	return (var.len);
}

void	file_args_double(t_init *var, char *value, char **filter, int *tmp)
{
	*tmp = *tmp + 1;
	while (value[*tmp])
	{
		if (value[*tmp] == '\"')
		{
			*tmp = *tmp + 1;
			break ;
		}
		filter[var->start][var->i] = value[*tmp];
		var->i++;
		*tmp = *tmp + 1;
	}
}
