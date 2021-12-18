/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 13:03:04 by mouassit          #+#    #+#             */
/*   Updated: 2021/12/18 13:20:44 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parsing_errors(t_init *var, t_envp *env_list, t_data **data, char *cmd)
{
	var->error = continue_error(var->head, var->error, env_list, data);
	free_itmes(env_list->allocation);
	free(cmd);
	if (var->error == 258)
		free_data(data);
	env_list->exit_status = var->error;
}
