/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_display_img.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjien-ji <tjien-ji@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 03:31:15 by tjien-ji          #+#    #+#             */
/*   Updated: 2024/09/13 03:36:43 by tjien-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/mlx_interface.h"
#include "../srcs/color.h"
#include "../mlx/mlx.h"
#include "../mlx/mlx_int.h"

int	main(void)
{
	t_mlx_ptrs		*mlx_struct;
	t_mlx_img_data	*img_data_ptr;

	mlx_struct = mrt_start_mlx_server();
	mrt_create_window(mlx_struct, 500, 500, "mlx");
	mrt_create_image(mlx_struct, 500, 500);
	img_data_ptr = (*mlx_struct->lst_img_dat)->content;
	for (int j = 0; j < 500; j++)
		for (int i = 0; i < 500; i++)
			mrt_put_pixel_to_image(img_data_ptr, i, j, get_trgb(color(255,255,0), 0));
	mrt_put_img_to_win(mlx_struct, 1, 1, (int [2]){0, 0});
	mlx_hook((*mlx_struct->lst_win)->content, DestroyNotify, 0,
		mlx_loop_end, mlx_struct->server);
	mlx_loop(mlx_struct->server);
	mrt_stop_mlx_server(mlx_struct);
}
