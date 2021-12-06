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

int	args_token(t_args	**head, char *args)
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

char	*convert(char *value)
{
	char *error;
	int i;
	int j;

	i = 0;
	j = 0;
	error = (char *)malloc(sizeof(char) * ((int)ft_strlen(value) + 3));
	error[(int)ft_strlen(value) + 2] = '\0';
	while (error[i])
	{
		if(i == 0)
		{
			error[i] = '`';
			i++;
		}
		else if(i == (int)ft_strlen(error) - 1)
		{
			error[i] = '\'';
			i++;
		}
		else
		{
			error[i] = value[j];
			j++;
			i++;
		}
	}
	return(error);
}

void	print_error_rdt(char *value)
{
	char	*error;
	char	*error_rdt;

	error = "minishell: syntax error near unexpected token ";
	error_rdt = NULL;
	error_rdt = convert(value);
	error = ft_strjoin(error,error_rdt);
	write(1,error,ft_strlen(error));
	write(1,"\n",1);
}

int		error_redirection(int check, t_tokens *tokens)
{
	if(check == 1 || tokens->next == NULL)
	{
		if(check == 1)
			print_error_rdt(tokens->value);
		else
			print_error_rdt("newline");
		return(1);
	}
	return(0);
}

int		get_len_double(char *value)
{
	int i;
	int len;
	int check;

	i = 0;
	len = 0;
	check=0;
	while (i <= (int)ft_strlen(value))
	{
		if(value[i] == '\"' )
			len++;
		i++;
	}
	return(len / 2);
}

int		len_couts(char *value)
{
	int i;
	int l;

	i = 0;
	l = 0;

	while (value[i])
	{
		if(value[i] == '\"')
		{
			l++;
			i++;
			while (value[i])
			{
				if(value[i] == '\"')
				{
					l++;
					break;
				}
				i++;
			}
		}
		if(value[i] == '\'')
		{
			l++;
			i++;
			while (value[i])
			{
				if(value[i] == '\'')
				{
					l++;
					break;
				}
				i++;
			}
		}
		i++;
	}
	return(l / 2);
}



int	end_dollar(char *value, int *start)
{
	if(value[*start] == '\"'
	|| value[*start] == '>' || value[*start] == '<'
	|| value[*start] == '|' || value[*start] == '$'
	|| value[*start] == '\'')
	{
		return(1);
	}
	return(0);
}

void	skip_value(char *value, int *start)
{
	while (value[*start])
	{
		if(value[*start] == '?' && value[*start + 1] != '\0')
		{
			*start = *start + 1;
			break;
		}
		*start = *start + 1;
		}
	*start = *start - 1;
}

int		get_allocation(char *value)
{
	int i;
	int len;
	char **split;
	int		nb;

	i = 0;
	nb = 0;
	split = NULL;
	len = len_couts(value);
	while (value[i])
	{
		if(value[i] != '\"' && value[i] != '\'' && value[i] != ' ' && value[i + 1] == '\"' && value[i + 1] == '\'')
		{
			nb++;
			len--;
		}
		else if(value[i] == ' ' && ((value[i + 1] == '\"') ||  (value[i + 1] == '\'')))
			len++;
		if(value[i] == '\"')
		{
			value[i] = ' ';
			i++;
			while (value[i])
			{
				if(value[i] == '\"')
				{
					if(value[i + 1] != ' ')
						len--;
					value[i] = ' ';
					break;
				}
				value[i] = ' ';
				i++;
			}
		}
		else if(value[i] == '\'')
		{
			value[i] = ' ';
			i++;
			while (value[i])
			{
				if(value[i] == '\'')
				{
					if(value[i + 1] != ' ')
						len--;
					value[i] = ' ';
					break;
				}
				value[i] = ' ';
				i++;
			}
		}
		else if(value[i] == '$' && delimiter_skip(value,&i))
		{
			nb++;
			skip_value(value,&i);
		}
		i++;
	}

	split = ft_split(value,' ');
	i  = 0;
	while (split[i])
		i++;
	if(nb)
		i = i - nb;
	if(len <= 0)
		len = 0;
	len = len + i;
	if(len == 0)
		len = 1;
	return(len);
}

int		len_args(char *value ,int *start)
{
	int len;
	int check;

	len = 0;
	check = 0;
	while (value[*start])
	{
		if(value[*start] == '\"')
		{
			*start = *start + 1;
			while (value[*start])
			{
				if(value[*start] == '\"')
					break;
				len++;
				*start = *start + 1;
			}
		}
		else if(value[*start] == '\'')
		{
			*start = *start + 1;
			while (value[*start])
			{
				if(value[*start] == '\'')
					break;
				len++;
				*start = *start + 1;
			}
			
		}
		else if(value[*start] != ' ')
		{
			if(value[*start] != '\"')
			{
				if(value[*start] == '$' && delimiter_skip(value,start))
					skip_value(value,start);
				else
				{
					check = 1;
					len++;
				}
			}
		}
		else if(value[*start] == ' ' && check == 1)
			break;
		*start = *start + 1;
	}
	return(len);
}

