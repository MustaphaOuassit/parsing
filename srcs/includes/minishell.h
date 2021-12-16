/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 15:55:14 by mouassit          #+#    #+#             */
/*   Updated: 2021/12/16 21:18:12 by mouassit         ###   ########.fr       */
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
int     end_str(char *cmd);
int     first_pipe(char *cmd, int start);
int    multi_couts(int *i, char *cmd,int ele);
int    middle_pipe(char *cmd, int *i);
int     skip_spaces(char *cmd);
char     *get_token(char *cmd, int *start, t_envp *envp_list);
void	initial_ex(char **token, char **token_word,int *len_dollar,char **dollar);
void	initialisation_envp(t_tokens **data, t_init *var, t_envp *env_list);
void	initialisation(int *i, int *len, char **token, char **token_word);
int		len_word(char *value, int start, t_envp *env_list);
char	*putex(int *len, char *value, int *i, t_envp *env_list);
void	put_word(t_tokens **data ,char **token_word,t_envp *env_list);
void	insert_dividers(t_tokens **data ,char *value,t_init *var, t_envp *env_list);
void	initialisation_data(t_init *var);
void	prep_data(t_init *var, t_envp *env_list,t_data **data);
int		file_error(t_init *var, t_tokens *tokens, t_envp *env_list);
char	*dollar_value(t_init *vr,int *len, int *i,t_envp *env_list);
void	file_args_double(t_init *var,char *value,char **filter,int *tmp);
void	file_double(char *value, int *i, int *len, char *file_name);
void	file_args_single(t_init *var,char *value,char **filter,int *tmp);
void	file_args_dollar(int *tmp,t_init *var, char *value, char **filter);
void	file_args_double(t_init *var,char *value,char **filter,int *tmp);
void	initialisation_args(t_init *var, char *value, t_envp *env_list);
char	**declar(int *len, int *j, int *tmp, t_envp *env_list);
char	*initial(t_init *var, t_envp *env_list, char **filter, char *value);
int		check_dollar(char *value, int start);
void	continue_len(char *dollar, t_init *var, int *start, t_envp *env_list);
void	convert_dollar(t_init *vr, int *i, int *len,t_envp *env_list);
void	continue_add(t_init *var, int *len,int *i);
char	*initialisation_token(int *len, t_envp *env_list);
char	*word_double_couts(int *i, int *len, t_init *var,t_envp *env_list);
char	*word_single_couts(int *i,int *len,t_init *var);
int		put_in_parcer(t_tokens **head, char *value, int type,t_envp *env_list);
int		check_dividers(int value, t_init *var);
char	*put_diveder(char *data, int value, t_init *var, t_envp *env_list);
void	print_error_rdt(char *value,t_envp *env_list);
int		redirection_token(t_redirection	**head,int type, char *file_name, t_envp *env_list);
char 	**filter_args(char *value,t_envp *env_list);
int		args_token(t_args	**head, char *args, t_envp *env_list);
int		redirection_value(t_tokens *tokens,t_envp *env_list,t_init *var);
char	*file_dollar(t_tokens *tokens, t_init *var, t_envp *env_list);
char	**put_data(t_init *var, t_envp *env_list);
int		all_data(t_data	**head, t_init *var,t_envp *env_list);
void	skip_value(char *value, int *start);
int		len_args(char *value ,int *start);
int		get_allocation(char *value,t_envp *env_list);
void	fill_dollar_exp(t_init *var,int tmp ,char *value, int *start);
char	*get_env(char *value, t_envp *env_list);
int		len_ambiguous(char *value, int	i);
char	*fill_ambiguous(char *value, int len, int i, t_envp *env_list);
int		fill_data_ambiguous(t_ambiguous **head, char *value,t_envp *env_list);
void	take_couts(int *start, char *value, int *i);
void	initialisation_file(t_init *var, char *value, t_envp *env_list);
char	*fill_herdoc(char *value,t_envp *env_list);
int		is_couts(char *value);
char	*skip_dollar(char *value, t_init *var,t_envp *env_list);
char	*fill_file(char *value, t_envp *env_list);
int		error_redirection(int check, t_tokens *tokens,t_envp *env_list);
void	initialisation_get(t_init *var, char *value);
void	skip_dlm(int *nb, int *len);
void	fill_space(char *value, int *i, int *len, int ele);
char	**check_len_values(char *value,int *len, int nb, t_envp *env_list);
int		allocation_expand(char *value, int *i);
char	*get_env_hrd(char *value, t_envp *env_list);
int		is_couts_hrd(char *value);
int		len_expand(char *value, t_envp *env_list);
int		check_dlm(int c);
char	*dollar_allocation(char *value, int *len, t_envp *env_list);
char	*fill_dollar_two(char *dollar, char *value, int len, t_envp *env_list);
int		len_token(char *cmd, int start);
int 	check_close(char *value, int i, int ele);
char	*initialisation_dollar(int *len_dollar, int *i, t_envp *env_list);
int		get_len(char *value);
int		len_file_name(char *value);
void	take_dollar(char *value, int *start, t_init *var,t_envp *env_list);
void	initialisation_var(int *i, int *close, char **dollar, int *len_dollar);
void	single_couts(char *value, int *start, int *i, t_envp *env_list);
char	*get_env_couts(char *value, t_envp *env_list);
int		len_couts(char *value);
 
#endif