/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 03:08:42 by mouassit          #+#    #+#             */
/*   Updated: 2021/12/17 00:12:34 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	error_value(t_init *var, char *value, t_envp *env_list)
{
	if (!ft_strcmp(value, "|"))
	{
		write(1, "minishell: syntax error near unexpected token `|'\n", 50);
		return (1);
	}
	redirection_token(&var->rdt, var->type, value, env_list);
	return (0);
}

void	fill_filter(t_init *var, char *value, t_envp *env_list)
{
	int		j;
	char	**filter;

	j = 0;
	filter = filter_args(value, env_list);
	if (filter)
	{
		while (filter[j])
		{
			args_token(&var->args, filter[j], env_list);
			var->len = var->len + 1;
			j++;
		}
	}
}

void	initialisation_data(t_init *var)
{
	var->rdt = NULL;
	var->args = NULL;
	var->check = 0;
	var->len = 0;
	var->error = 0;
	var->pipe = 0;
	var->nb_heredoc = 0;
	var->arguments = NULL;
}

int	file_error(t_init *var, t_tokens *tokens, t_envp *env_list)
{
	var->pipe = 0;
	if (tokens->type <= 5 && tokens->type >= 2)
	{
		if (redirection_value(tokens, env_list, var))
			return (1);
		var->type = tokens->type;
	}
	else if (var->check == 1)
	{
		var->check = 0;
		tokens->value = file_dollar(tokens, var, env_list);
		if (error_value(var, tokens->value, env_list))
			return (1);
	}
	else
		fill_filter(var, tokens->value, env_list);
	return (0);
}

void	prep_data(t_init *var, t_envp *env_list, t_data **data)
{
	int i;

	i = 0;
	var->arguments = put_data(var, env_list);
	all_data(data, var, env_list);
	var->rdt = NULL;
	var->args = NULL;
}
