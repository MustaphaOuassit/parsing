/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 03:05:08 by mouassit          #+#    #+#             */
/*   Updated: 2021/12/16 22:16:35 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*fill_file(char *value, t_envp *env_list)
{
	t_init	var;

	initialisation_file(&var, value, env_list);
	while (var.len < var.tmp)
	{
		if (value[var.i] == '$' && delimiter(value, &var.i))
		{
			var.file_name[var.len] = value[var.i];
			var.i++;
			var.len++;
			var.check = 1;
		}
		if (value[var.i] == '?' && var.check == 1)
		{
			var.i++;
			var.check = 0;
		}
		else
		{
			var.file_name[var.len] = value[var.i];
			var.i++;
			var.len++;
		}
	}
	return (var.file_name);
}

int	len_herdoc(char *value)
{
	int	i;
	int	len;
	int	check;

	i = 0;
	len = 0;
	check = 0;
	while (value[i])
	{
		if (value[i] == '\"')
			skip_content_value(value, &i, &len, '\"');
		else if (value[i] == '\'')
			skip_content_value(value, &i, &len, '\'');
		else
			len++;
		i++;
	}
	return (len);
}

void	file_double(char *value, int *i, int *len, char *file_name)
{
	*i = *i + 1;
	while (value[*i])
	{
		if (value[*i] == '\"')
			break ;
		file_name[*len] = value[*i];
		*i = *i + 1;
		*len = *len + 1;
	}
}

void	file_single(char *value, int *i, int *len, char *file_name)
{
	*i = *i + 1;
	while (value[*i])
	{
		if (value[*i] == '\'')
			break ;
		file_name[*len] = value[*i];
		*i = *i + 1;
		*len = *len + 1;
	}
}

char	*fill_herdoc(char *value, t_envp *env_list)
{
	t_init	var;

	var.i = 0;
	var.len = len_herdoc(value);
	var.tmp = var.len;
	var.file_name = (char *)malloc(sizeof(char) * (var.len + 1));
	free_in_parcer(&env_list->allocation, var.file_name, NULL);
	var.file_name[var.len] = 0;
	var.len = 0;
	while (var.len < var.tmp)
	{
		if (value[var.i] == '\"')
			file_double(value, &var.i, &var.len, var.file_name);
		else if (value[var.i] == '\'')
			file_single(value, &var.i, &var.len, var.file_name);
		else
		{
			var.file_name[var.len] = value[var.i];
			var.len++;
		}
		var.i++;
	}
	return (var.file_name);
}
