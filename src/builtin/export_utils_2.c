// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   export_utils_2.c                                   :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/03/19 10:13:48 by cabo-ram          #+#    #+#             */
// /*   Updated: 2025/03/19 15:00:51 by cabo-ram         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../includes/minishell.h"

// int	ft_strcmp(const char *s1, const char *s2)
// {
// 	while (*s1 && (*s1 == *s2))
// 	{
// 		s1++;
// 		s2++;
// 	}
// 	return ((unsigned char)(*s1) - (unsigned char)(*s2));
// }

// int	env_list_count(t_env *env_list)
// {
// 	int	count;

// 	count = 0;
// 	while (env_list)
// 	{
// 		count++;
// 		env_list = env_list->next;
// 	}
// 	return (count);
// }

// t_env	*new_env_list_node(char *var)
// {
// 	t_env	*new_node;

// 	new_node = gc_malloc(sizeof(t_env));
// 	if (!new_node)
// 	{
// 		perror("Erro de alocação de memória new_env_list_node");
// 		return (NULL);
// 	}
// 	new_node->var = ft_strdup(var);
// 	if (!new_node->var)
// 	{
// 		free(new_node);
// 		return (NULL);
// 	}
// 	new_node->next = NULL;
// 	return (new_node);
// }

// void	append_env_list(char *var, t_env **env_list)
// {
// 	t_env	*new_node;
// 	t_env	*temp;

// 	new_node = new_env_list_node(var);
// 	if (!new_node)
// 		return ;
// 	if (!*env_list)
// 	{
// 		*env_list = new_node;
// 		return ;
// 	}
// 	temp = *env_list;
// 	while (temp->next)
// 		temp = temp->next;
// 	temp->next = new_node;
// }

// // void	print_new_env_list(t_env *env_list)
// // {
// // 	int		count;
// // 	int		i;
// // 	char	**env_array;
// // 	t_env	*temp;

// // 	count = env_list_count(env_list);
// // 	env_array = gc_malloc(sizeof(char *) * (count + 1));
// // 	if (!env_array)
// // 	{
// // 		perror("Erro de alocação de memória print_new_env_list");
// // 		return ;
// // 	}
// // 	temp = env_list;
// // 	i = 0;
// // 	while (i < count)
// // 	{
// // 		env_array[i] = temp->var;
// // 		temp = temp->next;
// // 		i++;
// // 	}
// // 	env_array[count] = NULL;
// // }

// void	print_sort(t_env *env_list)
// {
// 	while (env_list)
// 	{
// 		printf("declare -x %s\n", env_list->var);
// 		env_list = env_list->next;
// 	}
// }

// t_env	*last_env_node(t_env *head)
// {
// 	if (!head)
// 		return (NULL);
// 	while (head && head->next)
// 		head = head->next;
// 	return (head);
// }

// t_env	*get_sorted_env(char **envp)
// {
// 	t_env	*head;
// 	int		i;

// 	head = NULL;
// 	i = 0;
// 	while (envp[1])
// 	{
// 		append_env_list(envp[i], &head);
// 		i++;
// 	}
// 	return (head);
// }

// t_env	*partition(t_env *low, t_env *high)
// {
// 	char	*pivot;
// 	t_env	*i;
// 	t_env	*j;

// 	pivot = high->var;
// 	i = low;
// 	j = low;
// 	while (j != high)
// 	{
// 		if (ft_strcmp(j->var, pivot) < 0)
// 		{
// 			ft_swap(i, j);
// 			i = i->next;
// 		}
// 		j = j->next;
// 	}
// 	ft_swap(i, high);
// 	return (i);
// }

// void	quick_sort(t_env *low, t_env *high)
// {
// 	t_env	*p;

// 	if (low && high && low != high && low != high->next)
// 	{
// 		p = partition(low, high);
// 		quick_sort(low, p->next);
// 		quick_sort(p->next, high);
// 	}
// }

// void	ft_xp(char **envp)
// {
// 	t_env	*env_list;
// 	t_env	*last;

// 	env_list = get_sorted_env(envp);
// 	last = last_env_node(env_list);
// 	quick_sort(env_list, last);
// 	print_sort(env_list);
// }
