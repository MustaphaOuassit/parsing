/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 02:09:03 by mouassit          #+#    #+#             */
/*   Updated: 2021/12/14 06:35:00 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redirection_token(t_redirection	**head, int type, char *file, t_envp *env)
{
	t_redirection	*new_node;
	t_redirection	*line;

	new_node = malloc(sizeof(t_redirection));
	free_in_parcer(&env->allocation, new_node, NULL);
	line = *head;
	new_node->file_name = file;
	new_node->type = type;
	new_node->next = NULL;
	if (*head == NULL)
	{
		*head = new_node;
		return (0);
	}
	while (line->next != NULL)
	{
		line = line->next;
	}
	line->next = new_node;
	return (0);
}

int	args_token(t_args	**head, char *args, t_envp *env_list)
{
	t_args	*new_node;
	t_args	*line;

	new_node = malloc(sizeof(t_redirection));
	free_in_parcer(&env_list->allocation, new_node, NULL);
	line = *head;
	new_node->arguments = args;
	new_node->next = NULL;
	if (*head == NULL)
	{
		*head = new_node;
		return (0);
	}
	while (line->next != NULL)
	{
		line = line->next;
	}
	line->next = new_node;
	return (0);
}

void	initialisation_convert(t_init *var, char *value, t_envp *env_list)
{
	var->i = 0;
	var->j = 0;
	var->check_error = (char *)malloc(sizeof(char)
			* ((int)ft_strlen(value) + 3));
	free_in_parcer(&env_list->allocation, var->check_error, NULL);
	var->check_error[(int)ft_strlen(value) + 2] = '\0';
}

char	*convert(char *value, t_envp *env_list)
{
	t_init	var;

	initialisation_convert(&var, value, env_list);
	while (var.i < (int)ft_strlen(value) + 2)
	{
		if (var.i == 0)
		{
			var.check_error[var.i] = '`';
			var.i++;
		}
		else if (var.i == (int)ft_strlen(value) + 1)
		{
			var.check_error[var.i] = '\'';
			var.i++;
		}
		else
		{
			var.check_error[var.i] = value[var.j];
			var.j++;
			var.i++;
		}
	}
	return (var.check_error);
}

void	print_error_rdt(char *value, t_envp *env_list)
{
	char	*error;
	char	*error_rdt;

	error = "minishell: syntax error near unexpected token ";
	error_rdt = NULL;
	error_rdt = convert(value, env_list);
	error = ft_strjoin(error, error_rdt);
	free_in_parcer(&env_list->allocation, error, NULL);
	write(1, error, ft_strlen(error));
	write(1, "\n", 1);
}
