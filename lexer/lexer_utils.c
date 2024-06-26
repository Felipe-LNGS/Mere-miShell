/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:51:21 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/01 14:51:38 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// // si token trouve dans input, return sa valeur associee, sinon return false
// int find_token(char *input, int i)
// {
// 	while (input[i])
// 	{
// 		if (input[i] == '|')
// 			return (PIPE);
// 		if(input[i] =='<')
// 		{
// 			if (input[i+1] == '<')
// 				return (i++, HERE_DOC);
// 			else
// 				return(IN_REDIR);
// 		}
// 		if (input[i] == '>')
// 		{
// 			if (input[i+1] == '>')
// 				return (i++, APPEND);
// 			else
// 				return(OUT_REDIR);
// 		}
// 		i++;
// 	}
// return(FALSE);
// }

// si token trouve dans input[i], return sa valeur associee, sinon return false
int	is_token(char *input, int *i)
{
	if (input[*i] == '|')
		return (PIPE);
	if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
			return ((*i)++, HERE_DOC);
		else
			return (IN_REDIR);
	}
	if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
			return ((*i)++, APPEND);
		else
			return (OUT_REDIR);
	}
	return (FALSE);
}
int	which_redir(char *input, int *i)
{
	if (input[*i] == '|' || input[*i] == '<' || input[*i] == '>')
		return (TRUE);
	return (FALSE);
}
// verifie si input[i] est un guillmet
int	which_quote(char input)
{
	if (!input)
		return (0);
	if (input == '\'')
		return (1);
	else if (input == '\"')
		return (2);
	else
		return (0);
}

void	add_node(t_env **env, char *value)
{
	t_env	*newnode;
	t_env	*last;

	newnode = malloc(sizeof(t_env));
	if (!newnode)
		return ;
	newnode->value = value;
	newnode->prev = NULL;
	newnode->next = NULL;
	if (*env == NULL)
	{
		*env = newnode;
		return ;
	}
	last = *env;
	while (last->next)
		last = last->next;
	last->next = newnode;
	newnode->prev = last;
}
