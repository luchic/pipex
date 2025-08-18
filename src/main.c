/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:20:32 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/18 21:35:03 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_core.h"
#include "ft_parse.h"
#include "ft_printf.h"
#include "ft_settings.h"
#include "ft_validate.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	fd_open_files(int *fd_in, int *fd_out, char *input_file,
		char *output_file)
{
	*fd_in = open(input_file, O_RDONLY);
	if (*fd_in == -1)
	{
		ft_printf_fd(STDERR_FILENO, "%s: %s: %s\n", PIPEX, input_file,
			strerror(errno));
	}
	ft_validate_write_file(output_file);
	*fd_out = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd_out == -1)
	{
		ft_printf_fd(STDERR_FILENO, "%s: %s: %s\n", PIPEX, output_file,
			strerror(errno));
		close(*fd_in);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*cmds;
	int		fd_in;
	int		fd_out;

	if (argc < 5)
		return (EXIT_FAILURE);
	fd_open_files(&fd_in, &fd_out, argv[1], argv[argc - 1]);
	cmds = ft_parse_args(argc - 3, argv + 2);
	if (!cmds)
	{
		ft_printf_fd(STDERR_FILENO, "%s: %s\n", PIPEX, ARG_ERROR);
		return (EXIT_FAILURE);
	}
	ft_set_progname(cmds, envp);
	ft_validate_prog(cmds);
	ft_run(cmds, fd_in, fd_out, envp);
}
