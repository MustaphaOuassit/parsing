/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_spaces.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 01:40:40 by mouassit          #+#    #+#             */
/*   Updated: 2021/12/14 06:38:03 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	skip_spaces(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] != ' ')
			break ;
		i++;
	}
	return (i);
}

int	check_close(char *value, int i, int ele)
{
	while (value[i])
	{
		if (value[i] == ele)
			return (1);
		i++;
	}
	return (0);
}

int	check_double_couts(char *value, int *i, int *len, int *close)
{
	*i = *i + 1;
	*close = check_close(value, *i, '\"');
	if (!*close)
	{
		*len = -1;
		return (*len);
	}
	*len = *len + 1;
	while (value[*i])
	{
		if (value[*i] == '\"')
			break ;
		*len = *len + 1;
		*i = *i + 1;
	}
	return (*len);
}

int	check_single_couts(char *value, int *i, int *len, int *close)
{
	*i = *i + 1;
	*close = check_close(value, *i, '\'');
	if (!*close)
	{
		*len = -1;
		return (*len);
	}
	*len = *len + 1;
	while (value[*i])
	{
		if (value[*i] == '\'')
			break ;
		*len = *len + 1;
		*i = *i + 1;
	}
	return (*len);
}

int	len_token(char *cmd, int start)
{
	t_init	var;

	var.i = start;
	var.len = 0;
	var.close = 0;
	while (cmd[var.i])
	{
		if (cmd[var.i] == '\"')
		{
			var.len = check_double_couts(cmd, &var.i, &var.len, &var.close);
			if (var.len == -1)
				return (var.len);
		}
		else if (cmd[var.i] == '\'')
		{
			var.len = check_single_couts(cmd, &var.i, &var.len, &var.close);
			if (var.len == -1)
				return (var.len);
		}
		var.i++;
		var.len++;
		if (cmd[var.i] == ' ')
			break ;
	}
	return (var.len);
}
