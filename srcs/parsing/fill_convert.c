/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_convert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 01:55:49 by mouassit          #+#    #+#             */
/*   Updated: 2021/12/16 22:21:39 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*fill_convert_three(char *value, int *start, t_envp *env_list)
{
	t_init	var;
	int		tmp;

	tmp = 0;
	if (value[*start + 1] == '?')
	{
		var.dollar = "?";
		*start = *start + 2;
	}
	else
	{
		var.len_dollar = check_dollar(value, *start + 1);
		var.dollar = (char *)malloc(sizeof(char) * (var.len_dollar + 1));
		free_in_parcer(&env_list->allocation, var.dollar, NULL);
		var.dollar[var.len_dollar] = '\0';
		tmp = var.len_dollar;
		*start = *start + 1;
		fill_dollar_exp(&var, tmp, value, start);
	}
	return (var.dollar);
}

void	dollar_manipulation(char *value, int *start, int *i, t_envp *env_list)
{
	t_init	var;
	int		tmp;

	var.tmp = *start;
	*i = *i + 1;
	var.dollar = NULL;
	tmp = 0;
	var.dollar = fill_convert_three(value, start, env_list);
	if (var.dollar)
	{
		var.value = get_env(var.dollar, env_list);
		if (env_list->type <= 4 && env_list->type >= 2 && is_space(var.value))
		{
			var.len = len_ambiguous(value, var.tmp);
			var.file_name = fill_ambiguous(value, var.len, var.tmp, env_list);
			env_list->file_name = ft_strdup(var.file_name);
			free_in_parcer(&env_list->allocation, env_list->file_name, NULL);
			env_list->type = 7;
			fill_data_ambiguous(&env_list->ambiguous, var.file_name, env_list);
		}
		*i = *i + (int)ft_strlen(var.value);
		*i = *i - 1;
		*start = *start - 1;
	}
}

int	delimiter(char *value, int *start)
{
	if (value[*start] == '$' && (value[*start + 1] == '_'
			|| value[*start + 1] == '?' || ft_isalpha(value[*start + 1]))
		&& value[*start + 1] && value[*start + 1] != '\"'
		&& value[*start + 1] != '>' && value[*start + 1] != '<'
		&& value[*start + 1] != '|' && value[*start + 1] != '$'
		&& value[*start + 1] != '\'')
	{
		return (1);
	}
	return (0);
}

int	delimiter_skip(char *value, int *start)
{
	if (value[*start] == '$' && (value[*start + 1] == '_'
			|| ft_isalpha(value[*start + 1]))
		&& value[*start + 1] && value[*start + 1] != '\"'
		&& value[*start + 1] != '>' && value[*start + 1] != '<'
		&& value[*start + 1] != '|' && value[*start + 1] != '$'
		&& value[*start + 1] != '\'')
	{
		return (1);
	}
	return (0);
}

void	single_couts(char *value, int *start, int *i, t_envp *env_list)
{
	if (value[*start] == '\'')
	{
		take_couts(start, value, i);
		*i = *i + 2;
	}
	else if (value[*start] == '$' && delimiter(value, start))
		dollar_manipulation(value, start, i, env_list);
	else
		*i = *i + 1;
}
