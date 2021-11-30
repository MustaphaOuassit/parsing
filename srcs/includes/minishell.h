/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayafdel <ayafdel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 15:55:14 by mouassit          #+#    #+#             */
/*   Updated: 2021/11/20 10:57:04 by ayafdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../../libraries/libft/libft.h"
# include <fcntl.h>


typedef struct s_envp{
	char    *key;
	char    *value;
	int     equal;
	struct s_envp *next;
}   t_envp;



typedef struct s_initialisation
{
	int	i;
	int	t;
	int	len;
	int	sword;
}				t_initial;

typedef		struct s_tokens{
	char	*value;
	int		type;
	struct s_tokens *next;
}		t_tokens;

typedef		struct s_test{
	int		a;
	int		b;
}		t_test;

typedef		struct s_list{
	char	*value;
	struct s_list *next;
}		t_list;

typedef		struct s_init{
	int type;
	char *token_word;
	char *value;
	int len;
	int close;
	int i;
	int len_dollar;
	char *dollar;
	char *token;
}		t_init;

typedef		struct s_redirection{
	char	*file_name;
	int		type;
	struct s_redirection *next;
}			t_redirection;

typedef		struct s_data{
	char	**arguments;
	int		nb_heredoc;
	t_redirection *redirection;
	struct s_data *next;
}		t_data;

typedef		struct s_args{
	char	*arguments;
	struct	s_args *next;
}			t_args;

//exec
void	ft_builtins(t_data *data, t_envp **env_list);
int		is_builtin(char *cmd);
int		exec_cmd(t_data *data, char **envp);
void	ft_cd(t_data *data);
void	ft_pwd();
void    ft_env(t_data *data, t_envp **var);
int		ft_echo(t_data *data);
void	ft_export(t_data *data, t_envp **env_list);
void	add_str_to_node(t_envp **head, char *str);
void	add_to_env(t_envp **head, t_envp *node);
t_envp* fill_envp(char *str);
int     env_key_error(char *var);
void	ft_unset(char **args, t_envp **env_list);
void    free_envp(t_envp *env);
int		fetch_fd(t_redirection *red, int **fd);
void	ft_exit();





//parsing

/*
	| : 1;
	> : 2;
	>> : 3;
	< : 4;
	<< : 5;
	word : 6;
*/

void    parsing(char *cmd, int *error,t_envp *env_list, t_data **data);
int    list_tokens(t_list **head, char *data);
int    check_tokens(t_list *head, int error,t_envp *env_list, t_data **dt);
int     fill_data(t_tokens *tokens, t_data **data);
int		delimiter(char *value, int *start);

#endif