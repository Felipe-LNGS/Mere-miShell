/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:21:24 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/29 10:38:44 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_path(t_env *env, t_cmds *cmds)
{
	int		i;
	char	*path_found;
	char	*path;
	char	**path_env;

	while (env && ft_strnstr(env->key, "PATH", 5) == 0)
		env = env->next;
	if (!env)
		return (NULL);
	path_env = ft_split(env->value, ':');
	i = -1;
	while (path_env[++i])
	{
		path_found = ft_strjoin(path_env[i], "/");
		if (!path_found)
			return (free_split(path_env), exit(EXIT_FAILURE), NULL);
		path = ft_join_free(path_found, cmds->tab[0]);
		if (!path)
			return (free_split(path_env), free(path_found), exit(1), NULL);
		if (access(path, F_OK) == 0)
			return (free_split(path_env), path);
		free(path);
	}
	return (free_split(path_env), NULL);
}

void	ft_cmd_no_found(char *str)
{
	ft_putstr_fd("command not found : ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}

int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

void	get_cmds(t_env *env, t_cmds *cmds, t_shell *shell)
{
	char	**env_array;

	if (!cmds || !cmds->tab || !cmds->tab[0])
		exit_and_free(shell, "Error : command structure");
	env_array = convert_env_to_array(env, shell);
	if (!env_array)
	{
		exit_and_free(shell, "Error : convert environment");
	}
	if (ft_strchr(cmds->tab[0], '/') != NULL)
	{
		if (is_directory(cmds->tab[0]))
		{
			ft_putstr_fd(cmds->tab[0], STDERR_FILENO);
			ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
			free_split(env_array);
			shell->exit_code = 126;
			exit_and_free(shell, "");
		}
		else if (access(cmds->tab[0], F_OK | X_OK) == 0)
		{
			cmds->path = ft_strdup(cmds->tab[0]);
		}
	}
	else
	{
		cmds->path = get_path(env, cmds);
	}
	if (!cmds->path)
	{
		ft_cmd_no_found(cmds->tab[0]);
		free_split(env_array);
		shell->exit_code = 127;
		exit_and_free(shell, "");
	}
	execve(cmds->path, cmds->tab, env_array);
	free_split(env_array);
	shell->exit_code = 126;
	exit_and_free(shell, "execve");
}