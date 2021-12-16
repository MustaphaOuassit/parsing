/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 16:09:13 by mouassit          #+#    #+#             */
/*   Updated: 2021/12/16 23:41:55 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	char *str;
	int i;
	t_data *data;
    t_envp *env_list;
	t_free *tmp;
	t_data *tmp_rdt;
	int j;
	int	len;
	int error;
	

	i = 0;
	j = 0;

	error = 0;
	data = NULL;
	tmp = NULL;

	while(envp[i])
	{
		add_to_env(&env_list, fill_envp(envp[i])); 
		i++;
	} 
	if (argc != 1 && !argv[0]) 
        return(-1);
	env_list->exit_status = 0;
	while(1)
	{
		len = 0;
		str = readline("-> minishell ");
		add_history(str);
		data = NULL;
		parsing(str,&error,env_list,&data);
		if(!error)
		{
			env_list->exit_status = error;
		}
		else
			env_list->exit_status = error;


			
		while (env_list->allocation != NULL)
		{
			tmp = env_list->allocation->next;
			free(env_list->allocation->value);
			free(env_list->allocation->table);
			free(env_list->allocation);
			env_list->allocation = tmp;
		}
		while (data != NULL)
		{
			tmp_rdt = data->next;
			free_two(data->arguments);
			free(data);
			data = tmp_rdt;
		}
		free(str);
	// if (1 && is_builtin("export"))
	// {
	// 	printf("%s\n", data->arguments[0]);
	// 	ft_builtins(data, &env_list);
	// }
	// else
	// 	exec_cmd(data, envp);
	}
}