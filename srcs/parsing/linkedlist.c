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
			*type = 4;
		return(1);
		
	}
	return(0);
}

int	put_in_parcer(t_tokens **head, char *value, int type)
{
	char *tmp;

	tmp = ft_strdup(value);
	t_tokens *new_node = malloc(sizeof(t_tokens));
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

char	*put_diveder(char *data, int value, int *i,int *type)
{
	char *token;
	
	token = (char *)malloc(sizeof(char) * (2));
	if((value == '>' && data[*i + 1] && data[*i + 1] == '>'))
	{
		token = ft_strdup(">>");
		*type = 3;
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
		if (value[start] == ' ' || value[start] == '\"' || value[start] == '\'' ||
		value[start] == '$' || value[start] == '>' || value[start] == '|'
		|| value[start] == '<')
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

void	take_couts(int *start, char *value, int *i)
{
	*start = *start + 1;
	while (value[*start])
	{
		if(value[*start] == '\'')
			break;
		*i = *i + 1;
		*start = *start + 1;
	}
}

void	initialisation_var(int *i, int *close, char **dollar, int *len_dollar)
{
	*i = 0;
	*close = 0;
	*dollar = NULL;
	*len_dollar = 0;
}

void	dollar_manipulation(char *value,int *start, int *i)
{
	t_init var;
	*i = *i + 1;
	var.dollar = NULL;
	var.len_dollar = check_dollar(value,*start + 1);
	var.dollar = (char *)malloc(sizeof(char) * (var.len_dollar + 1));
	var.dollar[var.len_dollar] = '\0';
	var.len_dollar = 0;
	*start = *start + 1;
	while (var.dollar[var.len_dollar])
	{
		var.dollar[var.len_dollar] = value[*start];
		var.len_dollar = var.len_dollar + 1;
		*start = *start + 1;
	}
	if(var.dollar)
	{
		*i = *i + (int)ft_strlen(get_env(var.dollar));
		*i = *i - 1;
		*start = *start - 1;
	}
}

int	delimiter(char *value, int *start)
{
	if(value[*start] == '$' && value[*start + 1] && value[*start + 1] != '\"'
	&& value[*start + 1] != '>' && value[*start + 1] != '<'
	&& value[*start + 1] != '|' && value[*start + 1] != '$'
	&& value[*start + 1] != '\'')
	{
		return(1);
	}
	return(0);
}

void	single_couts(char *value, int *start, int *i)
{
	if (value[*start] == '\'')
		take_couts(start,value,i);
	else if(value[*start] == '$' && delimiter(value, start))
		dollar_manipulation(value,start,i);
	else
		*i = *i + 1;
}

void	skip_string(char *value, int *start, int *i, int *len_dollar)
{
	while (value[*start])
	{
		if(value[*start] == '\"')
			break;
		if(value[*start] == '$' && delimiter(value,start))
			take_dollar(value, start, len_dollar,i);
		*i = *i + 1;
		*start = *start + 1;
	}
}

int		len_word(char *value, int start)
{
	t_init var;

	initialisation_var(&var.i,&var.close,&var.dollar,&var.len_dollar);
	while (start < (int)ft_strlen(value))
	{
		if(value[start] == '|' || value[start] == '>' ||
		value[start] == '<')
			break;
		if (value[start] == '\"')
		{
			start++;
			skip_string(value,&start,&var.i,&var.len_dollar);
			var.i = var.i + 2;
		}
		else
			single_couts(value,&start,&var.i);
		start++;
	}
	return(var.i);
}

char	*initialisation_dollar(int *len_dollar, int *i)
{
	char *dollar;

	dollar = (char *)malloc(sizeof(char) * (*len_dollar + 1));
	dollar[*len_dollar] = '\0';
	*len_dollar = 0;
	*i = *i + 1;
	return(dollar);
}

char *dollar_value(char *token_word,char *value,int *len, int *i)
{
	t_init var;
	int j;

	j = 0;
	var.len_dollar = check_dollar(value,*i + 1);
	var.dollar = initialisation_dollar(&var.len_dollar,i);
	while (var.dollar[var.len_dollar])
	{
		var.dollar[var.len_dollar] = value[*i];
		var.len_dollar = var.len_dollar + 1;
		*i = *i + 1;
	}
	if(var.dollar)
	{
		var.dollar = ft_strdup(get_env(var.dollar));
		j = 0;
		while (var.dollar[j])
		{
			token_word[*len] = var.dollar[j];
			*len = *len + 1;
			j++;
		}
		var.dollar = NULL;
	}
	return(token_word);
}


void	add_dollar(int *i, int *len, char *token_word, char *value)
{
	if(value[*i - 1] == '\"')
	{
		token_word[*len] = value[*i - 1];
		*len = *len + 1;
	}
}

void	right_couts(char *token_word, char *value, int *len, int *i)
{
	token_word[*len] = value[*i - 1];
	*len = *len + 1;
}

void	add_double_couts(char *token_word, char *value, int *len, int *i)
{
	if(value[*i - 1] == '\"')
	{
		token_word[*len] = value[*i];
		*len = *len + 1;
	}
	token_word[*len] = value[*i];
	*len = *len + 1;
	*i = *i + 1;
}

char	*word_double_couts(int *i,char *value, int *len,char *token_word)
{
	*i = *i + 1;
	while (*i <= (int)ft_strlen(value))
	{
		if(value[*i] == '\"')
		{
			add_double_couts(token_word,value,len,i);
			break;
		}
		if(value[*i] == '$' && delimiter(value,i))
		{
			add_dollar(i,len,token_word,value);
			token_word = dollar_value(token_word,value,len,i);
		}
		else
		{
			if(value[*i - 1] == '\"')
				right_couts(token_word, value, len,i);
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

char	*initialisation_token(int *len)
{
	char *token_word;
	
	token_word = NULL;
	token_word = (char *)malloc(sizeof(char) * (*len + 1));
	token_word[*len] = '\0';
	*len = 0;
	return(token_word);
}

void	convert_dollar(char *token_word,char *value, int *i, int *len)
{
	t_init var;
	int		j;

	j = 0;
	var.len_dollar = check_dollar(value,*i + 1);
	var.dollar = initialisation_dollar(&var.len_dollar,i);
	while (var.dollar[var.len_dollar])
	{
		var.dollar[var.len_dollar] = value[*i];
		var.len_dollar = var.len_dollar + 1;
		*i = *i + 1;
	}
	if(var.dollar)
	{
		var.dollar = ft_strdup(get_env(var.dollar));
		j = 0;
		while (var.dollar[j])
		{
			token_word[*len] = var.dollar[j];
			*len = *len + 1;
			j++;
		}
		var.dollar = NULL;
	}
}

void	continue_add(char *token_word, char *value, int *len,int *i)
{
	token_word[*len] = value[*i];
	*i = *i + 1;
	*len = *len + 1;
}

char *put_data_token(int *len, char *value, int *i)
{
	char *token_word;
	
	token_word = initialisation_token(len);
	while (*len <= (int)ft_strlen(token_word))
	{
		if(value[*i] == '\"')
			token_word = word_double_couts(i, value,len,token_word);
		else if(value[*i] == '\'')
		token_word = word_single_couts(i, value,len,token_word);
		else if(value[*i] == '>' || value[*i] == '<' ||
		value[*i] == '|')
		{
			*i = *i + 1;
			break;
		}
		else
		{
			if(value[*i] == '$' && delimiter(value,i))
				convert_dollar(token_word,value,i,len);
			else
				continue_add(token_word,value,len,i);
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

void	put_word(t_tokens **data ,char **token_word)
{
	char *dollar;

	dollar = NULL;
	if(*token_word)
	{
		put_in_parcer(data,*token_word,6);
		*token_word = NULL;
	}
}

void	insert_dividers(t_tokens **data ,char *value,int *i,int *type)
{
	char *token;

	token = NULL;
	if(value[*i] && check_dividers(value[*i],type))
	{
		token = put_diveder(value,value[*i],i,type);
		put_in_parcer(data,token,*type);
		if(!value[*i + 1])
			*i = *i + 1;
	}
}

int    check_tokens(t_list *head, int error)
{
	t_init var;
	t_tokens *data;
	int i;

	i = 0;
	data = NULL;
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
			put_word(&data,&var.token_word);
			insert_dividers(&data,head->value,&i,&var.type);
			i++;
		}
        head = head->next;
    }
	error = fill_data(data);
	return(error);
}