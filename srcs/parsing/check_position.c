/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_position.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 03:00:47 by mouassit          #+#    #+#             */
/*   Updated: 2021/12/17 02:15:24 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_position(t_init *var, char *value, char **filter, int *tmp)
{
	if (value[*tmp] == '\"')
		file_args_double(var, value, filter, tmp);
	else if (value[*tmp] == '\'')
		file_args_single(var, value, filter, tmp);
	else if (value[*tmp] != ' ')
		file_args_dollar(tmp, var, value, filter);
	else
		*tmp = *tmp + 1;
}

char	**filter_args(char *value, t_envp *env_list)
{
	t_init	var;

	initialisation_args(&var, value, env_list);
	if (var.len)
	{
		var.filter = declar(&var.len, &var.j, &var.tmp, env_list);
		while (var.j <= (int)ft_strlen(value))
		{
			var.filter[var.start] = initial(&var, env_list, var.filter, value);
			while (var.i < var.check)
				check_position(&var, value, var.filter, &var.tmp);
			var.start++;
			var.j++;
		}
		var.filter[var.len] = 0;
	}
	return (var.filter);
}

int	all_data(t_data	**head, t_init *var, t_envp *env_list)
{
	t_data	*new_node;
	t_data	*line;

	new_node = malloc(sizeof(t_data));
	line = *head;
	add_data_arguments(new_node, var->arguments);
	new_node->redirection = var->rdt;
	new_node->nb_heredoc = env_list->nb_herdoc;
	new_node->next = NULL;
	if (*head == NULL)
	{
		*head = new_node;
		return (0);
	}
	while (line->next != NULL)
		line = line->next;
	line->next = new_node;
	return (0);
}

int	len_file_name(char *value)
{
	int	i;
	int	len;
	int	check;

	i = 0;
	len = 0;
	check = 0;
	while (value[i])
	{
		if (value[i] == '$' && delimiter(value, &i))
			check = 1;
		if (value[i] == '?' && check == 1)
		{
			len--;
			check = 0;
		}
		len++;
		i++;
	}
	return (len);
}

void	skip_content_value(char *value, int *i, int *len, int ele)
{
	*i = *i + 1;
	while (value[*i])
	{
		if (value[*i] == ele)
			break ;
		*i = *i + 1;
		*len = *len + 1;
	}
}
