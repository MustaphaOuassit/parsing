/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_indice.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 01:53:26 by mouassit          #+#    #+#             */
/*   Updated: 2021/12/16 22:26:46 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_indice(int *i)
{
	if (*i < 0)
	{
		*i = 0;
		return (1);
	}
	return (0);
}

int	len_ambiguous(char *value, int i)
{
	int	len;

	if (i - 1 >= 0 && value[i - 1] != '>' && value[i - 1] != '<')
	{
		while (value[i])
		{
			if (value[i] == '>' || value[i] == '<')
				break ;
			i--;
			if (check_indice(&i))
				break ;
		}
	}
	len = 0;
	if (value[i] == '>' || value[i] == '<' || value[i] == '|')
		i++;
	while (value[i])
	{
		if (value[i] == '>' || value[i] == '<' || value[i] == '|')
			break ;
		len++;
		i++;
	}
	return (len);
}

void	check_start(int *i, char *value)
{
	if (*i - 1 >= 0 && value[*i - 1] != '>' && value[*i - 1] != '<')
	{
		while (value[*i])
		{
			if (value[*i] == '>' || value[*i] == '<')
				break ;
			*i = *i - 1;
			if (*i < 0)
			{
				*i = 0;
				break ;
			}
		}
	}
}

char	*fill_ambiguous(char *value, int len, int i, t_envp *env_list)
{
	char	*data;
	int		tmp;

	data = (char *)malloc(sizeof(char) * (len + 1));
	free_in_parcer(&env_list->allocation, data, NULL);
	data[len] = '\0';
	tmp = len;
	len = 0;
	check_start(&i, value);
	if (value[i] == '>' || value[i] == '<' || value[i] == '|')
		i++;
	while (len < tmp)
	{
		if (value[i] == '>' || value[i] == '<' || value[i] == '|')
			break ;
		data[len] = value[i];
		i++;
		len++;
	}
	return (data);
}

void	fill_dollar_exp(t_init *var, int tmp, char *value, int *start)
{
	int	i;

	i = 0;
	while (i < tmp)
	{
		var->dollar[i] = value[*start];
		i++;
		*start = *start + 1;
	}
}
