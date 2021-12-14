/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 02:00:41 by mouassit          #+#    #+#             */
/*   Updated: 2021/12/14 02:00:42 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../includes/minishell.h"

void	add_dollar(int *i, int *len,t_init *var)
{
	if(var->value[*i - 1] == '\"')
	{
		var->token_word[*len] = var->value[*i - 1];
		*len = *len + 1;
	}
}

void	right_couts(t_init *var, int *len, int *i)
{
	var->token_word[*len] = var->value[*i - 1];
	*len = *len + 1;
}

void	add_double_couts(t_init *var, int *len, int *i)
{
	if(var->value[*i - 1] == '\"')
	{
		var->token_word[*len] = var->value[*i];
		*len = *len + 1;
	}
	var->token_word[*len] = var->value[*i];
	*len = *len + 1;
	*i = *i + 1;
}

char	*word_double_couts(int *i, int *len, t_init *var,t_envp *env_list)
{
	*i = *i + 1;
	while (*i <= (int)ft_strlen(var->value))
	{
		if(var->value[*i] == '\"')
		{
			add_double_couts(var,len,i);
			break;
		}
		if(var->value[*i] == '$' && delimiter(var->value,i))
		{
			add_dollar(i,len,var);
			var->token_word = dollar_value(var,len,i,env_list);
		}
		else
		{
			if(var->value[*i - 1] == '\"')
				right_couts(var,len,i);
			var->token_word[*len] = var->value[*i];
			*len = *len + 1;
			*i = *i + 1;
		}
	}								
	return(var->token_word);
}

char *word_single_couts(int *i,int *len,t_init *var)
{
	*i = *i + 1;
	while (*i <= (int)ft_strlen(var->value))
	{
		if(var->value[*i] == '\'')
		{
			if(var->value[*i - 1] == '\'')
			{
			var->token_word[*len] = var->value[*i];
			*len = *len + 1;
		}
		var->token_word[*len] = var->value[*i];
		*len = *len + 1;
		*i = *i + 1;
			break;
		}
		if(var->value[*i - 1] == '\'')
				right_couts(var,len,i);
		var->token_word[*len] = var->value[*i];
		*len = *len + 1;
		*i = *i + 1;
	}
	return(var->token_word);
}