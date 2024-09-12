/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mlx_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjien-ji <tjien-ji@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 02:45:05 by tjien-ji          #+#    #+#             */
/*   Updated: 2024/09/13 02:50:52 by tjien-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "mlx_interface.h"

void	mrt_destroy_mlx_ptrs_struct(t_mlx_ptrs *mlx_struct)
{
	ft_lstclear(mlx_struct->lst_win, NULL);
	free(mlx_struct->lst_win);
	ft_lstclear(mlx_struct->lst_img, NULL);
	free(mlx_struct->lst_img);
	ft_lstclear(mlx_struct->lst_img_dat, free);
	free(mlx_struct->lst_img_dat);
	free(mlx_struct);
}