char  **filter_args(char *value)
{
	int j;
	int i;
	int r;
	int len;
	char **filter;
	int tmp;
	char *vtmp;

	j = 0;
	i = 0;
	r = 0;
	filter = NULL;
	vtmp = ft_strdup(value);
	len = get_allocation(vtmp);
	if(len)
	{
		filter = (char **)malloc(sizeof(char *) * (len + 1));
		filter[len] = 0;
		j = 0;
		tmp = 0;
		while (j <= (int)ft_strlen(value))
		{
			i = len_args(value,&j);
			filter[r] = (char *)malloc(sizeof(char) * (i + 1));
			filter[r][i] = '\0';
			i = 0;
			while (filter[r][i])
			{
				if(value[tmp] == '\"')
				{
					tmp++;
					while (value[tmp])
					{
						if(value[tmp] == '\"')
						{
							tmp++;
							break;
						}
						filter[r][i] = value[tmp];
						i++;
						tmp++;
					}
				}
				else if(value[tmp] == '\'')
				{
					tmp++;
					while (value[tmp])
					{
						if(value[tmp] == '\'')
						{
							tmp++;
							break;
						}
						filter[r][i] = value[tmp];
						i++;
						tmp++;
					}
				}
				else if(value[tmp] != ' ')
				{
					if(value[tmp] == '$' && delimiter_skip(value,&tmp))
						skip_value(value,&tmp);
					else
					{
						filter[r][i] = value[tmp];
						i++;
					}
					tmp++;
				}
				else
					tmp++;
			}
			r++;
			j++;
		}
		filter[len] = 0;
	}
	return(filter);
}

