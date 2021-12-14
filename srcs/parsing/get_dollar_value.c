/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dollar_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 02:07:51 by mouassit          #+#    #+#             */
/*   Updated: 2021/12/14 02:07:52 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

char *get_dollar_value(char *value, int *i, t_envp *env_list)
{
	t_init vr;
	char *dollar;

	vr.tmp = *i;
	vr.i = 0;
	vr.len = allocation_expand(value,i);
	dollar = (char *)malloc(sizeof(char) * (vr.len + 1));
	free_in_parcer(&env_list->allocation,dollar,NULL);
	dollar[vr.len] = '\0';
	vr.tmp++;
	while (vr.i < vr.len)
	{
		dollar[vr.i] = value[vr.tmp];
		vr.tmp++;
		vr.i++;
	}
	return(dollar);
}

void	fill_data_dollar(char *value, int *i, char *data,t_envp *env_list)
{
	t_init var;
	char *env;

	var.i = *i;
	var.j = 0;
	var.dollar = get_dollar_value(value,i,env_list);
	env = ft_strdup(get_env_hrd(var.dollar,env_list));
	free_in_parcer(&env_list->allocation,env,NULL);
	while (env[var.j])
	{
		data[var.i] = env[var.j];
		var.i++;
		var.j++;
	}

}

void	initialisation_expand(t_init *var, char *value, t_envp *env_list)
{
	var->i = 0;
	var->j = 0;
	var->tmp = 0;
	var->exp = NULL;
	var->len = len_expand(value, env_list);
	var->dollar = (char *)malloc(sizeof(char) * (var->len + 1));
	free_in_parcer(&env_list->allocation,var->dollar,NULL);
	var->dollar[var->len] = '\0';
	var->env = NULL;
}

void	fill_expand(char *dollar, char *value, int *tmp, int i)
{
	dollar[*tmp] = value[i];
	*tmp = *tmp + 1;
}

char	*expand_value(char *value, t_envp *env_list)
{
	t_init var;

	initialisation_expand(&var,value,env_list);
	while (var.tmp < var.len)
	{
		if(value[var.i] == '$' && check_dlm(value[var.i + 1]))
		{
			var.exp = get_dollar_value(value,&var.i,env_list);
			var.env = ft_strdup(get_env_hrd(var.exp,env_list));
			free_in_parcer(&env_list->allocation,var.env,NULL);
			var.j = 0;
			while (var.env[var.j])
			{
				var.dollar[var.tmp] = var.env[var.j];
				var.j++;
				var.tmp++;
			}
			var.i--;
		}
		else
			fill_expand(var.dollar,value,&var.tmp,var.i);
		var.i++;
	}
	return(var.dollar);
}