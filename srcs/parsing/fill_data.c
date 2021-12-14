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

int	check_dlm(int c)
{
	if(c != '\'' && c != '\"' && c != ' ' && c != '$'
		&& c != '|' && c != '<' && c != '>' && c != '\0')
		return(1);
	return(0);
}

int	allocation_expand(char *value, int *i)
{
	int len;

	len = 0;
	*i = *i + 1;
	if(value[*i] == '?')
	{
		*i = *i + 1;
		return (1);
	}
	while(value[*i])
	{
		if(value[*i] == '\'' || value[*i] == '\"' || value[*i] == ' ' 
			|| value[*i] == '$' || value[*i] == '|' || value[*i] == '<' 
			|| value[*i] == '>' || value[*i] == '\0')
			break;
		*i = *i + 1;
		len++;
	}
	return(len);
}

char	*get_env_hrd(char *value, t_envp *env_list)
{
	t_envp	*tmp;

	tmp = env_list;
	if(value[0] == '?')
		return(ft_itoa(env_list->exit_status));
	while (tmp != NULL)
	{
		if(!ft_strcmp(tmp->key,value))
			return(tmp->value);
		tmp = tmp->next;
	}
	tmp = NULL;
	return("\0");
}

void	get_dollar_expand(char *value, t_init *var,t_envp *env_list)
{
	t_init vr;
	char *dollar;

	vr.tmp = var->i;
	vr.i = 0;
	vr.len = allocation_expand(value,&var->i);
	dollar = (char *)malloc(sizeof(char) * (vr.len + 1));
	free_in_parcer(&env_list->allocation,dollar,NULL);
	dollar[vr.len] = '\0';
	vr.tmp++;
	while (vr.i < vr.len)
	{
		dollar[vr.i] = value[vr.tmp];
		vr.tmp++;
		vr.i++;
	}
	var->len = var->len + (int)ft_strlen(get_env_hrd(dollar,env_list));
}

int len_expand(char *value, t_envp *env_list)
{
	t_init var;

	var.len = 0;
	var.i = 0;
	while (value[var.i])
	{
		if(value[var.i] == '$' && check_dlm(value[var.i + 1]))
			get_dollar_expand(value,&var, env_list);
		else
		{
			var.len++;
			var.i++;
		}
	}
	return(var.len);
}

char *get_dollar_value(char *value, int *i, t_envp *env_list)
{
	t_init vr;
	char *dollar;

	vr.tmp = *i;
	vr.i = 0;
	vr.len = allocation_expand(value,i);
	dollar = (char *)malloc(sizeof(char) * (vr.len + 1));
	free_in_parcer(&env_list->allocation,dollar,NULL);
	dollar[vr.len] = '\0';
	vr.tmp++;
	while (vr.i < vr.len)
	{
		dollar[vr.i] = value[vr.tmp];
		vr.tmp++;
		vr.i++;
	}
	return(dollar);
}

void	fill_data_dollar(char *value, int *i, char *data,t_envp *env_list)
{
	t_init var;
	char *env;

	var.i = *i;
	var.j = 0;
	var.dollar = get_dollar_value(value,i,env_list);
	env = ft_strdup(get_env_hrd(var.dollar,env_list));
	free_in_parcer(&env_list->allocation,env,NULL);
	while (env[var.j])
	{
		data[var.i] = env[var.j];
		var.i++;
		var.j++;
	}

}

void	initialisation_expand(t_init *var, char *value, t_envp *env_list)
{
	var->i = 0;
	var->j = 0;
	var->tmp = 0;
	var->exp = NULL;
	var->len = len_expand(value, env_list);
	var->dollar = (char *)malloc(sizeof(char) * (var->len + 1));
	free_in_parcer(&env_list->allocation,var->dollar,NULL);
	var->dollar[var->len] = '\0';
	var->env = NULL;
}

void	fill_expand(char *dollar, char *value, int *tmp, int i)
{
	dollar[*tmp] = value[i];
	*tmp = *tmp + 1;
}

char	*expand_value(char *value, t_envp *env_list)
{
	t_init var;

	initialisation_expand(&var,value,env_list);
	while (var.tmp < var.len)
	{
		if(value[var.i] == '$' && check_dlm(value[var.i + 1]))
		{
			var.exp = get_dollar_value(value,&var.i,env_list);
			var.env = ft_strdup(get_env_hrd(var.exp,env_list));
			free_in_parcer(&env_list->allocation,var.env,NULL);
			var.j = 0;
			while (var.env[var.j])
			{
				var.dollar[var.tmp] = var.env[var.j];
				var.j++;
				var.tmp++;
			}
			var.i--;
		}
		else
			fill_expand(var.dollar,value,&var.tmp,var.i);
		var.i++;
	}
	return(var.dollar);
}

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

