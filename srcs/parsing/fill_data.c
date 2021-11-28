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
int		get_allocation(char *value)
{
	int i;
	int len;
	int	r;
	int	check;
	char **split;

	i = 0;
	len = 0;
	r = 0;
	check = 0;
	split = ft_split(value,' ');
	printf("|%s|\n",value);
	while (split[i])
	{
		printf("%s\n",split[i]);
		r = 0;
		while (r <= (int)ft_strlen(split[i]))
		{
			check = 0;
			if(split[i][r] == '\"')
			{
				r++;
				while (split[i][r])
				{
					if(split[i][r] == '\"')
					{
						len--;
						check = 1;
						break;
					}
					r++;
				}
				if(check == 0)
				{
					i++;
					while (split[i])
					{
						if(split[i][(int)ft_strlen(split[i]) - 1] == '\"')
							break;
						i++;
					}	
				}
			}
			else
				break;
			r++;
		}
		len++;
		i++;
	}
	if(len == 0)
		len = 1;
	printf("%d\n",len);
	return(0);
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
				{
					break;
				}
				len++;
				*start = *start + 1;
			}
		}
		if(value[*start] != ' ')
		{
			if(value[*start] != '\"')
			{
				check = 1;
				len++;
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

	j = 0;
	i = 0;
	r = 0;
	filter = NULL;
	len = get_allocation(value);
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
							break;
						filter[r][i] = value[tmp];
						i++;
						tmp++;
					}
				}
				else if(value[tmp] != ' ')
				{
					filter[r][i] = value[tmp];
					i++;
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

int	all_data(t_data	**head, char **arguments)
{
	t_data *new_node = malloc(sizeof(t_data));
	t_data *line;

	line = *head;
	new_node->arguments = arguments;
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
    t_redirection *rdt;
    t_args *args;
	int		check;
	int		type;
	int len;
	int 	j;
	int t;
	char **filter;
	t_data *data;
	char **arguments;

    rdt = NULL;
    args = NULL;
	data = NULL;
	filter = NULL;
	arguments = NULL;
	check = 0;
	len = 0;
	j = 0;
	t = 0;
    while (tokens != NULL)
    {
		if(tokens->type == 1)
		{
			// arguments = (char **)malloc(sizeof(char *) * (len + 1));
			// t = 0;
			// while (args != NULL)
			// {
			// 	arguments[t] = args->arguments;
			// 	t++;
			// 	args = args->next;
			// }
			// arguments[len] = 0;
			// all_data(&data,arguments);
			// len = 0;
			// tokens = tokens->next;
		}
		else
		{
			if( tokens->type <= 5 && tokens->type >= 2)
			{
				if(error_redirection(check, tokens))
					return(1);
				check = 1;
				type = tokens->type;
			}
			else if(check == 1)
			{
				check = 0;
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
	// while (data != NULL)
	// {
	// 	j = 0;
	// 	while (data->arguments[j])
	// 	{
	// 		printf("%s\n",data->arguments[j]);
	// 		j++;
	// 	}
	// 	data = data->next;
	// }
	
    return(0);
}