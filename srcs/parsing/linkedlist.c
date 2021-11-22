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

int		check_dollar(char *value, int start)
{
	int len;

	len = 0;
	while (value[start])
	{
		if (value[start] == ' ' || value[start] == '\"')
			break;
		len++;
		start++;
	}
	return(len);
}

char	*get_env(char *value)
{
	value[0] = 'd';
	char *str = ft_strdup("ls -la");
	return(str);
}

int		len_word(char *value, int start)
{
	int i;
	int close;
	char *dollar;
	int len_dollar;

	i = 0;
	close = 0;
	dollar = NULL;
	len_dollar = 0;
	while (value[start])
	{
		if(value[start] == '|' || value[start] == '>' || value[start] == '<' || value[start] == '$')
			break;
		if (value[start] == '\"')
		{
			start++;
			// close = check_close(value, start);
			// if(!close)
			// 	return(-1);
			while (value[start])
			{
				if(value[start] == '\"')
					break;
				if(value[start] == '$')
				{
					len_dollar = check_dollar(value,start + 1);
					dollar = (char *)malloc(sizeof(char) * (len_dollar + 1));
					dollar[len_dollar] = '\0';
					len_dollar = 0;
					start++;
					while (dollar[len_dollar])
					{
						dollar[len_dollar] = value[start];
						len_dollar++;
						start++;
					}
					start--;
					if(dollar)
					{
						i = i + (int)ft_strlen(get_env(dollar));
						i--;
					}
				}
				i++;
				start++;
			}
		}
		else if (value[start] == '\'')
		{
			start++;
			// close = check_close(value, start);
			// if(!close)
			// 	return(-1);
			while (value[start])
			{
				if(value[start] == '\'')
					break;
				i++;
				start++;
			}
		}
		else
			i++;
		start++;
	}
	return(i);
}

int    check_tokens(t_list *head, int error)
{
	int i;
	int type;
	char *token;
	char *token_word;
	int len;
	int check;

	i = 0;
	check = 0;
	token = NULL;
	token_word = NULL;
    while (head != NULL)
    {
		i = 0;
		len = 0;
		token = NULL;
		token_word = NULL;
		while (i <= (int)ft_strlen(head->value))
		{
			len = len_word(head->value,i);
			if(len)
			{
				token_word = (char *)malloc(sizeof(char) * (len + 1));
				token_word[len] = '\0';
				len = 0;
				while (len <= (int)ft_strlen(token_word))
				{
					if(head->value[i] == '\"')
					{
						i++;
						while (i <= (int)ft_strlen(head->value))
						{
							if(head->value[i] == '\"')
								break;
							token_word[len] = head->value[i];
							len++;
							i++;
						}
					}
					else if(head->value[i] == '>')
						break;
					else
					{
						token_word[len] = head->value[i];
						i++;
						len++;
					}
				}
				i--;
			}
			if(head->value[i] && check_dividers(head->value[i],&type))
			{
				if(token_word)
					put_in_parcer(token_word,10);
				token = put_diveder(head->value,head->value[i],&i,&type);
				put_in_parcer(token,type);
			}
			else if(token_word)
				put_in_parcer(token_word,10);
			i++;
		}
        head = head->next;
    }
    error = 2;
	return(error);
}