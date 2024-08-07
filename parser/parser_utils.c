/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felipe <felipe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:49:39 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/31 17:24:29 by felipe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmds	*init_cmds(t_shell *shell)
{
	t_cmds	*cmds;

	cmds = ft_calloc(1, sizeof(t_cmds));
	if (!cmds)
		exit_and_free(shell, "Error : malloc cmds");
	ft_bzero(cmds, sizeof(t_cmds));
	return (cmds);
}

int	check_quote_closed(char *word)
{
	int	d_quote;
	int	i;
	int	s_quote;

	s_quote = 0;
	d_quote = 0;
	i = 0;
	while (word[i])
	{
		if (which_quote(word[i]) == D_QUOTE)
			d_quote++;
		if (which_quote(word[i]) == S_QUOTE)
			s_quote++;
		i++;
	}
	if (s_quote % 2 != 0 || d_quote % 2 != 0)
		return (FALSE);
	return (TRUE);
}

int	count_arg(t_lexer *lex)
{
	int	count;

	count = 1;
	while (lex && lex->next && lex->next->token == 0)
	{
		count++;
		lex = lex->next;
	}
	return (count);
}

void	syntaxe(t_lexer *lex, t_shell *shell)
{
	t_lexer	*tmp;

	tmp = lex;
	while (tmp)
	{
		if (tmp->token == PIPE && (!tmp->next || tmp->next->token == PIPE))
			exit_and_free(shell, "Error : syntax error near unexpected token");
		if (tmp->token != 0 && (!tmp->next || tmp->next->token != 0))
			exit_and_free(shell, "Error : syntax error near unexpected token");
		tmp = tmp->next;
	}
}

char	*remove_quote(char *word, int *i, t_shell *shell)
{
	int		j;
	char	*dest;

	j = 0;
	dest = ft_calloc(ft_strlen(word + 1), sizeof(char *));
	if (!dest)
		exit_and_free(shell, "Error :  malloc parser");
	while (word[*i])
	{
		if ((which_quote(word[*i]) && *i == 0) || (which_quote(word[*i])
				&& word[*i + 1] == '\0'))
			(*i)++;
		else
		{
			dest[j] = word[*i];
			j++;
			(*i)++;
		}
	}
	dest[j] = '\0';
	return (dest);
}
