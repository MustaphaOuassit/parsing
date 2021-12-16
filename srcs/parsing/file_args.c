/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 02:59:22 by mouassit          #+#    #+#             */
/*   Updated: 2021/12/16 22:25:57 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	file_args_single(t_init *var, char *value, char **filter, int *tmp)
{
	*tmp = *tmp + 1;
	while (value[*tmp])
	{
		if (value[*tmp] == '\'')
		{
			*tmp = *tmp + 1;
			break ;
		}
		filter[var->start][var->i] = value[*tmp];
		var->i++;
		*tmp = *tmp + 1;
	}
}

void	file_args_dollar(int *tmp, t_init *var, char *value, char **filter)
{
	if (value[*tmp] == '$' && delimiter_skip(value, tmp))
		skip_value(value, tmp);
	else
	{
		filter[var->start][var->i] = value[*tmp];
		var->i++;
	}
	*tmp = *tmp + 1;
}

char	*initial(t_init *var, t_envp *env_list, char **filter, char *value)
{
	var->i = len_args(value, &var->j);
	filter[var->start] = (char *)malloc(sizeof(char) * (var->i + 1));
	free_in_parcer(&env_list->allocation, filter[var->start], NULL);
	filter[var->start][var->i] = '\0';
	var->check = var->i;
	var->i = 0;
	return (filter[var->start]);
}

char	**declar(int *len, int *j, int *tmp, t_envp *env_list)
{
	char	**filter;

	filter = (char **)malloc(sizeof(char *) * (*len + 1));
	free_in_parcer(&env_list->allocation, NULL, filter);
	filter[*len] = 0;
	*j = 0;
	*tmp = 0;
	return (filter);
}

void	initialisation_args(t_init *var, char *value, t_envp *env_list)
{
	var->j = 0;
	var->i = 0;
	var->start = 0;
	var->check = 0;
	var->filter = NULL;
	var->vtmp = ft_strdup(value);
	free_in_parcer(&env_list->allocation, var->vtmp, NULL);
	var->len = get_allocation(var->vtmp, env_list);
}
