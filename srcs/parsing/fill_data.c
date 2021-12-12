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

int	redirection_token(t_redirection	**head,int type, char *file_name, t_envp *env_list)
{
	t_redirection *new_node = malloc(sizeof(t_redirection));
	free_in_parcer(&env_list->allocation,new_node,NULL);
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

int	args_token(t_args	**head, char *args, t_envp *env_list)
{
	t_args *new_node = malloc(sizeof(t_redirection));
	free_in_parcer(&env_list->allocation,new_node,NULL);
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

char	*convert(char *value,t_envp *env_list)
{
	char *error;
	int i;
	int j;

	i = 0;
	j = 0;
	error = (char *)malloc(sizeof(char) * ((int)ft_strlen(value) + 3));
	free_in_parcer(&env_list->allocation,error,NULL);
	error[(int)ft_strlen(value) + 2] = '\0';
	while (i < (int)ft_strlen(value) + 2)
	{
		if(i == 0)
		{
			error[i] = '`';
			i++;
		}
		else if(i == (int)ft_strlen(value) + 1)
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

void	print_error_rdt(char *value,t_envp *env_list)
{
	char	*error;
	char	*error_rdt;

	error = "minishell: syntax error near unexpected token ";
	error_rdt = NULL;
	error_rdt = convert(value,env_list);
	error = ft_strjoin(error,error_rdt);
	free_in_parcer(&env_list->allocation,error,NULL);
	write(1,error,ft_strlen(error));
	write(1,"\n",1);
}

int		error_redirection(int check, t_tokens *tokens,t_envp *env_list)
{
	if(check == 1 || tokens->next == NULL)
	{
		if(check == 1)
			print_error_rdt(tokens->value,env_list);
		else
			print_error_rdt("newline",env_list);
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

int		get_allocation(char *value,t_envp *env_list)
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
	free_in_parcer(&env_list->allocation,NULL,split);
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

void	file_args_double(t_init *var,char *value,char **filter,int *tmp)
{
	*tmp = *tmp + 1;
	while (value[*tmp])
	{
		if(value[*tmp] == '\"')
		{
			*tmp = *tmp + 1;
			break;
		}
		filter[var->start][var->i] = value[*tmp];
		var->i++;
		*tmp = *tmp + 1;
	}
}

void	file_args_single(t_init *var,char *value,char **filter,int *tmp)
{
	*tmp = *tmp + 1;
	while (value[*tmp])
	{
		if(value[*tmp] == '\'')
		{
			*tmp = *tmp + 1;
			break;
		}
		filter[var->start][var->i] = value[*tmp];
		var->i++;
		*tmp = *tmp + 1;
	}
}

void	file_args_dollar(int *tmp,t_init *var, char *value, char **filter)
{
	if(value[*tmp] == '$' && delimiter_skip(value,tmp))
		skip_value(value,tmp);
	else
	{
		filter[var->start][var->i] = value[*tmp];
		var->i++;
	}
	*tmp = *tmp + 1;
}

char *initial(t_init *var, t_envp *env_list, char **filter, char *value)
{
	var->i = len_args(value,&var->j);
	filter[var->start] = (char *)malloc(sizeof(char) * (var->i + 1));
	free_in_parcer(&env_list->allocation,filter[var->start],NULL);
	filter[var->start][var->i] = '\0';
	var->check = var->i;
	var->i = 0;
	return(filter[var->start]);
}

char **declar(int *len, int *j, int *tmp, t_envp *env_list)
{
	char **filter;

	filter = (char **)malloc(sizeof(char *) * (*len + 1));
	free_in_parcer(&env_list->allocation,NULL,filter);
	filter[*len] = 0;
	*j = 0;
	*tmp = 0;
	return(filter);
}

void	initialisation_args(t_init *var, char *value, t_envp *env_list)
{
	var->j = 0;
	var->i = 0;
	var->start = 0;
	var->check = 0;
	var->filter = NULL;
	var->vtmp = ft_strdup(value);
	free_in_parcer(&env_list->allocation,var->vtmp,NULL);
	var->len = get_allocation(var->vtmp,env_list);
}

void	check_position(t_init *var, char *value, char **filter, int *tmp)
{
	if(value[*tmp] == '\"')
		file_args_double(var,value,filter,tmp);
	else if(value[*tmp] == '\'')
		file_args_single(var,value,filter,tmp);
	else if(value[*tmp] != ' ')
		file_args_dollar(tmp,var,value,filter);
	else
		*tmp = *tmp + 1;
}

char  **filter_args(char *value,t_envp *env_list)
{
	t_init var;

	initialisation_args(&var,value,env_list);
	if(var.len)
	{
		var.filter = declar(&var.len,&var.j,&var.tmp,env_list);
		while (var.j <= (int)ft_strlen(value))
		{
			var.filter[var.start] = initial(&var,env_list,var.filter,value);
			while (var.i < var.check)
				check_position(&var,value,var.filter,&var.tmp);
			var.start++;
			var.j++;
		}
		var.filter[var.len] = 0;
	}
	return(var.filter);
}

int	all_data(t_data	**head, t_init *var,t_envp *env_list)
{
	t_data *new_node = malloc(sizeof(t_data));
	free_in_parcer(&env_list->allocation,new_node,NULL);
	t_data *line;

	line = *head;
	new_node->arguments = var->arguments;
	new_node->redirection = var->rdt;
	new_node->nb_heredoc = env_list->nb_herdoc;
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

void	skip_content_value(char *value, int *i, int *len, int ele)
{
	*i = *i + 1;
	while (value[*i])
	{
		if(value[*i] == ele)
			break;
		*i = *i + 1;
		*len = *len + 1;
	}
}

void	dollar_handler(char *value, int *i, int *check,int *len)
{
	if(value[*i] == '$')
		*check = 1;
	if(value[*i] == '?' && *check == 1)
	{
		*len = *len - 1;
		*check = 0;
	}
	*len = *len + 1;
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
			skip_content_value(value,&i,&len,'\"');
		else if(value[i] == '\'')
			skip_content_value(value,&i,&len,'\'');
		else if(value[i] != '\'' && value[i] != '\"')
			dollar_handler(value,&i,&check,&len);
		i++;
	}
	return(len);
}

void	check_point(char *value, int *i)
{
	while (value[*i])
	{
		if(value[*i] == '?')
			break;
		*i = *i + 1;
	}
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
			skip_content_value(value,&i,&len,'\"');
		else if(value[i] == '\'')
			skip_content_value(value,&i,&len,'\'');
		else if(value[i] == '$' && delimiter(value, &i))
			check_point(value,&i);
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

void	file_skip(char *value, int *i)
{
	while (value[*i])
	{
		if(value[*i] == '?')
			break;
		*i = *i + 1;
	}
}

void	initialisation_values(t_init *vr, char *value, t_envp *env_list)
{
	vr->i = 0;
	vr->len = get_len(value);
	vr->tmp = vr->len;
	vr->file_name = (char *)malloc(sizeof(char) * (vr->len + 1));
	free_in_parcer(&env_list->allocation,vr->file_name,NULL);
	vr->file_name[vr->len] = 0;
	vr->len = 0;
}

char	*skip_dollar(char *value, t_init *var,t_envp *env_list)
{
	t_init vr;

	initialisation_values(&vr,value,env_list);
	while (vr.len < vr.tmp)
	{
		if(value[vr.i] == '\"')
			file_double(value,&vr.i,&vr.len,vr.file_name);
		else if(value[vr.i] == '\'')
			file_single(value,&vr.i,&vr.len,vr.file_name);
		else if(value[vr.i] == '$' && delimiter(value, &vr.i))
			file_skip(value,&vr.i);
		else
		{
			if(value[vr.i] == ' ')
			{
				var->error = -1;
				break;
			}
			vr.file_name[vr.len] = value[vr.i];
			vr.len++;
		}
		vr.i++;
	}
	return(vr.file_name);
}

void	initialisation_file(t_init *var, char *value, t_envp *env_list)
{
	var->i = 0;
	var->check = 0;
	var->len = len_file_name(value);
	var->tmp = var->len;
	var->file_name = (char *)malloc(sizeof(char) * (var->len + 1));
	free_in_parcer(&env_list->allocation,var->file_name,NULL);
	var->file_name[var->len] = '\0';
	var->len = 0;
}

char	*fill_file(char *value, t_envp *env_list)
{
	t_init var;

	initialisation_file(&var,value,env_list);
	while (var.len < var.tmp)
	{
		if(value[var.i] == '$' && delimiter(value,&var.i))
		{
			var.file_name[var.len] = value[var.i];
			var.i++;
			var.len++;
			var.check = 1;
		}
		if(value[var.i] == '?' && var.check == 1)
		{
			var.i++;
			var.check = 0;
		}
		else
		{
			var.file_name[var.len] = value[var.i];
			var.i++;
			var.len++;
		}
	}
	return(var.file_name);
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
			skip_content_value(value, &i, &len,'\"');
		else if(value[i] == '\'')
			skip_content_value(value, &i, &len,'\'');
		else
			len++;
		i++;
	}
	return(len);
}

void	file_double(char *value, int *i, int *len, char *file_name)
{
	*i = *i + 1;
	while (value[*i])
	{
		if(value[*i] == '\"')
			break;
		file_name[*len] = value[*i];
		*i = *i + 1;
		*len = *len + 1;
	}
}

void	file_single(char *value, int *i, int *len, char *file_name)
{
	*i = *i + 1;
	while (value[*i])
	{
		if(value[*i] == '\'')
			break;
		file_name[*len] = value[*i];
		*i = *i + 1;
		*len = *len + 1;
	}
}			
char	*fill_herdoc(char *value,t_envp *env_list)
{
	t_init var;

	var.i = 0;
	var.len = len_herdoc(value);
	var.tmp = var.len;
	var.file_name = (char *)malloc(sizeof(char) * (var.len + 1));
	free_in_parcer(&env_list->allocation,var.file_name,NULL);
	var.file_name[var.len] = 0;
	var.len = 0;
	while (var.len < var.tmp)
	{
		if(value[var.i] == '\"')
			file_double(value, &var.i, &var.len, var.file_name);
		else if(value[var.i] == '\'')
			file_single(value, &var.i, &var.len, var.file_name);
		else
		{
			var.file_name[var.len] = value[var.i];
			var.len++;
		}
		var.i++;
	}
	return(var.file_name);
}

char	*filter_value(char *value,t_envp *env_list)
{
	char	*file_name;

	file_name = fill_herdoc(value,env_list);
	return(file_name);
}

char	*filter_file_dollar(char *value, t_init *var, t_envp *env_list)
{
	int	i;
	char	*file_name;
	int		check;

	i = 0;
	check = is_couts(value);
	if(check)
		file_name = skip_dollar(value,var,env_list);
	else
	{
		file_name = fill_file(value,env_list);
		if(file_name[0] == '$')
			var->error = 1;
		else if(is_space(file_name))
			var->error = -1;
		else
			file_name = skip_dollar(value,var,env_list);
	}
	return(file_name);
}

char	**put_data(t_init *var, t_envp *env_list)
{
	char **arguments;
	int	t;
	
	arguments = NULL;
	arguments = (char **)malloc(sizeof(char *) * (var->len + 1));
	free_in_parcer(&env_list->allocation,NULL,arguments);
	t = 0;
	while (var->args != NULL)
	{
		arguments[t] = var->args->arguments;
		t++;
		var->args = var->args->next;
	}
	arguments[var->len] = 0;
	env_list->nb_herdoc = var->nb_heredoc;
	var->len = 0;
	var->nb_heredoc = 0;
	return(arguments);
}

int	redirection_value(t_tokens *tokens,t_envp *env_list,t_init *var)
{
	if(tokens->type == 5)
		var->nb_heredoc = var->nb_heredoc + 1;
	if(error_redirection(var->check, tokens,env_list))
		return(1);
	var->check = 1;
	return(0);
}

char	*file_dollar(t_tokens *tokens, t_init *var, t_envp *env_list)
{
	if(var->type != 5)
	{
		tokens->value = filter_file_dollar(tokens->value,var,env_list);
		if(var->error == 1)
			var->type = 7;
		if(var->error == -1)
		{
			var->type = 7;
			tokens->value = ft_strdup(env_list->ambiguous->value);
			free_in_parcer(&env_list->allocation,tokens->value,NULL);
			env_list->ambiguous = env_list->ambiguous->next;
		}
	}
	else
		tokens->value = filter_value(tokens->value,env_list);
	return(tokens->value);
}

int		error_value(t_init *var, char *value,t_envp *env_list)
{
	if(!ft_strcmp(value,"|"))
	{
		write(1,"minishell: syntax error near unexpected token `|'\n",50);
			return(1);
	}
	redirection_token(&var->rdt,var->type,value,env_list);
	return(0);
}

void	fill_filter(t_init *var, char *value, t_envp *env_list)
{
	int j;
	char **filter;

	j = 0;
	filter = filter_args(value,env_list);
	if(filter)
	{
		while (filter[j])
		{
			args_token(&var->args,filter[j],env_list);
			var->len = var->len + 1;
			j++;
		}
	}
}

void	initialisation_data(t_init *var)
{
	var->rdt = NULL;
    var->args = NULL;
	var->check = 0;
	var->len = 0;
	var->error = 0;
	var->pipe = 0;
	var->nb_heredoc = 0;
	var->arguments = NULL;
}

int		file_error(t_init *var, t_tokens *tokens, t_envp *env_list)
{
	var->pipe = 0;
	if( tokens->type <= 5 && tokens->type >= 2)
	{
		if(redirection_value(tokens,env_list,var))
			return(1);
		var->type = tokens->type;
	}
	else if(var->check == 1)
	{
		var->check = 0;
		tokens->value = file_dollar(tokens,var, env_list);
		if(error_value(var,tokens->value,env_list))
			return(1);
	}
	else
		fill_filter(var,tokens->value,env_list);
	return (0);
}

void	prep_data(t_init *var, t_envp *env_list,t_data **data)
{
	var->arguments = put_data(var,env_list);
	all_data(data,var,env_list);
	var->rdt = NULL;
	var->args = NULL;
}

int     fill_data(t_tokens *tokens, t_data **data,t_envp *env_list)
{
	t_init var;

	initialisation_data(&var);
    while (tokens != NULL)
    {
		if(tokens->type == 1 && var.check != 1)
		{
			var.pipe = 1;
			prep_data(&var,env_list,data);
			tokens = tokens->next;
		}
		else
		{
			if (file_error(&var,tokens,env_list))
				return (258);
        	tokens = tokens->next;
		}
    }
	if(var.pipe == 0)
		prep_data(&var,env_list,data);
    return(0);
}