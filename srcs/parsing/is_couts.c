/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_couts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 03:04:09 by mouassit          #+#    #+#             */
/*   Updated: 2021/12/16 22:00:09 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_couts_hrd(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (value[i] == '\'' || value[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

void	file_skip(char *value, int *i)
{
	while (value[*i])
	{
		if (value[*i] == '?')
			break ;
		*i = *i + 1;
	}
}

void	initialisation_values(t_init *vr, char *value, t_envp *env_list)
{
	vr->i = 0;
	vr->len = get_len(value);
	vr->tmp = vr->len;
	vr->file_name = (char *)malloc(sizeof(char) * (vr->len + 1));
	free_in_parcer(&env_list->allocation, vr->file_name, NULL);
	vr->file_name[vr->len] = 0;
	vr->len = 0;
}

char	*skip_dollar(char *value, t_init *var, t_envp *env_list)
{
	t_init	vr;

	initialisation_values(&vr, value, env_list);
	while (vr.len < vr.tmp)
	{
		if (value[vr.i] == '\"')
			file_double(value, &vr.i, &vr.len, vr.file_name);
		else if (value[vr.i] == '\'')
			file_single(value, &vr.i, &vr.len, vr.file_name);
		else if (value[vr.i] == '$' && delimiter(value, &vr.i))
			file_skip(value, &vr.i);
		else
		{
			if (value[vr.i] == ' ')
			{
				var->error = -1;
				break ;
			}
			vr.file_name[vr.len] = value[vr.i];
			vr.len++;
		}
		vr.i++;
	}
	return (vr.file_name);
}

void	initialisation_file(t_init *var, char *value, t_envp *env_list)
{
	var->i = 0;
	var->check = 0;
	var->len = len_file_name(value);
	var->tmp = var->len;
	var->file_name = (char *)malloc(sizeof(char) * (var->len + 1));
	free_in_parcer(&env_list->allocation, var->file_name, NULL);
	var->file_name[var->len] = '\0';
	var->len = 0;
}
