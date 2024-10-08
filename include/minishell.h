/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:12:08 by plangloi          #+#    #+#             */
/*   Updated: 2024/09/02 15:24:40 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../.libft/libft.h"
# include "exec.h"
# include "lexer.h"
# include "parser.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/stat.h>
# define PROMPT_LINE "\001\x1b[38;2;0;255;0m\x1b[1m\002➜ \001\x1b[0m\002"

extern int	g_signal;

typedef struct s_shell
{
	char	*av;
	int		exit_code;
	int		tmpexit_code;
	int		skip_here;
	t_cmds	*cmds;
	t_env	*env;
	t_lexer	*lex;
	int		flag;

}			t_shell;

/*-------------------BUILTINS-------------------*/
void		ft_echo(t_shell *shell, t_cmds *cmd, int fd_output, t_fd *fds);
void		run_builtins(t_shell *shell, t_cmds *cmds, t_fd *fds);
void		ft_pwd(t_cmds *cmds, t_shell *shell, int fd_output, t_fd *fds);
void		ft_cd(t_shell *shell, t_cmds *cmds);
void		ft_unset_builtin(t_shell *shell, t_cmds *cmds);
void		ft_exit(t_shell *shell, t_cmds *cmd, t_fd *fd);
void		ft_env(t_shell *shell, t_cmds *cmd, int fd_output, t_fd *fds);
void		ft_export(t_env **env, t_cmds *cmds, t_shell *shell);
void		print_error(char *str);
void		print_sorted_env(t_env *env, t_shell *shell, int count);
void		add_or_update_env(t_env **env, const char *key, const char *value);
int			is_valid_identifier(const char *str);
bool		process_arg(t_env **env, char *arg, char *next_arg);

/*--------------------LEXER--------------------*/
void		lex_str(char *input, t_lexer **lex, t_shell *shell);
void		store_token(t_lexer **lex, int token, t_shell *shell);
void		store_token_words(char *input, t_lexer **lex, int len,
				t_shell *shell);
t_lexer		*lexer(t_shell *shell);
char		*remove_quotes(char *str, t_shell *shell);
t_cmds		*create_cmds(t_lexer *lex, t_shell *shell);
t_lexer		*lex_to_cmds(t_lexer *lex, t_cmds **cmds, t_shell *shell);

/*--------------------PARSER--------------------*/
int			parser(t_lexer *lex, t_shell *shell);
char		*expand(char *input, int i, t_shell *shell);
t_cmds		*init_cmds(t_shell *shell);
int			syntaxe(t_lexer *lex);
void		tmp_is_token(t_cmds **current_cmd, t_shell *shell);

/*------------------EXPANDER------------------*/
char		*no_guillemets(char *word, int *i, t_shell *shell);
char		*expander(char *input, t_shell *shell);
char		*ft_strndup_dol(char *s);
char		*join_and_free(char *exp_w, const char *suffix, t_shell *shell);
char		*expand_join(char *word, int *i, char *exp_w, t_shell *shell);
char		*expand_variable(char *word, int *i, t_shell *shell, char *exp_w);
int			count_dols(char *word, int i);
char		*find_pwd(char *str, t_shell *shell);
char		*find_excode(char *str, t_shell *shell);
int			init_exp_checks(char *word, int i);
char		*copy_if_not_quoted(char *input, int *i, int start, char *tmp);
char		*copy_if_quoted(char *input, int *i, int opened, int start);
/*--------------------ENV--------------------*/
void		set_env_key_value(t_shell *shell, t_env *new, char **envp, int i);
void		maj_env_node(t_shell *shell, t_env *new_env_node, char **envp,
				int index);
void		get_env(t_shell *shell, char **envp);
char		*ft_readline(void);
char		*find_env(char *dest, t_env *envp);
char		**allocate_env_array(t_shell *shell, int count);
void		handle_empty_env(t_shell *shell);

/*--------------------EXEC--------------------*/
void		get_cmds(t_env *env, t_cmds *cmds, t_shell *shell);
char		*get_path(t_env *env, t_cmds *cmds);
int			here_doc(t_shell *shell, t_lexer *redirs);
void		close_all_fds(t_fd *fds);
void		close_fds_parent(t_fd *fds);
void		execute_cmd(t_shell *shell, t_cmds *cmds, t_fd *fds);
void		execute_child(t_shell *shell, t_cmds *cmds, t_fd *fds);
void		init_fd(t_fd *fd);
int			handle_input_redir(t_lexer *redirs, int fd, t_shell *shell);
int			handle_output_redir(t_lexer *redirs, t_shell *shell, int fd);
void		process_redirections(t_cmds *cmds, int *fd_in, int *fd_out,
				t_shell *shell);
void		set_fds(t_fd *fd);
void		run_exec(t_shell *shell);
void		child_builtins(t_shell *shell, t_fd *fd);
void		wait_child(t_shell *shell);
char		*create_env_entry(char *key, char *value, t_shell *shell);
int			count_env_vars(t_env *env);
void		ft_cmd_no_found(char *str);
int			is_directory(const char *path);
char		**convert_env_to_array(t_env *env, t_shell *shell);
void		find_path(t_env *env, t_cmds *cmds, t_shell *shell, t_fd *fds);

/*--------------------FREE--------------------*/
void		free_lexer(t_lexer **lex);
void		free_cmds(t_cmds **cmds);
void		free_env(t_env *env);
void		free_shell(t_shell *shell);
void		free_before_loop(t_shell *shell);
void		exit_and_free(t_shell *shell, char *str);
void		ft_freeshell(t_shell *shell);

/*--------------------SIGNALS--------------------*/
bool		check_captured_signals(t_shell *shell);
void		setup_shell_signals(void);
void		handle_heredoc_signal(int signal);
void		setup_heredoc_signals(void);
int			rl_event_dummy(void);

/*--------------------UTILS--------------------*/
void		print_env_list(t_env *env_list);
void		print_lexer(t_lexer *lexer);
void		print_list_cmds(t_shell *shell);
void		print_lexer_list(t_cmds *head);

#endif
