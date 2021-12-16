/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 02:57:28 by mouassit          #+#    #+#             */
/*   Updated: 2021/12/16 21:53:52 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	skip_value(char *value, int *start)
{
	while (value[*start])
	{
		if (value[*start] == '?' && value[*start + 1] != '\0')
		{
			*start = *start + 1;
			break ;
		}
		*start = *start + 1;
	}
	*start = *start - 1;
}

void	fill_space(char *value, int *i, int *len, int ele)
{
	value[*i] = ' ';
	*i = *i + 1;
	while (value[*i])
	{
		if (value[*i] == ele)
		{
			if (value[*i + 1] != ' ')
				*len = *len - 1;
			value[*i] = ' ';
			break ;
		}
		value[*i] = ' ';
		*i = *i + 1;
	}
}

char	**check_len_values(char *value, int *len, int nb, t_envp *env_list)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_split(value, ' ');
	free_in_parcer(&env_list->allocation, NULL, split);
	while (split[i])
		i++;
	if (nb)
		i = i - nb;
	if (*len <= 0)
		*len = 0;
	*len = *len + i;
	if (*len == 0)
		*len = 1;
	return (split);
}

void	initialisation_get(t_init *var, char *value)
{
	var->i = 0;
	var->nb = 0;
	var->split = NULL;
	var->len = len_couts(value);
}

void	skip_dlm(int *nb, int *len)
{
	*nb = *nb + 1;
	*len = *len - 1;
}
