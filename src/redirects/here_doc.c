/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:09:04 by ailbezer          #+#    #+#             */
/*   Updated: 2025/03/27 18:34:38 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_input(char *dlmt, int quotes, char **input, int fd)
{
	while (1)
	{
		signal(SIGINT, ctrl_c_hd);
		*input = readline(CYAN "> " END);
		gc_track(*input);
		if (!*input)
		{
			hd_eof(dlmt);
			break ;
		}
		if (!ft_strcmp(*input, dlmt))
			break ;
		if (!quotes)
			*input = handle_expansion_hd(*input);
		ft_putendl_fd(*input, fd);
	}
}

void	hd_loop(char *dlmt, int fd)
{
	char	*input;
	int		quotes;

	quotes = delimiter_quotes(dlmt);
	dlmt = remove_dlmt_quotes(dlmt);
	handle_input(dlmt, quotes, &input, fd);
	clear_all();
	exit(0);
}

static void	hd_routine(t_token *tokens, int fd)
{
	char		*dlmt;

	dlmt = delimiter(tokens);
	hd_loop(dlmt, fd);
	close(fd);
}

void	execute_hd(t_token *tokens)
{
	int		pid;
	int		status;
	int		fd;
	char	*filename;
	t_hd	*hd;

	hd = get_ms()->hd;
	filename = ft_strjoin("/tmp/here_doc", ft_itoa(get_ms()->hd->start_fd));
	append_hd(filename, &hd->arr_hds[hd->cmd_index]);
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	pid = fork();
	if (pid == 0)
		hd_routine(tokens, fd);
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		get_ms()->exit_status = WEXITSTATUS(status);
	}
}

void	check_hd(t_token *tokens)
{
	t_token	*temp;

	init_hd(tokens);
	temp = tokens;
	while (temp)
	{
		if (temp->type == PIPE)
			get_ms()->hd->cmd_index++;
		else if (temp->type == HERE_DOC)
		{
			execute_hd(temp);
			get_ms()->hd->start_fd++;
		}
		temp = temp->next;
	}
}
