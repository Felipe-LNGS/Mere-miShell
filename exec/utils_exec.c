/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:21:24 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/16 15:34:31 by plangloi         ###   ########.fr       */
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

int count_env_vars(t_env *env)
{
    int count = 0;
    t_env *tmp = env;

    while (tmp)
    {
        count++;
        tmp = tmp->next;
    }

    return count;
}

char **allocate_env_array(int count)
{
    char **env_array = malloc((count + 1) * sizeof(char *));
    if (!env_array)
        return NULL;
    return env_array;
}

char *create_env_entry(char *key, char *value)
{
    size_t len = strlen(key) + strlen(value) + 2; // Pour '=' et '\0'
    char *entry = malloc(len);
    if (entry)
        snprintf(entry, len, "%s=%s", key, value);
    return entry;
}

int fill_env_array(t_env *env, char **env_array)
{
    t_env *tmp = env;
    int i = 0;

    while (tmp)
    {
        env_array[i] = create_env_entry(tmp->key, tmp->value);
        if (!env_array[i])
        {
            for (int j = 0; j < i; j++)
                free(env_array[j]);
            return -1;
        }
        tmp = tmp->next;
        i++;
    }
    env_array[i] = NULL; // Le dernier élément doit être NULL

    return 0;
}

char **convert_env_to_array(t_env *env)
{
    int count = count_env_vars(env);
    char **env_array = allocate_env_array(count);

    if (!env_array)
        return NULL;

    if (fill_env_array(env, env_array) == -1)
    {
        free(env_array);
        return NULL;
    }

    return env_array;
}


int	get_cmds(t_env *env, t_cmds *cmds)
{
char **env_array = convert_env_to_array(env);	// if (!cmds->tab[0])
	// 	return (ft_cmd_no_found(&cmds->tab[0]), exit(EXIT_FAILURE), 1);
	if (ft_strchr(cmds->tab[0], '/') != NULL && access(cmds->tab[0],
			F_OK | X_OK) == 0)
		cmds->path = ft_strdup(cmds->tab[0]);
	else
	{
		cmds->path = get_path(env, cmds);
		if (!cmds->path)
		{
			ft_cmd_no_found(cmds->tab[0]);
			return (exit(EXIT_FAILURE), 1);
		}
	}
	// printf("cmds->tab %s\n", cmds->tab[0]);
	
	if (execve(cmds->path, cmds->tab, env_array) == -1)
	{
		ft_cmd_no_found(cmds->tab[0]);
		return (free(cmds->path), exit(EXIT_FAILURE), 1);
	}
	return (EXIT_SUCCESS);
}

static void	child_wtermsig(int sig)
{
	int g_return ;
	if (sig == 2)
	{
		write(1, "\n", 1);
		g_return = 130;
	}
	if (sig == 3)
	{
		write(1, "Quit: 3\n", 8);
		g_return = 131;
	}
}

void	wait_child(t_shell *shell)
{
	int		stat;
	t_cmds	*snake;

	int g_return ;
	snake = shell->cmds;
	while (snake)
	{
		if (snake->pid != -2 && snake->pid != -1)
		{
			waitpid(snake->pid, &stat, 0);
			if (WIFSIGNALED(stat))
				child_wtermsig(WTERMSIG(stat));
			else if (WIFEXITED(stat))
				g_return = WEXITSTATUS(stat);
		}
		snake = snake->next;
	}
}

void	close_all_fds(t_fd *fds)
{
	if (!(fds->pipes[0] == -2) && fds->pipes[0] >= 0)
		close(fds->pipes[1]);
	if (!(fds->pipes[1] == -2) && fds->pipes[1] >= 0)
		close(fds->pipes[1]);
	if (!(fds->redir[0] == -2) && fds->redir[0] >= 0)
		close(fds->redir[0]);
	if (!(fds->redir[1] == -2) && fds->redir[1] >= 0)
		close(fds->redir[1]);
	if (!(fds->output == -2) && fds->output >= 0)
		close(fds->output);
	if (!(fds->input == -2) && fds->input >= 0)
		close(fds->input);
}