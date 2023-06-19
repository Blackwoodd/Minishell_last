/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:10:07 by nbechon           #+#    #+#             */
/*   Updated: 2023/06/15 16:24:55 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <stdbool.h>
# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

# define ECHO "echo"
# define ECHO_N "echo -n"
# define CD "cd"
# define PWD "pwd"
# define EXIT "exit"
# define ENV "env"
# define EXPORT "export"
# define UNSET "unset"

# define EXIT_SYNTAX_ERROR 258
# define EXIT_CMD_NOT_FOUND 127
# define EXIT_CTRL_D 130
# define EXIT_BREAK 3

# define NB_ITER 5

typedef enum e_parser_tok_type
{
	std = 0,
	subshell = 1,
	and = 2,
	or = 3,
}	t_par_tok_type;

typedef enum e_pars_redir_type
{
	is_pipe = 0,
	is_in = 1,
	is_in_heredoc = 2,
	is_out = 3,
	is_out_append = 4,
}	t_redir_type;

typedef struct s_parser_tok
{
	t_par_tok_type	type;
	t_redir_type	redir_type[5];
	char			**cmd;
	size_t			cmd_size;
	char			**in;
	size_t			in_size;
	char			**out;
	size_t			out_size;
}	t_par_tok;

typedef struct s_env
{
	char	**envp;
	char	**env_var;
	char	*pwd;
	char	*oldpwd;
}			t_env;

typedef enum e_iterator
{
	lex = 0,
	par = 1,
	cmd = 2,
	in = 3,
	out = 4,
}	t_iter;

typedef struct s_expander_tokens
{
	char			**cmd;
	int				in;
	int				out;
	bool			is_pipe;
}	t_exp_tok;

//////////////////// strucure-quote  //////////////

typedef struct s_quote
{
	int		i;
	int		j;
	int		len;
	char	*start;
	char	*end;
	char	*quote;
}	t_quote;

//////////////////// structure-token //////////////

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

//////////////////// signal.c /////////////////////

void		signal_crtl(void);

//////////////////// commandes.c //////////////////

int			commande_echo(char **word);
int			commande_pwd(char **word);
int			commande_cd(char **word);

//////////////// commandes2.c //////////////////

int			commande_env(char **env);
int			commande_export(char **env);
int			commande_unset(char **tab);
int			commande_exit(char **tab);

//////////// verif_synthax.c ////////////////////

int			exit_syntax_error(void);
bool		valid_synthax_str(char	*rline);

//////////////// get_token_utils.c ///////////////

bool		verif_is_token(char *token);

///////////////	join_quotes.c ///////////////////

int			join_quote(char ***token);

/////////////// sub_token_utils.c ////////////////

int			get_subtoken_count(char *token[], int i);
char		*get_end_subtoken(char *token[], int *i, char *sub_token);

//////////////// utils_jquote.c ///////////////////

int			token_join_all(char ***token, t_quote *quote, int i);

/////////////// utils_jquote_bis.c ////////////////

int			combine_loop(char ***token, t_quote *quote);
int			token_join_end_one(char ***token, t_quote *quote);

///////////////// utils_token.c //////////////////

bool		token_is_right(char *token);
char		get_next_special(char *token);
size_t		get_token_size(char *token, char next_spe);

////////////// check_token_synthax,c /////////////

bool		valid_syntax_token(char	*token[]);

///////////////// error.c //////////////////////

void		set_err_code(int err_code);
int			get_err_code(void);

/////////////// utils_env_var.c ///////////////

char		*get_env_var_val(t_env *envar, char *var);
t_env		*init_envar(char **envp);
void		free_envar(t_env *envar);

////////////////// set_envar.c ////////////////

void		set_envar(t_env *envar);
t_env		*get_envar(void);
char		**get_env_var(void);

///////////////// get_iter.c //////////////////

t_iter		*get_iter(void);
void		set_iter(t_iter *iter);
void		reset_iter(void);

///////////////// parser_utils.c////////////////

int			init_current_pars_token(void);
int			free_pars_token(t_par_tok *pars_token[], int exit_code);
int			free_parser(t_par_tok *pars_token[], t_iter *iter, int exit_status);
size_t		get_stoken_size(char *lex_token[]);

/////////////// get_lex_set.c //////////////////

char		**get_lex_token(char **lex_toks, bool reset);
void		reset_lex_token(void);
void		set_lex_token(char **lex_toks);
char		**get_lexic_token(void);
char		*get_current_lex_token(void);

///////////////////// get_pars_token_utils.c  ///////////

int			set_tok_type_pipe(t_par_tok *pars_token, t_iter *iter);
int			get_subshell_token(t_iter *iter);
bool		is_token_redir(char *token);
bool		is_spe_token(char *token);
bool		is_token_quote(char *token);

//////////////////// token_redir_utils.c  //////////////

int			get_token_redir_type(char *token);
bool		try_get_token_redir_buff(char ****buff, size_t **buff_size,
				t_iter **buff_iter);

///////////////////// get_directory.c //////////////////

char		*get_directory_items(void);

///////////////////	get_token /////////////////////

int			get_token_cmd(char *token, t_par_tok *par_tok, t_iter *iter);
int			get_token_redir(char *lex_token[], t_iter *iter);
int			get_special_token(char *token, t_par_tok *par_toks[], t_iter *iter);
int			get_token_type(char *token, t_iter *iter);

//////////////////// interprete_env_var.c ////////////

char		*get_env_variable(char *lex_tok, char *var);
char		*get_var(char *lex_tok);
char		*interpret_env_var(char *lex_token);

///////////////////// get_pars_token.c ////////////////////

t_par_tok	**get_pars_token(void);
t_par_tok	*get_current_par_token(void);
void		set_pars_token(t_par_tok **pars_token);
void		reset_pars_token(void);

///////////////////// lexer.c ///////////////////////////

void		*ft_free_tab(char **tab);
char		**resize_token(char **token);
int			lexer(char *rline);

////////////////////// expander_utils.c ////////////////

int			free_exp_toks(t_exp_tok *exp_toks[], int exit_status);
int			get_tokens(t_par_tok *par_toks[]);
int			reinterprete_env_vars(t_par_tok *par_toks[], t_exp_tok *exp_toks[]);

//////////////////// ft_execute.c  ///////////////////

int			clean_quote_exp_tok_cmd(t_exp_tok *exp_tok);
bool		is_builtin(char *cmd);
int			init_path(char **path_splitted[]);
char		*get_abs_cmd_path(char *path_splitted, char *cmd);
int			ft_execute(t_exp_tok *exp_tok);

///////////////// parser.c //////////////////////////

int			parser(char *lexer_token[]);

/////////////////// exp_tok_utils.c /////////////////

t_exp_tok	**get_exp_toks(void);
void		set_exp_toks(t_exp_tok *exp_tok[]);
void		reset_exp_toks(void);

//////////////////// here_doc_utils.c ////////////////

int			wait_for_heredoc(t_par_tok *par_tok, t_exp_tok *exp_tok,
				char *buff, char *heredoc);

///////////////////// signal.c ////////////////////

void		cmd_signal(void);
void		global_signal(void);

////////////////// ft_execute_utils_bis.c ///////////

int			execute_child(t_exp_tok *exp_tok, char *abs_cmd_path, int status);
int			execute_builtin(t_exp_tok *exp_tok);
int			execute_builtin_child(t_exp_tok *exp_tok);
int			exbuiltin_reset_fd(t_exp_tok *exp_tok, int pipes_save[2]);

//////////////// ft_execute_utils.c ////////////////

int			handle_builtin_redirection(t_exp_tok *exp_tok);

////////////////// handle_pipe.c //////////////////

int			handle_pipes(t_exp_tok *exp_tok, int pipe_type);

//////////////// expander.c//////////////////////

int			execute_subshell(t_exp_tok *exp_tok);
int			expander(t_par_tok *pars_token[]);

////////////////// handle_redirection.c //////////

int			handle_redir(t_par_tok *par_tok, t_exp_tok *exp_tok, int pipe_type);

////////////////// exit.c /////////////////////

int			exit_builtin(char *args[]);

/////////////////// set_envp /////////////////

void		set_envp(char **envp);

///////////////////////////////////////////////

int			set_pipe_type(t_par_tok **par_toks, int i);

#endif