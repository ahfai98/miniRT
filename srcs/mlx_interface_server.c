/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_interface_server.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjien-ji <tjien-ji@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 02:09:26 by tjien-ji          #+#    #+#             */
/*   Updated: 2024/09/13 03:06:48 by tjien-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "mlx_interface.h"
#include "../mlx/mlx.h"
#include "../libft/libft.h"

t_mlx_ptrs	*mrt_start_mlx_server(void)
{
	t_mlx_ptrs	*mlx_struct;

	mlx_struct = (t_mlx_ptrs *) malloc(sizeof(t_mlx_ptrs));
	mlx_struct->server = mlx_init();
	mlx_struct->lst_win = (t_list **) malloc(sizeof(t_list));
	*mlx_struct->lst_win = NULL;
	mlx_struct->lst_img = (t_list **) malloc(sizeof(t_list));
	*mlx_struct->lst_img = NULL;
	mlx_struct->lst_img_dat = (t_list **) malloc(sizeof(t_list));
	*mlx_struct->lst_img_dat = NULL;
	return (mlx_struct);
}

void	mrt_stop_mlx_server(t_mlx_ptrs *mlx_struct)
{
	mrt_destroy_all_images(mlx_struct);
	mrt_destroy_all_windows(mlx_struct);
	mlx_destroy_display(mlx_struct->server);
	free(mlx_struct->server);
	mrt_destroy_mlx_ptrs_struct(mlx_struct);
}
