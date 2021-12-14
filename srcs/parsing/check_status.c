/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 01:52:07 by mouassit          #+#    #+#             */
/*   Updated: 2021/12/14 01:52:08 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

char	*check_status(int *start)
{
	t_init vr;

	vr.dollar = "?";
	*start = *start + 2;
	return (vr.dollar);
}

void	take_dollar(char *value, int *start, t_init *var,t_envp *env_list)
{
	t_init vr;

	vr.dollar = NULL;
	vr.tmp = 0;
	if(value[*start + 1] == '?')
		vr.dollar = check_status(start);
	else
	{
		var->len_dollar = check_dollar(value,*start + 1);
		vr.dollar = (char *)malloc(sizeof(char) * (var->len_dollar + 1));
		free_in_parcer(&env_list->allocation,vr.dollar,NULL);
		vr.dollar[var->len_dollar] = '\0';
		vr.tmp = var->len_dollar;
		var->len_dollar = 0;
		*start = *start + 1;
		while (var->len_dollar < vr.tmp)
		{
			vr.dollar[var->len_dollar] = value[*start];
			var->len_dollar = var->len_dollar + 1;
			*start = *start + 1;
		}
	}
	continue_len(vr.dollar,var,start,env_list);
}

void	take_couts(int *start, char *value, int *i)
{
	*start = *start + 1;
	while (value[*start])
	{
		if(value[*start] == '\'')
			break;
		*i = *i + 1;
		*start = *start + 1;
	}
}

void	initialisation_var(int *i, int *close, char **dollar, int *len_dollar)
{
	*i = 0;
	*close = 0;
	*dollar = NULL;
	*len_dollar = 0;
}

int		is_space(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if(value[i] == ' ')
			return(1);
		i++;
	}
	
	return(0);
}