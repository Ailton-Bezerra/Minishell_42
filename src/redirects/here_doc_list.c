/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:36:05 by ailbezer          #+#    #+#             */
/*   Updated: 2025/03/24 17:51:56 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_hd	*init_hd(t_token *tokens)
{
	int		cmd_qtd;
	t_hd	*hd;

	cmd_qtd = count_pipes(tokens) + 1;
	hd = gc_malloc(sizeof(t_hd));
	hd->arr_hds = gc_malloc(sizeof(t_hd_list) * cmd_qtd);
	hd->cmd_index = 0;
	hd->start_fd = 0;
	return (hd);
}

t_hd_list	*new_hd_node(char *filename)
{
	t_hd_list	*new;

	new = gc_malloc(sizeof(t_hd_list));
	new->filename = filename;
	new->next = NULL;
	return (new);
}

t_hd_list	*last_hd_node(t_hd_list *head)
{
	if (!head)
		return (NULL);
	while (head && head->next)
		head = head->next;
	return (head);
}

void	append_hd(char *filename, t_hd_list **head)
{
	t_hd_list	*new;
	new = new_hd_node(filename);
	if (!*head)
		*head = new;
	else
		last_hd_node(*head)->next = new;
}
