/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokuno <sokuno@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:31:29 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/21 12:17:01 by sokuno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <stdbool.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>

typedef enum e_token_kind {
	WORD,
	RESERVED,
	OPERATOR,
	END
}	t_token_kind;

typedef struct s_token {
	char			*word;
	t_token_kind	kind;
	struct s_token	*next;
}	t_token;

typedef enum e_node_kind {
	SIMPLE_CMD,
	REDIR_OUT,
	REDIR_IN,
	REDIR_APPEND,
	REDIR_HEREDOC,
}	t_node_kind;

typedef struct s_node {
	t_node_kind		kind;
	struct s_node	*next;
	t_token			*command;
	struct s_node	*redirect;
	t_token			*filename;
	int				filefd;
	int				targetfd;
	int				stashed_targetfd;
	bool			should_expand;
	bool			can_redirect;
	t_token			*delimiter;
	int				inpipe[2];
	int				outpipe[2];
}	t_node;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}				t_env;

typedef struct s_minishell
{
	int		exit_status;
	int		signal;
	bool	should_heredoc_stop;
}	t_minishell;

extern t_minishell	g_minishell;

# define SUCCESS 0
# define ERROR 1
# define USAGE_ERROR 2
# define FILE_ERROR 126
# define COMMAND_ERROR 127
# define TOKENIZE_ERROR 258
# define PARSE_ERROR 258
# define SYNTAX_ERROR 258
# define READ 0
# define WRITE 1

//tokenizer
t_token	*tokenize(char *line, bool *syntax_error);
t_token	*token_last(t_token *lst);
t_token	*new_token(char	*word, t_token_kind kind);
void	token_add_back(t_token **lst, t_token *new);
char	**init_operators(void);
bool	is_metacharacter(char c);
bool	is_operator(const char *s);
bool	is_brank(char c);
char	**tokens_to_argv(t_token *token);
void	print_argv(char **argv);
//parser
t_node	*parse(t_token *token, bool *syntax_error);
t_node	*node_last(t_node *lst);
t_node	*new_node(char	*word, t_node_kind kind);
void	node_add_back(t_node **lst, t_node *new);
bool	is_same_operator(t_token *token, char *operator);
bool	is_command(t_token *token);
//expansion
void	expand(t_env *env, t_node *node);
void	expand_variables(t_env *env, t_node *node);
void	remove_quote(t_token *token);
int		append_char(char **dest, char src);
int		expand_variable(t_env *env, char **new_word, char *word);
int		expand_single_quote(char **new_word, char *word);
int		expand_double_quote(t_env *env, char **new_word, char *word);
int		expand_statuscode(char **new_word);
char	*expand_heredoc(t_env *env, char *line);
bool	is_variable(char *str);
bool	is_dollar_quote(char *str);
bool	is_statuscode(char *str);
bool	is_alpha_under(char c);
bool	is_alpha_under_digit(char c);
//error
void	fatal_error(char *message);
void	builtin_error(char *command, char *arg, char *message);
void	standard_error(char *message);
void	file_error(char *file, char *message);
void	command_error(char *file, char *message);
void	parser_error(char *word, bool *syntax_error);
void	assert_error(char *message);
void	exit_error(char *arg, char *message);
void	usage_error(char *file, char *message);
int		tokenizer_error(char *message, char *line, bool *syntax_error);
//print_error
ssize_t	ft_putchar_stderr(char c);
ssize_t	ft_putstr_stderr(char *s);
ssize_t	ft_putnbr_stderr(int n);
ssize_t	ft_nbrdigits(int nbr, int n);
ssize_t	utoa_stderr(unsigned long nbr, unsigned long n, char *asc);
ssize_t	ft_putvoid_stderr(void *s);
int		print_error(const char *format, ...);
//execute
pid_t	execute_command(t_env **env, t_node *node);
void	execute(t_env **env, t_node *node);
char	*search_path(char *line, char **environ);
int		wait_pipe(pid_t last_pid);
void	validate_path(char **environ, char **argv, char *path);
bool	is_execrable(char *path);
bool	exists_file(char *path);
bool	is_file(char *path);
bool	is_directory(char *path);
//redirect
int		stash_fd(int fd);
int		open_redirect_file(t_env *env, t_node *redirect);
void	do_redirect(t_node *redirect);
void	reset_redirect(t_node *redirect);
int		read_heredoc(t_env *env, t_node *redirect);
bool	is_redirect(t_node_kind kind);
bool	is_heredoc(t_node_kind kind);
bool	validate_redirect(t_node *node);
//free
void	free_token(t_token *token);
void	free_redirect(t_node *redirect);
void	free_node(t_node *node);
bool	exists_file(char *path);
//env
t_env	*new_env(char *name, char *value);
void	envadd_back(t_env **env, t_env *new);
char	*get_env_value(t_env *env, char *name);
void	init_env(t_env **env);
int		envsize(t_env *env);
char	**get_environ(t_env *env);
//delete_env
void	delete_env(t_env **env, char *arg);
void	delete_all_env(t_env **env);
//update_env
void	update_env(t_env **env, char *arg);
void	set_env(t_env **env, char *name, char *value);
bool	exists_env(t_env **env, char *arg);
//free_env
void	free_env(t_env *env);
//builtin
bool	is_builtin(t_node *node);
int		execute_builtin(t_env **env, t_node *node);
int		builtin_echo(char **argv);
int		builtin_pwd(void);
int		builtin_exit(char **argv);
int		builtin_env(t_env *env);
int		builtin_export(t_env **env, char **argv);
int		builtin_unset(t_env **env, char **argv);
int		builtin_cd(t_env **env, char **argv);
//signal
void	set_sigactions(void);
void	reset_sigactions(void);
//pipe
void	setup_pipe(t_node *node);
void	setup_pipe_child(t_node *node);
void	setup_pipe_parent(t_node *node);
//utils
void	*try_calloc(size_t count, size_t size);
char	*try_strdup(const char *str);
char	*try_strndup(const char *src, size_t n);
void	print_command(t_node *node);
void	print_redirects(t_node *redirect);
void	print_file_and_delimiter(t_node *node);
void	print_argv(char **argv);
void	print_tokens(t_token *token);

#endif
