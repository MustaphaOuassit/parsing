/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 02:02:19 by mouassit          #+#    #+#             */
/*   Updated: 2021/12/16 22:03:18 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	initialisation(int *i, int *len, char **token, char **token_word)
{
	*i = 0;
	*len = 0;
	*token = NULL;
	*token_word = NULL;
}

char	*initialisation_token(int *len, t_envp *env_list)
{
	char	*token_word;

	token_word = NULL;
	token_word = (char *)malloc(sizeof(char) * (*len + 1));
	free_in_parcer(&env_list->allocation, token_word, NULL);
	token_word[*len] = '\0';
	*len = 0;
	return (token_word);
}

void	fill_convert(char *value, t_envp *env_list, int *len, char *token_word)
{
	int	j;

	j = 0;
	if (value)
	{
		value = ft_strdup(get_env(value, env_list));
		free_in_parcer(&env_list->allocation, value, NULL);
		while (value[j])
		{
			token_word[*len] = value[j];
			*len = *len + 1;
			j++;
		}
		value = NULL;
	}
}

void	convert_dollar(t_init *vr, int *i, int *len, t_envp *env_list)
{
	t_init	var;
	int		j;
	int		tmp;

	j = 0;
	tmp = 0;
	if (vr->value[*i + 1] == '?')
	{
		var.dollar = "?";
		*i = *i + 2;
	}
	else
	{
		var.len_dollar = check_dollar(vr->value, *i + 1);
		tmp = var.len_dollar;
		var.dollar = initialisation_dollar(&var.len_dollar, i, env_list);
		while (var.len_dollar < tmp)
		{
			var.dollar[var.len_dollar] = vr->value[*i];
			var.len_dollar = var.len_dollar + 1;
			*i = *i + 1;
		}
	}
	fill_convert(var.dollar, env_list, len, vr->token_word);
}

void	continue_add(t_init *var, int *len, int *i)
{
	var->token_word[*len] = var->value[*i];
	*i = *i + 1;
	*len = *len + 1;
}
