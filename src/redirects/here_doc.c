/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:09:04 by ailbezer          #+#    #+#             */
/*   Updated: 2025/03/20 15:00:58 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*delimiter(t_token *tokens)
{	
	t_token	*temp;
	
	temp = tokens;
	while (temp->next)
	{
		if (temp->type == HERE_DOC)
			break ;
		temp = temp->next;
	}
	return (temp->next->value);
}

void	hd_loop(t_token *tokens, char *dlmt, int fd)
{
	char	*input;
	
	(void)tokens;
	while (1)
	{
		signal(SIGINT, ctrl_c_hd);
		input = readline(CYAN "> " END);
		if (!input)
		{
			hd_eof(dlmt);
			break ;
		}
		if (!ft_strcmp(input, dlmt))
		{
			free(input);
			break ;
		}
		if (!delimiter_quotes(dlmt))
			input = handle_expansion_hd(input);
		ft_putendl_fd(input, fd);
		free(input);
	}
	exit(0);
}

void	hd_routine(t_token *tokens)
{
	int			fd;
	char		*filename;
	char		*dlmt;
	t_hd		*hd;
	
	hd = get_ms()->hd;
	dlmt = delimiter(tokens);
	filename = ft_strjoin("here_doc", ft_itoa(get_ms()->hd->start_fd));
	append_hd(filename, &hd->arr_hds[hd->cmd_index]);
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	hd_loop(tokens, dlmt, fd);
	close(fd);
}

void	execute_hd(t_token *tokens)
{
	int		pid;
	int		status;
	
	pid = fork();
	if (pid == 0)
		hd_routine(tokens);
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
			execute_hd(tokens);
			get_ms()->hd->start_fd++;
		}
		temp = temp->next;
	}
}
