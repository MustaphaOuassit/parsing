/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 13:53:03 by mouassit          #+#    #+#             */
/*   Updated: 2021/11/21 13:53:05 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../includes/minishell.h"

int    list_tokens(t_list **head, char *data)
{
    t_list *new_node = malloc(sizeof(t_list));
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

int    check_tokens(t_list *head, int error)
{
    while (head != NULL)
    {
        printf("%s\n",head->value);
        head = head->next;
    }
    error = 2;
	return(error);
}