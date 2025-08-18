/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:20:32 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/18 13:40:50 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include "ft_parse.h"
#include "ft_pipe.h"
#include "ft_printf.h"
#include "ft_utils.h"
#include "ft_validate.h"
#include "libft.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void ft_close_pipe(t_list *cmds)
{
	t_pipe	*pp;
	t_list	*cur;

	cur = cmds;
	while (cur)
	{
		pp = cur->content;
		if (pp->fd_inline != -1)
			close(pp->fd_inline);
		if (pp->fd_outline != -1)
			close(pp->fd_outline);
		cur = cur->next;
	}
}

void	ft_run_fort(t_list* head, t_pipe *cur_process, char **envp)
{
	int	pid;
	int ex;

	pid = fork();
	// ft_printf("cmd: %s\n", cur_process->cmdname);
	if (pid == 0)
	{
		if (!cur_process->to_exec)
			exit(0);
		if(cur_process->fd_inline == -1)
		{
			ft_close_pipe(head);
			exit(0);
		}
		else
			dup2(cur_process->fd_inline, STDIN_FILENO);
		dup2(cur_process->fd_outline, STDOUT_FILENO);
		cur_process->fd_inline = -1;
		cur_process->fd_outline = -1;
		ft_close_pipe(head);
		ex = execve(cur_process->cmdname, cur_process->args, envp);
		if (ex == -1)
		{
			ft_printf_fd(STDERR_FILENO, "%s: %s\n",
				cur_process->args[0], strerror(errno));
			exit(2);
		}
	}
	close(cur_process->fd_inline);
	close(cur_process->fd_outline);
	cur_process->pid = pid;
}

void	ft_wait_to(t_list *cmds)
{
	t_pipe	*cur_process;
	int status;

	while (cmds)
	{
		cur_process = cmds->content;
		if (cur_process->pid > 0)
			waitpid(cur_process->pid, &status, 0);
		if (cmds->next)
		{
			cmds = cmds->next;
			continue;
		}
		if (cur_process->fd_inline > 0 && WIFEXITED(status))
			if (WEXITSTATUS(status))
				exit(WEXITSTATUS(status));
		cmds = cmds->next;
	}
}

void ft_set_pipes(t_list *cmd)
{
	int fd[2];
	t_pipe *pp;
	t_list *next;
	t_list *cur;

	cur = cmd;
	next = cur->next;
	while (next)
	{
		if (pipe(fd) == -1)
		{
			ft_printf_fd(STDERR_FILENO, "Error creating pipe: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		pp = cur->content;
		pp->fd_outline = fd[1];
		pp = next->content;
		pp->fd_inline = fd[0];
		cur = next;
		next = next->next;
	}
}

int	ft_run(t_list *cmds, int fd_inline, int fd_outline, char **envp)
{
	t_pipe	*pp;
	t_list	*head;
	
	head = cmds;
	pp = cmds->content;
	pp->fd_inline = fd_inline;
	pp = ft_lstlast(cmds)->content;
	pp->fd_outline = fd_outline;

	ft_set_pipes(cmds);
	while (cmds)
	{
		pp = cmds->content;
		ft_run_fort(head, pp, envp);
		cmds = cmds->next;
	}
	ft_wait_to(head);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*cmds;
	int		fd_in;
	int		fd_out;

	if (argc < 5)
		return (EXIT_FAILURE);
	fd_in = open(argv[1], O_RDONLY);
	if (fd_in == -1)
	{
		ft_printf_fd(STDERR_FILENO, "pipex: %s: %s\n",
			argv[1], strerror(errno));
	}
	if (access(argv[argc - 1], F_OK) == 0)
	{
		if ( access(argv[argc - 1], W_OK) != 0)
		{ft_printf_fd(STDERR_FILENO, "pipex: %s: %s\n",
			argv[argc - 1], strerror(errno));
		close(fd_in);
		return (1);}
	}
	fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		ft_printf_fd(STDERR_FILENO, "Error opening output file (%s): %s\n",
			argv[argc - 1], strerror(errno));
		close(fd_in);
		return (127);
	}
	cmds = ft_parse_args(argc - 3, argv + 2);
	if (!cmds)
	{
		ft_printf_fd(STDERR_FILENO, "Error parsing arguments\n");
		return (EXIT_FAILURE);
	}
	ft_set_progname(cmds, envp);
	ft_validate_prog(cmds);
	ft_run(cmds, fd_in, fd_out, envp);
}