int	all_data(t_data	**head, t_redirection *rdt, char **arguments, int nb_heredoc)
{
	t_data *new_node = malloc(sizeof(t_data));
	t_data *line;

	line = *head;
	new_node->arguments = arguments;
	new_node->redirection = rdt;
	new_node->nb_heredoc = nb_heredoc;
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

int		len_file_name(char *value)
{
	int i;
	int len;
	int check;

	i = 0;
	len = 0;
	check = 0;
	while (value[i])
	{
		if(value[i] == '$' && delimiter(value,&i))
			check = 1;
		if(value[i] == '?' && check == 1)
		{
			len--;
			check = 0;
		}
		len++;
		i++;
	}
	return(len);
}

int		get_len_word(char *value)
{
	int i;
	int len;
	int check;

	i = 0;
	len = 0;
	check = 0;
	while (value[i])
	{
		 if(value[i] == '\"')
		{
			i++;
			while (value[i])
			{
				if (value[i] == '\"')
					break;
				len++;
				i++;
			}
			
		}
		else if(value[i] == '\'')
		{
			i++;
			while (value[i])
			{
				if (value[i] == '\'')
					break;
				len++;
				i++;
			}
		}
		else if(value[i] != '\'' && value[i] != '\"')
		{
			if(value[i] == '$')
				check = 1;
			if(value[i] == '?' && check == 1)
			{
				len--;
				check = 0;
			}
			len++;
		}
		i++;
	}
	return(len);
}

int		get_len(char *value)
{
	int i;
	int len;
	int check;

	i = 0;
	len = 0;
	check = 0;
	while (value[i])
	{
		if(value[i] == '\"')
		{
			i++;
			while (value[i])
			{
				if(value[i] == '\"')
					break;
				i++;
				len++;
			}
			
		}
		else if(value[i] == '\'')
		{
			i++;
			while (value[i])
			{
				if(value[i] == '\'')
					break;
				i++;
				len++;
			}
			
		}
		else if(value[i] == '$' && delimiter(value, &i))
		{
			while (value[i])
			{
				if(value[i] == '?')
					break;
				i++;
			}
		}
		else
			len++;
		i++;
	}
	return(len);
}

int		is_couts(char *value)
{
	int i;

	i = 0;
	while (value[i])
	{
		if(value[i] == '\'' || value[i] == '\"' || (value[i] == '$' && !(delimiter(value,&i)) ))
			return(1);
		i++;
	}
	return(0);
}

char	*skip_dollar(char *value, int *error)
{
	int i;
	int	len;
	char	*file_name;

	i = 0;
	len = get_len(value);
	file_name = (char *)malloc(sizeof(char) * (len + 1));
	file_name[len] = 0;
	len = 0;
	while (file_name[len])
	{
		if(value[i] == '\"')
		{
			i++;
			while (value[i])
			{
				if(value[i] == '\"')
					break;
				file_name[len] = value[i];
				i++;
				len++;
			}
			
		}
		else if(value[i] == '\'')
		{
			i++;
			while (value[i])
			{
				if(value[i] == '\'')
					break;
				file_name[len] = value[i];
				i++;
				len++;
			}
		}
		else if(value[i] == '$' && delimiter(value, &i))
		{
			while (value[i])
			{
				if(value[i] == '?')
					break;
				i++;
			}
		}
		else
		{
			if(value[i] == ' ')
			{
				*error = -1;
				break;
			}
			file_name[len] = value[i];
			len++;
		}
		i++;
	}
	return(file_name);
}

char	*fill_file(char *value)
{
	int i;
	int		len;
	char	*file_name;
	int		check;

	i = 0;
	check = 0;
	len = len_file_name(value);
	file_name = (char *)malloc(sizeof(char) * (len + 1));
	file_name[len] = '\0';
	len = 0;
	while (file_name[len])
	{
		if(value[i] == '$' && delimiter(value,&i))
		{
			file_name[len] = value[i];
			i++;
			len++;
			check = 1;
		}
		if(value[i] == '?' && check == 1)
		{
			i++;
			check = 0;
		}
		else
		{
			file_name[len] = value[i];
			i++;
			len++;
		}
	}
	return(file_name);
}

int		len_herdoc(char *value)
{
	int i;
	int len;
	int check;

	i = 0;
	len = 0;
	check = 0;
	while (value[i])
	{
		if(value[i] == '\"')
		{
			i++;
			while (value[i])
			{
				if(value[i] == '\"')
					break;
				i++;
				len++;
			}
			
		}
		else if(value[i] == '\'')
		{
			i++;
			while (value[i])
			{
				if(value[i] == '\'')
					break;
				i++;
				len++;
			}
		}
		else
			len++;
		i++;
	}
	return(len);
}

char	*fill_herdoc(char *value)
{
	int i;
	int	len;
	char	*file_name;

	i = 0;
	len = len_herdoc(value);
	file_name = (char *)malloc(sizeof(char) * (len + 1));
	file_name[len] = 0;
	len = 0;
	while (file_name[len])
	{
		if(value[i] == '\"')
		{
			i++;
			while (value[i])
			{
				if(value[i] == '\"')
					break;
				file_name[len] = value[i];
				i++;
				len++;
			}
			
		}
		else if(value[i] == '\'')
		{
			i++;
			while (value[i])
			{
				if(value[i] == '\'')
					break;
				file_name[len] = value[i];
				i++;
				len++;
			}
		}
		else
		{
			file_name[len] = value[i];
			len++;
		}
		i++;
	}
	return(file_name);
}

char	*filter_value(char *value)
{
	char	*file_name;

	file_name = fill_herdoc(value);
	return(file_name);
}

char	*filter_file_dollar(char *value, int *error)
{
	int	i;
	char	*file_name;
	int		check;

	i = 0;
	check = is_couts(value);
	if(check)
		file_name = skip_dollar(value,error);
	else
	{
		file_name = fill_file(value);
		if(file_name[0] == '$')
			*error = 1;
		else if(is_space(file_name))
			*error = -1;
		else
			file_name = skip_dollar(value,error);
	}
	return(file_name);
}


int     fill_data(t_tokens *tokens, t_data **data,t_envp *env_list)
{
    t_redirection *rdt;
    t_args *args;
	int		check;
	int		type;
	int len;
	int 	j;
	int t;
	char **filter;
	char **arguments;
	int		pipe;
	int		nb_heredoc;
	char	*tmp;
	int		error;

    rdt = NULL;
    args = NULL;
	filter = NULL;
	arguments = NULL;
	check = 0;
	len = 0;
	j = 0;
	t = 0;
	error = 0;
	pipe = 0;
	nb_heredoc = 0;
	tmp = NULL;
    while (tokens != NULL)
    {
		if(tokens->type == 1)
		{
			pipe = 1;
			arguments = (char **)malloc(sizeof(char *) * (len + 1));
			t = 0;
			while (args != NULL)
			{
				arguments[t] = args->arguments;
				t++;
				args = args->next;
			}
			arguments[len] = 0;
			all_data(data,rdt,arguments,nb_heredoc);
			rdt = NULL;
			len = 0;
			nb_heredoc = 0;
			tokens = tokens->next;
		}
		else
		{
			pipe = 0;
			if( tokens->type <= 5 && tokens->type >= 2)
			{
				if(tokens->type == 5)
					nb_heredoc++;
				if(error_redirection(check, tokens))
					return(258);
				check = 1;
				type = tokens->type;
			}
			else if(check == 1)
			{
				check = 0;
				if(type != 5)
				{
					tokens->value = filter_file_dollar(tokens->value,&error);
					if(error == 1)
						type = 7;
					if(error == -1)
					{
						type = 7;
						tokens->value = ft_strdup(env_list->ambiguous->value);
						env_list->ambiguous = env_list->ambiguous->next;
					}
				}
				else
					tokens->value = filter_value(tokens->value);
				redirection_token(&rdt,type,tokens->value);
			}
			else
			{
				filter = filter_args(tokens->value);
				if(filter)
				{
					j = 0;
					while (filter[j])
					{
						args_token(&args,filter[j]);
						len++;
						j++;
					}
				}
			}
        	tokens = tokens->next;
		}
    }
	if(pipe == 0)
	{
			arguments = (char **)malloc(sizeof(char *) * (len + 1));
			t = 0;
			while (args != NULL)
			{
				arguments[t] = args->arguments;
				t++;
				args = args->next;
			}
			arguments[len] = 0;
			all_data(data,rdt,arguments,nb_heredoc);
			rdt = NULL;
			len = 0;
			nb_heredoc = 0;
	}
    return(0);
}