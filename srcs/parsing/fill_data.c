/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 16:25:08 by mouassit          #+#    #+#             */
/*   Updated: 2021/12/20 11:23:37 by mouassit         ###   ########.fr       */
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

void	free_items(t_free **allocation)
{
	t_free	*tmp;

	while (*allocation != NULL)
	{
		tmp = (*allocation)->next;
		free((*allocation)->value);
		free((*allocation)->table);
		free((*allocation));
		(*allocation) = tmp;
	}
	*allocation = NULL;
}

void	free_data(t_data **data)
{
	t_data			*tmp_data;
	t_redirection	*tmp_rdt;

	while (*data != NULL)
	{
		tmp_data = (*data)->next;
		while ((*data)->redirection)
		{
			tmp_rdt = (*data)->redirection->next;
			free((*data)->redirection->file_name);
			free((*data)->redirection);
			(*data)->redirection = tmp_rdt;
		}
		if ((*data)->arguments)
			free_two((*data)->arguments);
		free((*data));
		(*data) = tmp_data;
	}
	(*data) = NULL;
}

void	add_data_arguments(t_data *node, char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (i)
	{
		node->arguments = (char **)malloc(sizeof(char *) * (i + 1));
		node->arguments[i] = 0;
		i = 0;
		while (str[i])
		{
			node->arguments[i] = ft_strdup(str[i]);
			i++;
		}
	}
}

void	initialisation_parsing(t_init *var, char *cmd, t_envp *env_list)
{
	var->head = NULL;
	var->start = skip_spaces(cmd);
	var->token = NULL;
	env_list->allocation = NULL;
	var->error = check_pipe(cmd, var->start);
}
