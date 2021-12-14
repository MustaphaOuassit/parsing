/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 03:03:03 by mouassit          #+#    #+#             */
/*   Updated: 2021/12/14 04:54:13 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	dollar_handler(char *value, int *i, int *check, int *len)
{
	if (value[*i] == '$')
		*check = 1;
	if (value[*i] == '?' && *check == 1)
	{
		*len = *len - 1;
		*check = 0;
	}
	*len = *len + 1;
}

int	get_len_word(char *value)
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
		else if (value[i] != '\'' && value[i] != '\"')
			dollar_handler(value, &i, &check, &len);
		i++;
	}
	return (len);
}

void	check_point(char *value, int *i)
{
	while (value[*i])
	{
		if (value[*i] == '?')
			break ;
		*i = *i + 1;
	}
}

int	get_len(char *value)
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
		else if (value[i] == '$' && delimiter(value, &i))
			check_point(value, &i);
		else
			len++;
		i++;
	}
	return (len);
}

int	is_couts(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (value[i] == '\'' || value[i] == '\"'
			|| (value[i] == '$' && !(delimiter(value, &i))))
			return (1);
		i++;
	}
	return (0);
}
