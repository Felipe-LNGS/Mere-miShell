/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmerveil <lmerveil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 11:05:00 by felipe            #+#    #+#             */
/*   Updated: 2024/08/01 10:23:16 by lmerveil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Fonction pour verifier si la chaîne représente un nombre valide avec signe
static int	is_valid_number(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

// Fonction pour gerer les arguments de exit
static int	exit_args(char **tab, int *flag)
{
	if (!tab[1])
	{
		return (0);
	}
	if (!is_valid_number(tab[1]))
	{
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(tab[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		*flag = 1;
		return (2);
	}
	if (tab[2])
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		*flag = 1;
		return (1);
	}
	return (ft_atoi(tab[1]) % 256);
}

void	ft_exit(t_shell *shell, t_cmds *cmd, t_fd *fd)
{
	int	flag;
	int	ext;

	flag = 0;
	ext = exit_args(cmd->tab, &flag);
	if (cmd->tab[1] && cmd->tab[2] && !flag)
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return ;
	}
	if (cmd->next || cmd->prev)
		return ;
	ft_freeshell(shell);
	close_all_fds(fd);
	exit(ext);
}
