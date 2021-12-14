/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 02:56:19 by mouassit          #+#    #+#             */
/*   Updated: 2021/12/14 04:59:28 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	error_redirection(int check, t_tokens *tokens, t_envp *env_list)
{
	if (check == 1 || tokens->next == NULL)
	{
		if (check == 1)
			print_error_rdt(tokens->value, env_list);
		else
			print_error_rdt("newline", env_list);
		return (1);
	}
	return (0);
}

int	get_len_double(char *value)
{
	int	i;
	int	len;
	int	check;

	i = 0;
	len = 0;
	check = 0;
	while (i <= (int)ft_strlen(value))
	{
		if (value[i] == '\"' )
			len++;
		i++;
	}
	return (len / 2);
}

void	add_check_couts(int *l, int *i, char *value, int ele)
{
	*l = *l + 1;
	*i = *i + 1;
	while (value[*i])
	{
		if (value[*i] == ele)
		{
			*l = *l + 1;
			break ;
		}
		*i = *i + 1;
	}
}

int	len_couts(char *value)
{
	int	i;
	int	l;

	i = 0;
	l = 0;
	while (value[i])
	{
		if (value[i] == '\"')
			add_check_couts(&l, &i, value, '\"');
		if (value[i] == '\'')
			add_check_couts(&l, &i, value, '\'');
		i++;
	}
	return (l / 2);
}

int	end_dollar(char *value, int *start)
{
	if (value[*start] == '\"'
		|| value[*start] == '>' || value[*start] == '<'
		|| value[*start] == '|' || value[*start] == '$'
		|| value[*start] == '\'')
	{
		return (1);
	}
	return (0);
}
