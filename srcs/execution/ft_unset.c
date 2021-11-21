# include "../includes/minishell.h"

void	remove_from_env(t_envp **head, char *key)
{
	t_envp *tmp;
    t_envp *prev;

	tmp = (*head);
	if (tmp == NULL)
		return;
    if (!strcmp(key, tmp->key))
    {
        (*head) = tmp->next;
        return ;
        free_envp(tmp);
    }

    while (tmp != NULL && ft_strcmp(key, tmp->key))
    {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL)
        return;
    prev->next = tmp->next;
    free_envp(tmp);
}

void ft_unset(char **args, t_envp **env_list)
{
    int i;

    i = 1;
    while (args[i])
    {
        if (env_key_error(args[i]))
            printf("bash: export: `%s`: not a valid identifier\n", args[i]);
        else
            remove_from_env(env_list, args[i]);
        i++;
    }
}