void	initialisation_convert(t_init *var, char *value, t_envp *env_list)
{
	var->i = 0;
	var->j = 0;
	var->check_error = (char *)malloc(sizeof(char) * ((int)ft_strlen(value) + 3));
	free_in_parcer(&env_list->allocation,var->check_error,NULL);
	var->check_error[(int)ft_strlen(value) + 2] = '\0';
}

char	*convert(char *value,t_envp *env_list)
{
	t_init var;

	initialisation_convert(&var,value,env_list);
	while (var.i < (int)ft_strlen(value) + 2)
	{
		if(var.i == 0)
		{
			var.check_error[var.i] = '`';
			var.i++;
		}
		else if(var.i == (int)ft_strlen(value) + 1)
		{
			var.check_error[var.i] = '\'';
			var.i++;
		}
		else
		{
			var.check_error[var.i] = value[var.j];
			var.j++;
			var.i++;
		}
	}
	return(var.check_error);
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

void	add_check_couts(int *l, int *i, char *value, int ele)
{
	*l = *l + 1;
	*i = *i + 1;
	while (value[*i])
	{
		if(value[*i] == ele)
		{
			*l = *l + 1;
			break;
		}
		*i = *i + 1;
	}
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
			add_check_couts(&l,&i,value,'\"');
		if(value[i] == '\'')
			add_check_couts(&l,&i,value,'\'');
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

void	fill_space(char *value, int *i, int *len, int ele)
{
	value[*i] = ' ';
		*i = *i + 1;
	while (value[*i])
	{
		if(value[*i] == ele)
		{
			if(value[*i + 1] != ' ')
				*len = *len - 1;
			value[*i] = ' ';
			break;
		}
		value[*i] = ' ';
		*i = *i + 1;
	}
}

char	**check_len_values(char *value,int *len, int nb, t_envp *env_list)
{
	char **split;
	int i;

	i  = 0;
	split = ft_split(value,' ');
	free_in_parcer(&env_list->allocation,NULL,split);
	while (split[i])
		i++;
	if(nb)
		i = i - nb;
	if(*len <= 0)
		*len = 0;
	*len = *len + i;
	if(*len == 0)
		*len = 1;
	return (split);
}

void	initialisation_get(t_init *var, char *value)
{
	var->i = 0;
	var->nb = 0;
	var->split = NULL;
	var->len = len_couts(value);
}

void	skip_dlm(int *nb, int *len)
{
	*nb = *nb + 1;
	*len = *len - 1;
}

int		get_allocation(char *value,t_envp *env_list)
{
	t_init var;

	initialisation_get(&var,value);
	while (value[var.i])
	{
		if(value[var.i] != '\"' && value[var.i] != '\'' && value[var.i] != ' '
		&& value[var.i + 1] == '\"' && value[var.i + 1] == '\'')
			skip_dlm(&var.nb,&var.len);
		else if(value[var.i] == ' ' && ((value[var.i + 1] == '\"') ||  (value[var.i + 1] == '\'')))
			var.len++;
		if(value[var.i] == '\"')
			fill_space(value,&var.i,&var.len,'\"');
		else if(value[var.i] == '\'')
			fill_space(value,&var.i,&var.len,'\'');
		else if(value[var.i] == '$' && delimiter_skip(value,&var.i))
		{
			var.nb++;
			skip_value(value,&var.i);
		}
		var.i++;
	}
	var.split = check_len_values(value,&var.len,var.nb,env_list);
	return(var.len);
}

void	fill_dollar_args(char *value, int *start, t_init *var)
{
	if(value[*start] == '$' && delimiter_skip(value,start))
		skip_value(value,start);
	else
	{
		var->check = 1;
		var->len++;
	}
}

void	file_len_args(int *start,char *value, int *len, int ele)
{
	*start = *start + 1;
	while (value[*start])
	{
		if(value[*start] == ele)
			break;
		*len = *len + 1;
		*start = *start + 1;
	}
}

int		len_args(char *value ,int *start)
{
	t_init var;

	var.len = 0;
	var.check = 0;
	while (value[*start])
	{
		if(value[*start] == '\"')
			file_len_args(start,value,&var.len,'\"');
		else if(value[*start] == '\'')
			file_len_args(start,value,&var.len,'\'');
		else if(value[*start] != ' ')
		{
			if(value[*start] != '\"')
				fill_dollar_args(value,start,&var);
		}
		else if(value[*start] == ' ' && var.check == 1)
			break;
		*start = *start + 1;
	}
	return(var.len);
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

int		is_couts_hrd(char *value)
{
	int i;

	i = 0;
	while (value[i])
	{
		if(value[i] == '\'' || value[i] == '\"')
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
	{
		if(!is_couts_hrd(tokens->value))
			var->type = 8;
		tokens->value = filter_value(tokens->value,env_list);
	}
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