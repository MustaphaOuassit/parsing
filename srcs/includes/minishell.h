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

typedef		struct s_args{
	char	*arguments;
	struct	s_args *next;
}			t_args;

typedef		struct s_redirection{
	char	*file_name;
	int		type;
	struct s_redirection *next;
}			t_redirection;

typedef		struct s_init{
	int type;
	char *token_word;
	char *value;
	char **arguments;
	int len;
	int close;
	int i;
	int j;
	int	end;
	int	tmp;
	int len_dollar;
	int	redirection;
	char *dollar;
	char **filter;
	char *vtmp;
	char *check_error;
	char *token;
	char *file_name;
	int start;
	int check;
	int	nb_heredoc;
	int error;
	char **split;
	int nb;
	int pipe;
	char *exp;
	char *env;
	t_args *args;
	t_redirection *rdt;
    t_list *head;
}		t_init;


typedef		struct s_data{
	char	**arguments;
	int		nb_heredoc;
	t_redirection *redirection;
	struct s_data *next;
}		t_data;


typedef		struct s_ambiguous{
	char	*value;
	struct s_ambiguous *next;
}		t_ambiguous;

typedef		struct s_free{
	void	*value;
	char	**table;
	struct s_free *next;
}		t_free;
typedef struct s_envp{
	char    *key;
	char    *value;
	int     equal;
	int		type;
	char	*file_name;
	int		exit_status;
	int		nb_herdoc;
	t_free		*allocation;
	t_ambiguous *ambiguous;
	struct s_envp *next;
}   t_envp;

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
	<< expand : 8
	function expand : expand_value();
*/

int    parsing(char *cmd, int *error,t_envp *env_list, t_data **data);
int    list_tokens(t_list **head, char *data, t_envp *env_list);
int    check_tokens(t_list *head, int error,t_envp *env_list, t_data **dt);
int     fill_data(t_tokens *tokens, t_data **data, t_envp *env_list);
int		delimiter(char *value, int *start);
int		delimiter_skip(char *value, int *start);
int		is_space(char *value);
int		free_in_parcer(t_free **head, void *value, char	**table);
void	free_two(char **table);
void	file_double(char *value, int *i, int *len, char *file_name);
void	file_single(char *value, int *i, int *len, char *file_name);
void	skip_content_value(char *value, int *i, int *len, int ele);
char	*expand_value(char *value, t_envp *env_list);
char	*fill_dollar_one(char *value,t_envp *env_list);









 
#endif