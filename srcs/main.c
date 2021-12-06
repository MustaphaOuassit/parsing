/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayafdel <ayafdel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 16:09:13 by mouassit          #+#    #+#             */
/*   Updated: 2021/11/20 11:01:15 by ayafdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	char *str;
	int i;
	t_data *data;
    t_envp *env_list;
	int j;
	int error;

	i = 0;
	j = 0;
	error = 0;
	data = NULL;

	while(envp[i])
	{
		add_to_env(&env_list, fill_envp(envp[i])); 
		i++;
	} 
	if (argc != 1 && !argv[0]) 
        return(-1);
	while(1)
	{
		str = readline("-> minishell ");
		add_history(str);
		env_list->exit_status = 0;
		parsing(str,&error,env_list,&data);
		if(!error)
		{
			while (data != NULL)
			{
				j = 0;
				printf("-------------------\n");
				printf("\n");
				printf("Arguments :\n");
				while (data->arguments[j])
				{
				printf("%s\n",data->arguments[j]);
				j++;
			}
				printf("\n");
				printf("Redirections :\n");
			while (data->redirection != NULL)
			{
				printf("%s %d\n",data->redirection->file_name,data->redirection->type);
				data->redirection = data->redirection->next;
			}
				printf("\n");
				printf("Heredoc :\n");
				printf("%d\n",data->nb_heredoc);
				data = data->next;
			}
		}
		else
			env_list->exit_status = error;

	// if (1 && is_builtin("export"))
	// {
	// 	printf("%s\n", data->arguments[0]);
	// 	ft_builtins(data, &env_list);
	// }
	// else
	// 	exec_cmd(data, envp);
	}
}