/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_interface_image.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjien-ji <tjien-ji@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 02:05:30 by tjien-ji          #+#    #+#             */
/*   Updated: 2024/09/13 03:06:33 by tjien-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "mlx_interface.h"
#include "../mlx/mlx.h"
#include "../libft/libft.h"

/*
**	Creates a new image with the mlx library and appends the image pointer to
**	the mlx_struct->lst_img list. Also creates a new node in
**	mlx_struct->lst_img_dat to hold the data returned by mlx_get_data_addr().
**	Returns the index of the image created, or -1 if failed.
**	Index starts from 1.
*/
int	mrt_create_image(t_mlx_ptrs *mlx_struct, int width, int height)
{
	void			*ptr;
	t_list			*node;
	t_mlx_img_data	*img_dat;

	ptr = mlx_new_image(mlx_struct->server, width, height);
	if (!ptr)
	{
		ft_putstr_fd("Unable to create new image", STDERR_FILENO);
		return (-1);
	}
	node = ft_lstnew(ptr);
	ft_lstadd_back(mlx_struct->lst_img, node);
	img_dat = (t_mlx_img_data *) malloc(sizeof(t_mlx_img_data));
	ptr = mlx_get_data_addr(node->content, &img_dat->bits_per_pixel,
			&img_dat->size_line, &img_dat->endian);
	img_dat->addr = ptr;
	img_dat->pix_color = 0xffffff;
	img_dat->img_width = width;
	img_dat->img_height = height;
	node = ft_lstnew(img_dat);
	ft_lstadd_back(mlx_struct->lst_img_dat, node);
	return (ft_lstsize(*mlx_struct->lst_img_dat));
}

/*
**	Reset all pixels in the img_dat to black without destroying the image
*/
void	mrt_clear_img_dat(t_mlx_img_data *img_dat)
{
	ft_bzero(img_dat->addr, img_dat->size_line * img_dat->img_height);
}

void	mrt_destroy_image(t_mlx_ptrs *mlx_struct, size_t img_idx)
{
	t_list	*node_img;

	node_img = ft_get_node_by_idx(mlx_struct->lst_img, img_idx);
	if (node_img == NULL)
		return ;
	mlx_destroy_image(mlx_struct->server, node_img->content);
	node_img->content = NULL;
}

void	mrt_destroy_all_images(t_mlx_ptrs *mlx_struct)
{
	t_list	*node_img;
	t_list	*tmp_node_img;

	node_img = *mlx_struct->lst_img;
	while (node_img)
	{
		mlx_destroy_image(mlx_struct->server, node_img->content);
		tmp_node_img = node_img->next;
		free(node_img);
		node_img = tmp_node_img;
	}
	ft_lstclear(mlx_struct->lst_img_dat, &free);
	*mlx_struct->lst_img = NULL;
	*mlx_struct->lst_img_dat = NULL;
}

/*
**	Modifies region of memory pointed to by image data address to put a pixel
**	onto the image.
**	x and y specify the coordinates of the pixel, x = 0 and y = 0 being the top
**	left corner of the image.
**	color should be the return value from mlx_get_color_value to ensure correct
**	color values for displays with bit depths lower than 24.
**	If there's a need to set brightness to less than 1, then
**	mrt_get_color_value can be used instead.
*/
void	mrt_put_pixel_to_image(t_mlx_img_data *img_dat,
			size_t x, size_t y, int color)
{
	size_t	pixel_idx;
	int		bytes_per_line;
	int		bits_per_pixel;

	bytes_per_line = img_dat->size_line;
	bits_per_pixel = img_dat->bits_per_pixel;
	pixel_idx = y * bytes_per_line + x * bits_per_pixel / 8;
	if (img_dat->endian)
		color = ft_swap_endianness(color);
	ft_memcpy(img_dat->addr + pixel_idx, &color, bits_per_pixel / 8);
}
