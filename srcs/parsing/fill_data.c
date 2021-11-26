/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 16:25:08 by mouassit          #+#    #+#             */
/*   Updated: 2021/11/26 16:25:11 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../includes/minishell.h"

int	redirection_token(t_redirection	**head,int type, char *file_name)
{
	t_redirection *new_node = malloc(sizeof(t_redirection));
	t_redirection *line;

	line = *head;
	new_node->file_name = file_name;
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

int	args_token(t_args **head, char *args)
{
	t_args *new_node = malloc(sizeof(t_redirection));
	t_args *line;

	line = *head;
	new_node->arguments = args;
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

int     fill_data(t_tokens *tokens)
{
    t_data *data;
    t_args *args;

    data = NULL;
    args = NULL;
    data->redirection = NULL;
    data->arguments = NULL;
    while (tokens != NULL)
    {
        if( tokens->type <= 5 && tokens->type >= 2)
        {
            redirection_token(&data->redirection, tokens->value,tokens->type);
        }
        else
            args_token(&args,tokens->value);
        tokens = tokens->next;
    }
    
    return(0);
}