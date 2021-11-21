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

int	check_dividers(int value, int *type)
{
	if(value == '|' || value == '>' || value == '<')
	{
		if (value == '|')
			*type = 1;
		if(value == '>')
			*type = 2;
		if(value == '<')
			*type = 3;
		return(1);
		
	}
	return(0);
}

void	put_in_parcer(char *value, int type)
{
	printf("V : %s T : %d\n",value,type);
}

int    check_tokens(t_list *head, int error)
{
	int i;

	i = 0;
    while (head != NULL)
    {
		int type;
		char *dividers;

		i = 0;
		dividers = (char *)malloc(sizeof(char) * (2));
		while (head->value[i])
		{
			if(check_dividers(head->value[i],&type))
			{
				if((head->value[i] == '>' && head->value[i + 1] && head->value[i + 1] == '>'))
				{
					dividers = ft_strdup(">>");
					type = 4;
					i++;
				}
				else if((head->value[i] == '<' && head->value[i + 1] && head->value[i + 1] == '<'))
				{
					dividers = ft_strdup("<<");
					type = 5;
					i++;
				}
				else
				{
					dividers[0] = head->value[i];
					dividers[1] = '\0';
				}
				put_in_parcer(dividers,type);
			}
			i++;
		}
		
        head = head->next;
    }
    error = 2;
	return(error);
}