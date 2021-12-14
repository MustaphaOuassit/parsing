/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 01:46:01 by mouassit          #+#    #+#             */
/*   Updated: 2021/12/14 01:46:19 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

void	free_two(char **table)
{
	int	i;

	i = 0;
	while (table[i])
	{
		free(table[i]);
		table[i] = NULL;
		i++;
	}
	free(table);
	table = NULL;
}

int    list_tokens(t_list **head, char *data, t_envp *env_list)
{
    t_list *new_node = malloc(sizeof(t_list));
	free_in_parcer(&env_list->allocation,new_node,NULL);
	t_list *line;

	line = *head;
	new_node->value = data;
	new_node->next = NULL;
	if(*head == NULL)
	{
		*head = new_node;
		return(0);
	}
	while (line->next != NULL)
		line = line->next;
	line->next = new_node;
return(0);   
}

int	check_dividers(int value, t_init *var)
{
	if(value == '|' || value == '>' || value == '<')
	{
		if (value == '|')
			var->type = 1;
		if(value == '>')
			var->type = 2;
		if(value == '<')
			var->type = 4;
		return(1);
		
	}
	return(0);
}

int	put_in_parcer(t_tokens **head, char *value, int type,t_envp *env_list)
{
	char *tmp;

	tmp = ft_strdup(value);
	free_in_parcer(&env_list->allocation,tmp,NULL);
	t_tokens *new_node = malloc(sizeof(t_tokens));
	free_in_parcer(&env_list->allocation,new_node,NULL);
	t_tokens *line;
	 line = *head;
	new_node->value = tmp;
	new_node->type = type;
	new_node->next = NULL;
	if(*head == NULL)
	{
		*head = new_node;
		return(0);
	}

	while (line->next != NULL)
	{	
		line = line->next;
	}
	line->next = new_node;
return(0);
}

int	free_in_parcer(t_free **head, void *value, char	**table)
{
	t_free *new_node = malloc(sizeof(t_free));
	t_free *line;
	line = *head;
	new_node->value = value;
	new_node->table = table;
	new_node->next = NULL;
	if(*head == NULL)
	{
		*head = new_node;
		return(0);
	}
	while (line->next != NULL)
	{	
		line = line->next;
	}
	line->next = new_node;
return(0);
}
