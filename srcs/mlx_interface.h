/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_interface.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjien-ji <tjien-ji@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 01:57:44 by tjien-ji          #+#    #+#             */
/*   Updated: 2024/09/13 03:06:04 by tjien-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_INTERFACE_H
# define MLX_INTERFACE_H

# define MLX_KEYCODE_ESCAPE 0xff1b
# define MLX_KEYCODE_LEFT_ARROW 0xff51
# define MLX_KEYCODE_UP_ARROW 0xff52
# define MLX_KEYCODE_RIGHT_ARROW 0xff53
# define MLX_KEYCODE_DOWN_ARROW 0xff54
# define MLX_KEYCODE_A 0x0061
# define MLX_KEYCODE_D 0x0064
# define MLX_KEYCODE_S 0x0073
# define MLX_KEYCODE_W 0x0077

# include "../libft/libft.h"

typedef struct s_mlx_ptrs
{
	void	*server;
	t_list	**lst_win;
	t_list	**lst_img;
	t_list	**lst_img_dat;
}	t_mlx_ptrs;

typedef struct s_mlx_img_data
{
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		pix_color;
	int		color_1;
	int		color_2;
	int		img_width;
	int		img_height;
}	t_mlx_img_data;

/*	mlx_interface_server	*/
t_mlx_ptrs			*mrt_start_mlx_server(void);
void				mrt_stop_mlx_server(t_mlx_ptrs *mlx_struct);

/*	mlx_interface_window	*/
int					mrt_create_window(t_mlx_ptrs *mlx_struct, int x, int y,
						char *title);
void				mrt_destroy_window(t_mlx_ptrs *mlx_struct, size_t win_idx);
void				mrt_destroy_all_windows(t_mlx_ptrs *mlx_struct);
void				mrt_put_img_to_win(t_mlx_ptrs *mlx_struct,
						size_t win_idx, size_t img_idx, int coords[2]);
void				mrt_clear_window(t_mlx_ptrs *mlx_struct, size_t win_idx);

/*	mlx_interface_image	*/
int					mrt_create_image(t_mlx_ptrs *mlx_struct, int width,
						int height);
void				mrt_clear_img_dat(t_mlx_img_data *img_dat);
void				mrt_destroy_image(t_mlx_ptrs *mlx_struct, size_t img_idx);
void				mrt_destroy_all_images(t_mlx_ptrs *mlx_struct);
void				mrt_put_pixel_to_image(t_mlx_img_data *img_dat,
						size_t x, size_t y, int color);

/*	utils_mlx_struct	*/
void				mrt_destroy_mlx_ptrs_struct(t_mlx_ptrs *mlx_struct);

/*	utils_t_list	*/
t_list				*ft_get_node_by_idx(t_list **list_start, const size_t n);
size_t				ft_get_node_idx(t_list **lst_start, t_list *node);
size_t				ft_get_node_idx_by_content(t_list **lst_start,
						void *content);
void				ft_del_node_by_idx(t_list **lst_start, size_t idx,
						void (*del)(void*));

/*	utils_generic	*/
unsigned int		ft_swap_endianness(unsigned int value);

#endif
