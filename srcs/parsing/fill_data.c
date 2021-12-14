/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 16:25:08 by mouassit          #+#    #+#             */
/*   Updated: 2021/12/14 05:24:52 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	fill_data(t_tokens *tokens, t_data **data, t_envp *env_list)
{
	t_init	var;

	initialisation_data(&var);
	while (tokens != NULL)
	{
		if (tokens->type == 1 && var.check != 1)
		{
			var.pipe = 1;
			prep_data(&var, env_list, data);
			tokens = tokens->next;
		}
		else
		{
			if (file_error(&var, tokens, env_list))
				return (258);
			tokens = tokens->next;
		}
	}
	if (var.pipe == 0)
		prep_data(&var, env_list, data);
	return (0);
}
