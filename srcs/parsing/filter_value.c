/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 03:07:36 by mouassit          #+#    #+#             */
/*   Updated: 2021/12/16 23:50:15 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*filter_value(char *value, t_envp *env_list)
{
	char	*file_name;

	file_name = fill_herdoc(value, env_list);
	return (file_name);
}

char	*filter_file_dollar(char *value, t_init *var, t_envp *env_list)
{
	int		i;
	char	*file_name;
	int		check;

	i = 0;
	check = is_couts(value);
	if (check)
		file_name = skip_dollar(value, var, env_list);
	else
	{
		file_name = fill_file(value, env_list);
		if (file_name[0] == '$')
			var->error = 1;
		else if (is_space(file_name))
			var->error = -1;
		else
			file_name = skip_dollar(value, var, env_list);
	}
	return (file_name);
}

char	**put_data(t_init *var, t_envp *env_list)
{
	char	**arguments;
	int		t;

	arguments = NULL;
	arguments = (char **)malloc(sizeof(char *) * (var->len + 1));
	free_in_parcer(&env_list->allocation, NULL, arguments);
	t = 0;
	while (var->args != NULL)
	{
		arguments[t] = var->args->arguments;
		t++;
		var->args = var->args->next;
	}
	arguments[var->len] = 0;
	env_list->nb_herdoc = var->nb_heredoc;
	var->len = 0;
	var->nb_heredoc = 0;
	return (arguments);
}

int	redirection_value(t_tokens *tokens, t_envp *env_list, t_init *var)
{
	if (tokens->type == 5)
		var->nb_heredoc = var->nb_heredoc + 1;
	if (error_redirection(var->check, tokens, env_list))
		return (1);
	var->check = 1;
	return (0);
}

char	*file_dollar(t_tokens *tokens, t_init *var, t_envp *env_list)
{
	if (var->type != 5)
	{
		tokens->value = filter_file_dollar(tokens->value, var, env_list);
		if (var->error == 1)
			var->type = 7;
		if (var->error == -1)
		{
			var->type = 7;
			tokens->value = ft_strdup(env_list->ambiguous->value);
			free_in_parcer(&env_list->allocation, tokens->value, NULL);
			env_list->ambiguous = env_list->ambiguous->next;
		}
	}
	else
	{
		if (!is_couts_hrd(tokens->value))
			var->type = 8;
		tokens->value = filter_value(tokens->value, env_list);
	}
	return (tokens->value);
}
