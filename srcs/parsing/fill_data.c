/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 16:25:08 by mouassit          #+#    #+#             */
/*   Updated: 2021/12/17 02:14:42 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	fill_data(t_tokens *tokens, t_data **data, t_envp *env_list)
{
	t_init	var;

	initialisation_data(&var);
	while (tokens != NULL)
	{
		if (tokens->type == 1 && var.check != 1)
		{
			var.pipe = 1;
			prep_data(&var, env_list, data);
			tokens = tokens->next;
		}
		else
		{
			if (file_error(&var, tokens, env_list))
				return (258);
			tokens = tokens->next;
		}
	}
	if (var.pipe == 0)
		prep_data(&var, env_list, data);
	return (0);
}

void	free_itmes(t_free *allocation)
{
	t_free	*tmp;

	while (allocation != NULL)
	{
		tmp = allocation->next;
		free(allocation->value);
		free(allocation->table);
		free(allocation);
		allocation = tmp;
	}
}

void	free_data(t_data *data)
{
	t_data	*tmp_rdt;

	while (data != NULL)
	{
		tmp_rdt = data->next;
		free_two(data->arguments);
		free(data);
		data = tmp_rdt;
	}
}

void	add_data_arguments(t_data *node, char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	node->arguments = (char **)malloc(sizeof(char *) * (i + 1));
	node->arguments[i] = 0;
	i = 0;
	while (str[i])
	{
		node->arguments[i] = ft_strdup(str[i]);
		i++;
	}
}
