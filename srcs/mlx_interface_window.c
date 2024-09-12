/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_interface_window.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjien-ji <tjien-ji@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 02:10:46 by tjien-ji          #+#    #+#             */
/*   Updated: 2024/09/13 03:06:42 by tjien-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "mlx_interface.h"
#include "../mlx/mlx.h"
#include "../libft/libft.h"

/*
**	Creates a new window with the mlx library and appends the window pointer to
**	the mlx_struct->lst_win list. Returns the index of the window created.
**	Index starts from 1.
*/
int	mrt_create_window(t_mlx_ptrs *mlx_struct, int x, int y, char *title)
{
	t_list	*tmp;

	tmp = ft_lstnew(mlx_new_window(mlx_struct->server, x, y, title));
	ft_lstadd_back(mlx_struct->lst_win, tmp);
	return (ft_lstsize(*mlx_struct->lst_win));
}

void	mrt_destroy_window(t_mlx_ptrs *mlx_struct, size_t win_idx)
{
	void	*win_ptr;

	win_ptr = ft_get_node_by_idx(mlx_struct->lst_win, win_idx)->content;
	if (win_ptr == NULL)
		return ;
	mlx_destroy_window(mlx_struct->server, win_ptr);
	win_ptr = NULL;
}

void	mrt_destroy_all_windows(t_mlx_ptrs *mlx_struct)
{
	t_list	*node;
	t_list	*tmp_node;

	node = *mlx_struct->lst_win;
	while (node)
	{
		tmp_node = node->next;
		mlx_destroy_window(mlx_struct->server, node->content);
		free(node);
		node = tmp_node;
	}
	*mlx_struct->lst_win = NULL;
}

/*
**	Puts image with img_idx onto window with win_idx. Existing
**	coords[0] should be the x-coordinate at which the image should be placed,
**	while coords[1] should be the y-coordinate.
*/
void	mrt_put_img_to_win(t_mlx_ptrs *mlx_struct, size_t win_idx,
		size_t img_idx, int coords[2])
{
	t_list	*node_win;
	t_list	*node_img;

	node_win = ft_get_node_by_idx(mlx_struct->lst_win, win_idx);
	node_img = ft_get_node_by_idx(mlx_struct->lst_img, img_idx);
	if (node_win == NULL || node_img == NULL)
		return ;
	mlx_put_image_to_window(mlx_struct->server, node_win->content,
		node_img->content, coords[0], coords[1]);
}

void	mrt_clear_window(t_mlx_ptrs *mlx_struct, size_t win_idx)
{
	t_list	*node_win;

	node_win = ft_get_node_by_idx(mlx_struct->lst_win, win_idx);
	if (node_win == NULL)
		return ;
	mlx_clear_window(mlx_struct->server, node_win->content);
}
