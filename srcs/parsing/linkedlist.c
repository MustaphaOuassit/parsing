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
		if (value[start] == ' ' || value[start] == '\"' || value[start] == '$')
			break;
		len++;
		start++;
	}
	return(len);
}

int		check_dollar_word(char *value, int start)
{
	int len;

	len = 0;
	while (value[start])
	{
		if(value[start] == ' ' || value[start] == '\"' || value[start] == '\'' 
		|| value[start] == '|' || value[start] == '>' || value[start] == '<' 
		|| value[start] == '$')
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

void	take_dollar(char *value, int *start, int *len_dollar, int *i)
{
	char *dollar;

	dollar = NULL;
	*len_dollar = check_dollar(value,*start + 1);
	dollar = (char *)malloc(sizeof(char) * (*len_dollar + 1));
	dollar[*len_dollar] = '\0';
	*len_dollar = 0;
	*start = *start + 1;
	while (dollar[*len_dollar])
	{
		dollar[*len_dollar] = value[*start];
		*len_dollar = *len_dollar + 1;
		*start = *start + 1;
	}
	if(dollar)
	{
		*i = *i + (int)ft_strlen(get_env(dollar));
		*i = *i - 1;
		*start = *start - 1;
	}
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
	while (start < (int)ft_strlen(value))
	{
		if(value[start] == '|' || value[start] == '>' ||
		value[start] == '<' || value[start] == '$')
			break;
		if (value[start] == '\"')
		{
			start++;
			while (value[start])
			{
				if(value[start] == '\"')
					break;
				
				if(value[start] == '$')
					take_dollar(value, &start, &len_dollar,&i);
				i++;
				start++;
			}
		}
		else if (value[start] == '\'')
		{
			start++;
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

char	*word_double_couts(int *i,char *value, int *len,char *token_word)
{
	int len_dollar;
	char *dollar;
	int j;


	len_dollar = 0;
	dollar = NULL;
	*i = *i + 1;
	j = 0;
	while (*i <= (int)ft_strlen(value))
	{
		if(value[*i] == '\"')
		{
			*i = *i + 1;
			break;
		}
		if(value[*i] == '$')
		{
			len_dollar = check_dollar(value,*i + 1);
			dollar = (char *)malloc(sizeof(char) * (len_dollar + 1));
			dollar[len_dollar] = '\0';
			len_dollar = 0;
			*i = *i + 1;
			while (dollar[len_dollar])
			{
				dollar[len_dollar] = value[*i];
				len_dollar++;
				*i = *i + 1;
			}
			if(dollar)
			{
				dollar = ft_strdup(get_env(dollar));
				j = 0;
				while (dollar[j])
				{
					token_word[*len] = dollar[j];
					*len = *len + 1;
					j++;
				}
				dollar = NULL;
			}
		}
		else
		{
			token_word[*len] = value[*i];
			*len = *len + 1;
			*i = *i + 1;
		}
	}
	return(token_word);
}

char *word_single_couts(int *i,char *value, int *len,char *token_word)
{
	*i = *i + 1;
	while (*i <= (int)ft_strlen(value))
	{
		if(value[*i] == '\'')
		{
			*i = *i + 1;
			break;
		}
		token_word[*len] = value[*i];
		*len = *len + 1;
		*i = *i + 1;
	}
	return(token_word);
}

char *dollar_token(int *i,char *dollar,char *value)
{
	int len_dollar;
	int tmp;

	tmp = 0;
	len_dollar = check_dollar_word(value,*i + 1);
	dollar = (char *)malloc(sizeof(char) * (len_dollar + 1));
	dollar[len_dollar] = '\0';
	tmp = len_dollar;
	len_dollar = 0;
	*i = *i + 1;
	while (value[*i])
	{
		if(value[*i] == ' ' || value[*i] == '\"' || value[*i] == '\'' 
		|| value[*i] == '|' || value[*i] == '>' || value[*i] == '<' 
		|| value[*i] == '$')
		{
			*i = *i - 1;
			break;
		}
		if(len_dollar <= tmp)
			dollar[len_dollar] = value[*i];
			len_dollar++;
			*i = *i + 1;
	}
	return(dollar);
}

void	initialisation(int *i, int *len, char **token, char **token_word)
{
	*i = 0;
	*len = 0;
	*token = NULL;
	*token_word = NULL;
}

void	insert_dividers(char *value,int *i,int *type)
{
	char *token;

	token = NULL;
	if(value[*i] && check_dividers(value[*i],type))
	{
		token = put_diveder(value,value[*i],i,type);
		put_in_parcer(token,*type);
		if(!value[*i + 1])
			*i = *i + 1;
	}
}

void	put_word(char **token_word,char *value, int *i,int *type)
{
	char *dollar;

	dollar = NULL;
	if(*token_word)
	{
		put_in_parcer(*token_word,10);
		*token_word = NULL;
	}
	if(value[*i]=='$')
	{
		dollar = dollar_token(i,dollar,value);
		if(dollar)
		{
			put_in_parcer(dollar,55);
			dollar = NULL;
		}
	}
	insert_dividers(value,i,type);
}

char *put_data_token(int *len, char *value, int *i)
{
	char *token_word;

	token_word = NULL;
	token_word = (char *)malloc(sizeof(char) * (*len + 1));
	token_word[*len] = '\0';
	*len = 0;
	while (*len <= (int)ft_strlen(token_word))
	{
		if(value[*i] == '\"')
			token_word = word_double_couts(i, value,len,token_word);
		else if(value[*i] == '\'')
		token_word = word_single_couts(i, value,len,token_word);
		else if(value[*i] == '>' || value[*i] == '<' ||
		value[*i] == '|' || value[*i] == '$')
		{
			*i = *i + 1;
			break;
		}
		else
		{
			token_word[*len] = value[*i];
			*i = *i + 1;
			*len = *len + 1;
		}
	}
	*i = *i - 1;
	return(token_word);
}
void initialisation_init(char **token, char **token_word,int *len_dollar,char **dollar)
{
	*token = NULL;
	*token_word = NULL;
	*len_dollar = 0;
	*dollar = NULL;
}

int    check_tokens(t_list *head, int error)
{
	t_init var;
	int i;

	i = 0;
	var.type = 0;
	var.len = 0;
	initialisation_init(&var.token,&var.token_word,&var.len_dollar,&var.dollar);
    while (head != NULL)
    {
		initialisation(&i,&var.len,&var.token,&var.token_word);
		while (i <= (int)ft_strlen(head->value))
		{
			var.len = len_word(head->value,i);
			if(var.len)
				var.token_word = put_data_token(&var.len, head->value,&i);
			put_word(&var.token_word,head->value,&i,&var.type);
			i++;
		}
        head = head->next;
    }
    error = 2;
	return(error);
}