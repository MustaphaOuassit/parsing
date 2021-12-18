/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 10:26:07 by mouassit          #+#    #+#             */
/*   Updated: 2021/12/18 13:17:08 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	end_pipe(char *cmd, int end)
{
	char	*str;

	str = "minishell: syntax error near unexpected token `|'\n";
	if (cmd[end] == '|')
	{
		write(1, str, 51);
		return (1);
	}
	return (0);
}

int	check_pipe(char *cmd, int start)
{
	t_init	var;

	var.end = end_str(cmd);
	var.i = start;
	if (first_pipe(cmd, start))
		return (258);
	while (cmd[var.i])
	{
		if (cmd[var.i] == '\"')
		{
			if (multi_couts(&var.i, cmd, '\"'))
				return (1);
		}
		if (cmd[var.i] == '\'')
		{
			if (multi_couts(&var.i, cmd, '\''))
				return (1);
		}
		if (middle_pipe(cmd, &var.i))
			return (258);
		var.i++;
	}
	if (end_pipe(cmd, var.end))
		return (258);
	return (0);
}

int	continue_error(t_list *head, int error, t_envp *env_list, t_data **data)
{
	if (error != -1)
		error = check_tokens(head, error, env_list, data);
	return (error);
}

int	parsing(char *cmd, t_envp *env_list, t_data **data)
{
	t_init	var;

	initialisation_parsing(&var, cmd, env_list);
	if (var.error)
	{
		free(cmd);
		env_list->exit_status = var.error;
		return (var.error);
	}
	while (var.start < (int)ft_strlen(cmd))
	{
		if (cmd[var.start] != ' ')
		{
			var.token = get_token(cmd, &var.start, env_list);
			if (var.start == -1)
			{
				var.error = 1;
				break ;
			}
			list_tokens(&var.head, var.token, env_list);
		}
		var.start++;
	}
	parsing_errors(&var, env_list, data, cmd);
	return (var.error);
}
