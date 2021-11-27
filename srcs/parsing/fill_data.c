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

	i = 0;
	len = 0;
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

	i = 0;
	len = 0;
	while (i <= (int)ft_strlen(value))
	{
		if(value[i] == ' ' )
		{
			i++;
			while (value[i])
			{
				if(value[i] != ' ')
				{
					len++;
					break;
				}
				i++;
			}
		}
		else if(value[i] == '\"' )
		{
			i++;
			while (value[i] != '\"')
				i++;
		}
		i++;
	}
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
	}
	return(filter);
}

int     fill_data(t_tokens *tokens)
{
    t_redirection *rdt;
    t_args *args;
	int		check;
	int		type;
	int 	j;
	char **filter;

    rdt = NULL;
    args = NULL;
	check = 0;
	j = 0;
    while (tokens != NULL)
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
					printf("**%s**\n",filter[j]);
					j++;
				}
				
			}
		}
        tokens = tokens->next;
    }

	while (rdt != NULL)
	{
		printf("%d %s\n",rdt->type,rdt->file_name);
		rdt = rdt->next;
	}
	
    
    return(0);
}