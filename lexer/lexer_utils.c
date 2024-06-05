/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:51:21 by plangloi          #+#    #+#             */
/*   Updated: 2024/06/05 16:48:58 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int find_tokken(char *input, int i)
{
	while (input[i])
	{
		if (input[i] == '|')
			return (PIPE);
		if(input[i] =='<')
		{
			if (input[i+1] == '<')
				return (i++, HERE_DOC);
			else
				return(IN_REDIR);
		}
		if (input[i] == '>')
		{
			if (input[i+1] == '>')
				return (i++, APPEND);
			else
				return(OUT_REDIR);
		}
		i++;
	}
return(false);
}

int quote_de_porc(char input)
{
	if(input== '\'')
		return(1);
	else if (input == '\"')
		return(2);
	else 
		return(0);
}
