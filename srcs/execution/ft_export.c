# include "../includes/minishell.h"

void print_exp(t_envp *head) {
    t_envp *current_node;
    
    current_node = head;

   	while (current_node != NULL)
    {
        ft_putstr_fd("declare -x ", 1);
        ft_putstr_fd(current_node->key, 1);
        if (current_node->equal)
        {
            ft_putstr_fd("=\"", 1);
            if (current_node->value)
                ft_putstr_fd(current_node->value, 1);
            ft_putstr_fd("\"", 1);
        }
        ft_putstr_fd("\n", 1);
        current_node = current_node->next;
    }
}

t_envp*	fill_envp(char *str)
{
	t_envp *node;

	node = malloc(sizeof(t_envp));

	if (ft_strchr(str, '='))
	{
		node->equal = 1;
		node->key = ft_substr(str, 0, ft_indexof(str, '='));
		if (*(ft_strchr(str,'=') + 1))
			node->value = ft_strdup(ft_strchr(str,'=') + 1);
		else
			node->value = 0;
	}
	else
	{
		node->equal = 0;
		node->key = ft_strdup(str);
		node->value = 0;
	}
	node->next=NULL;
	return node;
}

int     env_key_error(char *var)
{
    int i;

    i = 1;
    if (!ft_isalpha(var[0]) && var[0] != '_')
        return (1);
    while (var[i])
    {
        if (!ft_isalnum(var[i]) && var[i] != '_')
            return (1);
        i++;
    }
    return(0);
}

void	add_to_env(t_envp **head, t_envp *node)
{
	t_envp *tmp;

	tmp = (*head);
	if (tmp == NULL)
	{
		*head = node;
		return;
	}
	while (tmp != NULL)
	{
		if (!ft_strcmp(node->key, tmp->key))
		{
			if (node->equal)
			{
				tmp->equal = 1;
				tmp->value = ft_free_first(tmp->value, ft_strdup_null(node->value));
			}
			free_envp(node);
			return ;
		}
		if (tmp->next == NULL)
			break;
		tmp = tmp->next;
	}
	tmp->next = node;
}

void	ft_export(t_data *data, t_envp **env_list)
{
    int i;
	t_envp *node;


    i = 1;
    if (data->arguments[1] == NULL)
        print_exp(*env_list);
    else
    {
        while (data->arguments[i])
        {
            node = fill_envp(data->arguments[i]);
            if (env_key_error(node->key))
                printf("bash: export: `%s`: not a valid identifier\n", data->arguments[i]);
            else
                add_to_env(env_list, node);
            i++;
        }
    }
}