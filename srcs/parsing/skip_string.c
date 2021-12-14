/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 01:57:29 by mouassit          #+#    #+#             */
/*   Updated: 2021/12/14 01:57:30 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../includes/minishell.h"

void	skip_string(char *value, int *start,t_init *var,t_envp *env_list)
{
	while (value[*start])
	{
		if(value[*start] == '\"')
			break;
		if(value[*start] == '$' && delimiter(value,start))
			take_dollar(value, start,var,env_list);
		var->i++;
		*start = *start + 1;
	}
}

int		len_word(char *value, int start, t_envp *env_list)
{
	t_init var;

	initialisation_var(&var.i,&var.close,&var.dollar,&var.len_dollar);
	while (start < (int)ft_strlen(value))
	{
		if(value[start] == '|' || value[start] == '>' ||
		value[start] == '<')
			break;
		if (value[start] == '\"')
		{
			start++;
			skip_string(value,&start,&var,env_list);
			var.i = var.i + 2;
		}
		else
			single_couts(value,&start,&var.i,env_list);
		start++;
	}
	return(var.i);
}

char	*initialisation_dollar(int *len_dollar, int *i, t_envp *env_list)
{
	char *dollar;

	dollar = (char *)malloc(sizeof(char) * (*len_dollar + 1));
	free_in_parcer(&env_list->allocation,dollar,NULL);
	dollar[*len_dollar] = '\0';
	*len_dollar = 0;
	*i = *i + 1;
	return(dollar);
}

char *fill_convert_two(char *dollar, t_envp *env_list, int *len, char *token_word)
{
	int j;

	j = 0;
	if(dollar)
	{
		dollar = ft_strdup(get_env_couts(dollar,env_list));
		free_in_parcer(&env_list->allocation,dollar,NULL);
		while (dollar[j])
		{
			token_word[*len] = dollar[j];
			*len = *len + 1;
			j++;
		}
		dollar = NULL;
	}
	return(token_word);
}

char *dollar_value(t_init *vr,int *len, int *i,t_envp *env_list)
{
	t_init var;
	int	tmp;

	tmp = 0;
	if(vr->value[*i + 1] == '?')
	{
		var.dollar = "?";
		*i = *i + 2;
	}
	else
	{
		var.len_dollar = check_dollar(vr->value,*i + 1);
		tmp = var.len_dollar;
		var.dollar = initialisation_dollar(&var.len_dollar,i,env_list);
		while (var.len_dollar < tmp)
		{
			var.dollar[var.len_dollar] = vr->value[*i];
			var.len_dollar = var.len_dollar + 1;
			*i = *i + 1;
		}
	}
	vr->token_word = fill_convert_two(var.dollar,env_list,len,vr->token_word);

	return(vr->token_word);
}