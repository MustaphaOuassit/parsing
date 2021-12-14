/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continue_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 02:03:48 by mouassit          #+#    #+#             */
/*   Updated: 2021/12/14 06:16:58 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	continue_dollar(t_init *var, int *i, int *len, t_envp *env_list)
{
	if (var->value[*i] == '$' && delimiter(var->value, i))
		convert_dollar(var, i, len, env_list);
	else
		continue_add(var, len, i);
}

char	*putex(int *len, char *value, int *i, t_envp *env_list)
{
	t_init	var;

	var.token_word = initialisation_token(len, env_list);
	var.value = value;
	while (*len <= (int)ft_strlen(var.token_word))
	{
		if (value[*i] == '\"')
			var.token_word = word_double_couts(i, len, &var, env_list);
		else if (var.value[*i] == '\'')
			var.token_word = word_single_couts(i, len, &var);
		else if (var.value[*i] == '>' || var.value[*i] == '<'
			|| var.value[*i] == '|')
		{
			*i = *i + 1;
			break ;
		}
		else
			continue_dollar(&var, i, len, env_list);
	}
	*i = *i - 1;
	return (var.token_word);
}

void	initial_ex(char **token, char **word, int *len, char **dlr)
{
	*token = NULL;
	*word = NULL;
	*len = 0;
	*dlr = NULL;
}

void	put_word(t_tokens **data, char **token_word, t_envp *env_list)
{
	char	*dollar;

	dollar = NULL;
	if (*token_word)
	{
		put_in_parcer(data, *token_word, 6, env_list);
		*token_word = NULL;
	}
}

void	insert_dividers(t_tokens **data, char *value, t_init *var, t_envp *env)
{
	char	*token;

	token = NULL;
	if (value[var->i] && check_dividers(value[var->i], var))
	{
		token = put_diveder(value, value[var->i], var, env);
		put_in_parcer(data, token, var->type, env);
		if (!value[var->i + 1])
			var->i = var->i + 1;
	}
}
