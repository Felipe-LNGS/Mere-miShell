/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:53:16 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/22 16:38:48 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void free_before_loop(t_cmds **cmds)
{
	if (cmds && *cmds)
		free_cmds(cmds);
}

void exit_and_free(t_shell *shell, char *str, int sig)
{
    if (str)
        perror(str);
    if (shell)
        free_shell(shell);
    exit(sig);
}