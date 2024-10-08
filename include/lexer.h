/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmerveil <lmerveil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:39:48 by plangloi          #+#    #+#             */
/*   Updated: 2024/08/22 16:31:17 by lmerveil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

# define ERR_QUOTE "Error: Unmatched quotes\n"
# define FALSE 0
# define TRUE 1

# define IN_REDIR 500  // <
# define HERE_DOC 501  // <<
# define APPEND 502    // >>
# define OUT_REDIR 503 // >
# define PIPE 504      // |

# define S_QUOTE 1 // '
# define D_QUOTE 2 // "

typedef struct s_lexer
{
	int				token;
	char			*word;
	int				space;
	struct s_lexer	*next;
	struct s_lexer	*prev;
	int				skip;
}					t_lexer;

typedef struct s_env
{
	char			*value;
	char			*key;
	int				index;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

int					which_quote(char input);
int					is_token(char *input, int *i);
int					which_redir(char *input, int *i);
int					count_arg(t_lexer *lex);
void				is_word(char *input, int *i);
void				is_quoted(char *input, int *i, int *opened);

#endif
