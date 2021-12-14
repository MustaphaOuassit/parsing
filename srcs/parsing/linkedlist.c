/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 13:53:03 by mouassit          #+#    #+#             */
/*   Updated: 2021/12/14 02:02:54 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../includes/minishell.h"

int		allocation_envp(t_envp *data)
{
	int	len;

	len = 0;
	while (data != NULL)
	{
		len++;
		data = data->next;
	}
	return(len);
}

void	initialisation_envp(t_tokens **data, t_init *var, t_envp *env_list)
{
	*data = NULL;
	var->type = 0;
	var->len = 0;
	var->redirection = 0;
	env_list->type = 0;
	env_list->ambiguous = NULL;
}

void	check_type(t_envp *env_list, int type)
{
	if(env_list->type != 7)
		env_list->type = type;
	if(type == 5)
		env_list->type = type;
	if(type == 1)
		env_list->type = 0;
}

int    check_tokens(t_list *head, int error,t_envp *env_list, t_data **dt)
{
	t_init var;
	t_tokens *data;
	
	var.j = 0;
	initialisation_envp(&data,&var,env_list);
	initialisation_init(&var.token,&var.token_word,&var.len_dollar,&var.dollar);
    while (head != NULL)
    {
		initialisation(&var.j,&var.len,&var.token,&var.token_word);
		while (var.j <= (int)ft_strlen(head->value))
		{
			check_type(env_list,var.type);
			var.len = len_word(head->value,var.j,env_list);
			if(var.len)
				var.token_word = put_data_token(&var.len, head->value,&var.j,env_list);
			put_word(&data,&var.token_word,env_list);
			var.i = var.j;
			insert_dividers(&data,head->value,&var,env_list);
			var.j = var.i;
			var.j++;
		}
        head = head->next;
    }
	error = fill_data(data,dt,env_list);
	return(error);
}
