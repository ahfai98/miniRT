/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyap <jyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 06:04:31 by tjien-ji          #+#    #+#             */
/*   Updated: 2024/10/01 11:58:10 by jyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"
#include "mlx_structs.h"
#include "generic_obj.h"
#include <math.h>
#include <X11/keysym.h>

void	kb_event_handler_transform_cam(int keycode, t_mlxs *mlxs)
{
	if (keycode == XK_equal || keycode == XK_minus)
		kb_event_handler_zoom_cam(keycode, mlxs);
	else if (keycode == XK_w || keycode == XK_a || keycode == XK_s
		|| keycode == XK_d || keycode == XK_Up || keycode == XK_Down)
		kb_event_handler_translate_cam(keycode, mlxs);
	else if (keycode == XK_h || keycode == XK_k
		|| keycode == XK_u || keycode == XK_j
		|| keycode == XK_bracketleft || keycode == XK_bracketright)
		kb_event_handler_rotate_cam(keycode, mlxs);
	else
		return ;
	render(mlxs);
}

void	kb_event_handler_rotate_cam(int keycode, t_mlxs *mlxs)
{
	if (keycode == XK_h)
		rotate_cam_y(&mlxs->sc->cam, -10);
	else if (keycode == XK_k)
		rotate_cam_y(&mlxs->sc->cam, 10);
	else if (keycode == XK_u)
		rotate_cam_x(&mlxs->sc->cam, 10);
	else if (keycode == XK_j)
		rotate_cam_x(&mlxs->sc->cam, -10);
	else if (keycode == XK_bracketleft)
		rotate_cam_z(&mlxs->sc->cam, 10);
	else if (keycode == XK_bracketright)
		rotate_cam_z(&mlxs->sc->cam, -10);
}

void	kb_event_handler_translate_cam(int keycode, t_mlxs *mlxs)
{
	t_vect	translation_vect;

	translation_vect = vect(0, 0, 0);
	if (keycode == XK_w)
		translation_vect = mult(mlxs->sc->cam.v, -1);
	else if (keycode == XK_a)
		translation_vect = mult(mlxs->sc->cam.u, -1);
	else if (keycode == XK_s)
		translation_vect = mlxs->sc->cam.v;
	else if (keycode == XK_d)
		translation_vect = mlxs->sc->cam.u;
	else if (keycode == XK_Up)
		translation_vect = mlxs->sc->cam.norm;
	else if (keycode == XK_Down)
		translation_vect = mult(mlxs->sc->cam.norm, -1);
	mlxs->sc->cam.pos = add(mlxs->sc->cam.pos, translation_vect);
}

void	kb_event_handler_zoom_cam(int keycode, t_mlxs *mlxs)
{
	double	diff;

	diff = 0;
	if (keycode == XK_equal && mlxs->sc->cam.fov_deg < 179)
		diff = 1;
	else if (keycode == XK_minus && mlxs->sc->cam.fov_deg > 2)
		diff = -1;
	mlxs->sc->cam.fov_deg += diff;
}
