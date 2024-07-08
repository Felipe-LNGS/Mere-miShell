/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:17:49 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/08 17:58:04 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	child_looping(int fd_tmp, t_fd *fd, t_cmds *cmds, t_env *envp)
{
	fd_tmp = fd->pipes[0];
	if (pipe(fd->pipes) == -1)
		return (close_fd(fd->pipes[0], fd_tmp, 3), exit(EXIT_FAILURE), 1);
	cmds->pid = fork();
	if (cmds == -1)
		return (close_fd(fd->pipes, fd_tmp, 3), exit(EXIT_FAILURE), 1);
	else if (cmds->pid == 0)
	{
		if (dup2(fd_tmp, STDIN_FILENO) == -1 || dup2(fd->pipes[1],
				STDOUT_FILENO) == -1)
			return (perror("dup2"), close_fd(fd->pipes, fd_tmp, 3),
				exit(EXIT_FAILURE), 1);
		close_fd(fd->pipes, fd_tmp, 3);
		// get_cmds(envp, av);
	}
	close_fd(fd->pipes, fd_tmp, 1);
	return (0);
}

int	first_child(t_cmds *cmds, t_fd *fd, t_env *envp)
{
	if (pipe(fd) == -1)
		return (close(fd->pipes[0]), close(fd->pipes[1]), exit(EXIT_FAILURE),
			1);
	cmds->pid = fork();
	if (cmds->pid == -1)
		return (close(fd->pipes[0]), close(fd->pipes[1]), exit(EXIT_FAILURE),
			1);
	if (cmds->pid == 0)
	{
		fd->input = open(cmds->lex_redir->word, O_RDONLY, 0644);
		if (fd->input == -1)
			return (perror(cmds->lex_redir->word), close_fd(fd, fd->input, 2),
				exit(EXIT_FAILURE), 1);
		if (dup2(fd->input, STDIN_FILENO) == -1 || dup2(fd->pipes[1],
				STDOUT_FILENO) == -1)
			return (perror("dup2"), close_fd(fd, fd->input, 3),
				exit(EXIT_FAILURE), 1);
		close_fd(fd, fd->input, 3);
		// get_cmds(envp, av[2]);
	}
	return (close(fd->piint		last_child(char **av, int argc, int *fd, char **envp);
pes[1]), 1);
}

int	last_child(t_cmds *cmds, t_fd *fd, t_env *envp)
{
	t_cmds	*tmp;

	cmds->pid = fork();
	if (cmds->pid == -1)
		return (exit(EXIT_FAILURE), 1);
	if (cmds->pid == 0)
	{
		tmp = cmds;
		while (tmp)
			tmp = tmp->next;
		if (tmp->lex_redir->token == HERE_DOC)
			fd->output = open(tmp->lex_redir->word, O_WRONLY | O_CREAT | O_APPEND,
					0644);
		else if (tmp->lex_redir->token == OUT_REDIR)
			fd->output = open(tmp->lex_redir->word, O_WRONLY | O_CREAT | O_TRUNC,
					0644);
		if (fd->output == -1)
		{
			return (perror(tmp->lex_redir->word), close_fd(fd->pipes, fd->output,
					2), exit(EXIT_FAILURE), 1);
		}
		if (dup2(fd->output, STDOUT_FILENO) == -1 || dup2(fd->pipes[0],
				STDIN_FILENO) == -1)
			first_child(cmds, fd->pipes, envp);
		return (perror("dup2"), exit(EXIT_FAILURE), 1);
		close_fd(fd->pipes, fd->output, 3);
		// get_cmds(envp, av[ac - 2]);
	}
	return (0);
}int		last_child(char **av, int argc, int *fd, char **envp);


void	loop_here_doc(t_cmds *cmds, t_fd *fd)
{
	char	*line;
	char	*limiter;

	limiter = ft_strjoin(cmds->lex_redir->next->word, "\n");
	while (1)
	{
		line = readline("> ");
		if (line == NULL || ft_strncmp(line, limiter, ft_strlen(line)) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd->output);
		free(line);
	}
	free(limiter);
}

t_fd	*here_doc(t_cmds *cmds)
{
	char	*file_name;
	t_fd	*fd;
	int		tmp;

	file_name = ft_strdup("42");
	while (access(file_name, F_OK) == 0)
		file_name = ft_strjoinandfree(file_name, "42");
	tmp = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd->input == -1)
	{
		perror("infile");
		exit(EXIT_FAILURE);
	}
	fd->input = open(file_name, O_RDONLY);
	if (fd->pipes[0] == -1)
	{
		perror("fd");
		exit(EXIT_FAILURE);
	}
	unlink(file_name);
	loop_here_doc(cmds, tmp);
	free(file_name);
	close(fd->input);
	return (fd);
}
