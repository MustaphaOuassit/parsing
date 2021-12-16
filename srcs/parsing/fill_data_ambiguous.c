/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data_ambiguous.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 01:49:06 by mouassit          #+#    #+#             */
/*   Updated: 2021/12/16 22:20:47 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	fill_data_ambiguous(t_ambiguous **head, char *value, t_envp *env_list)
{
	char		*tmp;
	t_ambiguous	*new_node;
	t_ambiguous	*line;

	new_node = malloc(sizeof(t_ambiguous));
	tmp = ft_strdup(value);
	free_in_parcer(&env_list->allocation, tmp, NULL);
	free_in_parcer(&env_list->allocation, new_node, NULL);
	line = *head;
	new_node->value = tmp;
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

char	*put_diveder(char *data, int value, t_init *var, t_envp *env_list)
{
	char	*token;

	token = (char *)malloc(sizeof(char) * (2));
	free_in_parcer(&env_list->allocation, token, NULL);
	if ((value == '>' && data[var->i + 1] && data[var->i + 1] == '>'))
	{
		token = ft_strdup(">>");
		free_in_parcer(&env_list->allocation, token, NULL);
		var->type = 3;
		var->i = var->i + 1;
	}
	else if ((value == '<' && data[var->i + 1] && data[var->i + 1] == '<'))
	{
		token = ft_strdup("<<");
		free_in_parcer(&env_list->allocation, token, NULL);
		var->type = 5;
		var->i = var->i + 1;
	}
	else
	{
		token[0] = value;
		token[1] = '\0';
	}
	return (token);
}

int	check_dollar(char *value, int start)
{
	int	len;

	len = 0;
	while (value[start])
	{
		if (value[start] == ' ' || value[start] == '\"' || value[start] == '\''
			|| value[start] == '$' || value[start] == '>' || value[start] == '|'
			|| value[start] == '<' || (value[start] != '_'
				&& !ft_isalpha(value[start]) && !ft_isdigit(value[start])))
			break ;
		len++;
		start++;
	}
	return (len);
}

char	*dollar_allocation(char *value, int *len, t_envp *env_list)
{
	char	*dollar;

	dollar = NULL;
	if (env_list->type == 5)
	{
		dollar = (char *)malloc(sizeof(char) * ((int)ft_strlen(value) + 2));
		free_in_parcer(&env_list->allocation, dollar, NULL);
		*len = (int)ft_strlen(value) + 1;
		dollar[(int)ft_strlen(value) + 1] = '\0';
	}
	else
	{
		dollar = (char *)malloc(sizeof(char) * ((int)ft_strlen(value) + 3));
		free_in_parcer(&env_list->allocation, dollar, NULL);
		*len = (int)ft_strlen(value) + 2;
		dollar[(int)ft_strlen(value) + 2] = '\0';
	}
	return (dollar);
}

char	*fill_dollar_two(char *dollar, char *value, int len, t_envp *env_list)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < len)
	{
		if (i == 0)
			dollar[i] = '$';
		else if (i == (int)ft_strlen(dollar) - 1 && env_list->type != 5)
			dollar[i] = '?';
		else
		{
			dollar[i] = value[j];
			j++;
		}
		i++;
	}
	return (dollar);
}
