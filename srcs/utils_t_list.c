/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_t_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjien-ji <tjien-ji@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 18:05:42 by tjien-ji          #+#    #+#             */
/*   Updated: 2024/09/13 03:23:39 by tjien-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

/*
**	Returns the idx-th node in list, or NULL if list has less than idx nodes.
**	Index starts at 1, so idx = 1 is the first node (list_start).
**	Returns NULL if idx = 0.
*/
t_list	*ft_get_node_by_idx(t_list **list_start, const size_t idx)
{
	size_t	i;
	t_list	*node;

	if (idx == 0)
		return (NULL);
	node = *list_start;
	i = 1;
	while (i++ < idx && node != NULL)
		node = node->next;
	return (node);
}

/*
**	Returns the index of node specified, or 0 if node is not found in list.
**	Index is one-based.
*/
size_t	ft_get_node_idx(t_list **lst_start, t_list *node)
{
	t_list	*tmp_node;
	size_t	idx;

	if (lst_start == NULL || *lst_start == NULL)
		return (0);
	tmp_node = *lst_start;
	idx = 1;
	while (tmp_node != NULL && tmp_node != node)
	{
		tmp_node = tmp_node->next;
		idx++;
	}
	if (tmp_node == node)
		return (idx);
	else
		return (0);
}

/*
**	Returns the index of node with the content specified, or 0 if node is not
**	found in list.
**	Index is one-based.
*/
size_t	ft_get_node_idx_by_content(t_list **lst_start, void *content)
{
	t_list	*tmp_node;
	size_t	idx;

	if (lst_start == NULL || *lst_start == NULL)
		return (0);
	tmp_node = *lst_start;
	idx = 1;
	while (tmp_node != NULL && tmp_node->content != content)
	{
		tmp_node = tmp_node->next;
		idx++;
	}
	if (tmp_node->content == content)
		return (idx);
	else
		return (0);
}

void	ft_del_node_by_idx(t_list **lst_start, size_t idx, void (*del)(void*))
{
	t_list	*prev_node;
	t_list	*node_to_del;

	if (lst_start == NULL || *lst_start == NULL || idx == 0)
		return ;
	if (idx == 1)
	{
		node_to_del = *lst_start;
		*lst_start = (*lst_start)->next;
	}
	else
	{
		prev_node = ft_get_node_by_idx(lst_start, idx - 1);
		if (prev_node == NULL || prev_node->next == NULL)
			return ;
		node_to_del = prev_node->next;
		prev_node->next = node_to_del->next;
	}
	if (del != NULL)
		del(node_to_del->content);
	free(node_to_del);
}
