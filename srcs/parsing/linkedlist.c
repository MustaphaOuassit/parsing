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

char	*put_diveder(char *data, int value, int *i,int *type)
{
	char *token;
	
	token = (char *)malloc(sizeof(char) * (2));
	if((value == '>' && data[*i + 1] && data[*i + 1] == '>'))
	{
		token = ft_strdup(">>");
		*type = 4;
		*i = *i + 1;
	}
	else if((value == '<' && data[*i + 1] && data[*i + 1] == '<'))
	{
		token = ft_strdup("<<");
		*type = 5;
		*i = *i + 1;
	}
	else
	{
		token[0] = value;
		token[1] = '\0';
	}
	return(token);
}

int    check_tokens(t_list *head, int error)
{
	int i;

	i = 0;
    while (head != NULL)
    {
		int type;
		char *token;

		i = 0;

		while (head->value[i])
		{

			if(check_dividers(head->value[i],&type))
			{
				token = put_diveder(head->value,head->value[i],&i,&type);
				put_in_parcer(token,type);
			}
			i++;
		}
        head = head->next;
    }
    error = 2;
	return(error);
}