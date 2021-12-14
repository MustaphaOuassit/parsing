/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 01:50:26 by mouassit          #+#    #+#             */
/*   Updated: 2021/12/14 05:50:25 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env(char *value, t_envp *env_list)
{
	char	*dollar;
	int		len;
	t_envp	*tmp;

	len = 0;
	tmp = env_list;
	if (value[0] == '?')
		return (ft_itoa(env_list->exit_status));
	dollar = dollar_allocation(value, &len, env_list);
	dollar = fill_dollar_two(dollar, value, len, env_list);
	if (env_list->type == 5)
		return (dollar);
	while (tmp != NULL)
	{
		if (!ft_strcmp(tmp->key, value))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (dollar);
}

char	*fill_dollar_one(char *value, t_envp *env_list)
{
	char	*dollar;
	int		i;
	int		j;

	i = 0;
	j = 0;
	dollar = (char *)malloc(sizeof(char) * ((int)ft_strlen(value) + 3));
	free_in_parcer(&env_list->allocation, dollar, NULL);
	dollar[(int)ft_strlen(value) + 2] = '\0';
	while (i < (int)ft_strlen(value) + 2)
	{
		if (i == 0)
			dollar[i] = '$';
		else
		{
			dollar[i] = value[j];
			j++;
		}
		i++;
	}
	return (dollar);
}

char	*get_env_couts(char *value, t_envp *env_list)
{
	t_envp	*tmp;
	char	*dollar;

	tmp = env_list;
	if (value[0] == '?')
		return (ft_itoa(env_list->exit_status));
	dollar = fill_dollar_one(value, env_list);
	if (env_list->type == 5)
		return (dollar);
	while (tmp != NULL)
	{
		if (!ft_strcmp(tmp->key, value))
			return (tmp->value);
		tmp = tmp->next;
	}
	tmp = NULL;
	return ("\0");
}

void	continue_len(char *dollar, t_init *var, int *start, t_envp *env_list)
{
	if (dollar)
	{
		var->i = var->i + (int)ft_strlen(get_env_couts(dollar, env_list));
		var->i = var->i - 1;
		*start = *start - 1;
	}
}
