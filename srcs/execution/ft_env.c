# include "../includes/minishell.h"

void print_env(t_envp **head)
{
    t_envp *current_node = (*head);
   	while ( current_node != NULL)
    {
        if (current_node->equal)
        {

            ft_putstr_fd(current_node->key, 1);
            ft_putstr_fd("=", 1);
        }
        if (current_node->value)
            ft_putstr_fd(current_node->value, 1);
        ft_putstr_fd("\n", 1);
        current_node = current_node->next;
    }
}

void    ft_env(t_data *data, t_envp **env_list)
{
    (void) data;
    print_env(env_list);
}

int		fetch_fd(t_redirection *red, int **fd)
{
	t_redirection *tmp;

	*fd = malloc(2 * sizeof(int));
	if (*fd == NULL)
		return (1);
	(*fd)[0] = 0;
	(*fd)[1] = 1;
	tmp = red;
	while (tmp != NULL)
	{
		if (tmp->type == 0)
		{
			(*fd)[0] = open(tmp->file_name, O_RDONLY);
			if ((*fd)[0] == -1)
				return (1);
		}
		if (tmp->type == 1)
		{
			(*fd)[1] = open(tmp->file_name, O_RDWR | O_CREAT | O_TRUNC, 0777);
			if ((*fd)[1] == -1)
				return (1);
		}
		printf("%s\n", tmp->file_name);
		tmp = tmp->next;
	}
	return (0);
}

void	ft_builtins(t_data *data, t_envp **env_list)
{

		if (ft_strcmp(data->arguments[0],"echo") == 0)
			ft_echo(data); 
		if (ft_strcmp(data->arguments[0], "pwd") == 0)
			ft_pwd();
		if (ft_strcmp(data->arguments[0], "env") == 0)
			ft_env(data, env_list);
		if (ft_strcmp(data->arguments[0], "export") == 0)
			ft_export(data, env_list);
		if (ft_strcmp(data->arguments[0], "unset") == 0)
			ft_unset(data->arguments, env_list);
		if (ft_strcmp(data->arguments[0], "exit") == 0)
			ft_exit();
		if (ft_strcmp(data->arguments[0], "cd") == 0)
			ft_cd(data);
}

int		is_builtin(char *cmd)
{
		if (ft_strcmp(cmd,"echo") == 0)
			return (1);
		if (ft_strcmp(cmd, "env") == 0)
			return (1);
		if (ft_strcmp(cmd, "export") == 0)
			return (1);
		if (ft_strcmp(cmd, "unset") == 0)
			return (1);
		if (ft_strcmp(cmd, "exit") == 0)
			return (1);
		if (ft_strcmp(cmd, "pwd") == 0)
			return (1);
		if (ft_strcmp(cmd, "cd") == 0)
			return (1);
		return (0);
}

char	*fetch_env_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	return (envp[i]);
}

void	error_command(char	*str)
{
	if (str)
		ft_putstr_fd(str, 2);
	ft_putstr_fd(" : command not found\n", 2);
	exit(127);
}

char	*fetch_pathname(char	*cmd,	char	**envp)
{
	char	**path;
	char	*pathname;
	int		i;

	i = 0;

	if (!cmd)
		error_command(NULL);
	if (access(cmd, F_OK) == 0 && cmd[0] == '/')
		return (ft_strdup(cmd));
	path = ft_split(fetch_env_path(envp), ':');
	path[0] = ft_free_first(path[0], ft_strdup(ft_strrchr(path[0], '=') + 1));
	while (path[i])
	{
		pathname = ft_strjoin_char(path[i], cmd, '/');
		if (access(pathname, F_OK) == 0)
			break ;
		i++;
		free(pathname);
		if (path[i] == 0)
			error_command(cmd);
	}
	ft_free_split(path);
	return (pathname);
}

void	ft_execute(char **args, int *fd, char **envp)
{
	char *path;


	if (args[0][0] == '/' || !ft_strncmp(args[0], "./", 2))
		path = ft_strdup(args[0]);
	else
		path = fetch_pathname(args[0], envp);
	printf("fd[1]=%d\n", fd[1]);
	if (fd[0] != 0)
		dup2(fd[0], STDIN_FILENO);
	if (fd[1] != 1)
	{
		//printf("fd[1]=%d\n", fd[1]);
		//printf("%d\n", fd[1]);
		dup2(fd[1], STDOUT_FILENO);
	}
	execve(path, args, envp);
	perror("");
	exit(127);
}

int		exec_cmd(t_data *data, char **envp)
{

	//int pipe_fd[2];
	int fork_id[2];
	int *fd;
	fork_id[0] = fork();
	if (fork_id[0] == 0)
	{
		fetch_fd(data->redirection, &fd);
		if (fd == NULL)
			return (-1);
		ft_execute(data->arguments, fd, envp);
	}
	else
		wait(NULL);
	return (0);
}
void	new_node_redirect(t_redirection **head, char *file, int type)
{
	t_redirection *new;
	t_redirection *tmp;

	tmp = *head;
	new = malloc(sizeof(t_redirection));
	new->file_name = ft_strdup(file);
	new->type = type;
	new->next = NULL;
	if (*head == NULL)
	{
		(*head) = new;
		return ;
	}
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		printf("TEST\n");
	}
	tmp->next = new;
}

t_redirection * fill_redirect()
{
	t_redirection *head;
	head = NULL;
	new_node_redirect(&head, "file1", 1);
	new_node_redirect(&head, "file2", 1);
	new_node_redirect(&head, "file3", 1);
	new_node_redirect(&head, "file4", 1);
	//new_node_redirect(&head, "file2", 1);
	printf("%s\n", head->file_name);
	//printf("%s\n", head->filename);

	return (head);
}