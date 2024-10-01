/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyap <jyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 05:01:26 by tjien-ji          #+#    #+#             */
/*   Updated: 2024/10/01 11:58:10 by jyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"
#include "mlx_structs.h"
#include "generic_obj.h"
#include <math.h>
#include <X11/keysym.h>

void	mouse_event_handler_resize_obj(int button, t_mlxs *mlxs)
{
	double	diff;

	diff = 0;
	if (button == MOUSE_SCROLL_UP)
		diff = 1;
	else if (button == MOUSE_SCROLL_DOWN)
		diff = -1;
	else
		return ;
	resize_obj_1(mlxs->last_selected_obj, diff);
	render(mlxs);
}

void	kb_event_handler_transform_obj(int keycode, t_mlxs *mlxs)
{
	if (keycode == XK_equal || keycode == XK_minus)
		kb_event_handler_resize_obj(keycode, mlxs);
	else if (keycode == XK_w || keycode == XK_a || keycode == XK_s
		|| keycode == XK_d || keycode == XK_Up || keycode == XK_Down)
		kb_event_handler_translate_obj(keycode, mlxs);
	else if (keycode == XK_h || keycode == XK_k
		|| keycode == XK_u || keycode == XK_j
		|| keycode == XK_bracketleft || keycode == XK_bracketright)
		kb_event_handler_rotate_obj(keycode, mlxs);
	else
		return ;
	render(mlxs);
}

void	kb_event_handler_rotate_obj(int keycode, t_mlxs *mlxs)
{
	t_vect	rotation_axis;
	double	deg;

	deg = 10;
	if (keycode == XK_h || keycode == XK_k)
		rotation_axis = vect(0, 1, 0);
	else if (keycode == XK_u || keycode == XK_j)
		rotation_axis = vect(1, 0, 0);
	else if (keycode == XK_bracketleft || keycode == XK_bracketright)
		rotation_axis = vect(0, 0, 1);
	else
		return ;
	if (keycode == XK_h || keycode == XK_j
		|| keycode == XK_bracketleft)
		deg *= -1;
	rotate_obj(mlxs->last_selected_obj, rotation_axis, deg);
}

void	kb_event_handler_translate_obj(int keycode, t_mlxs *mlxs)
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
	translate_obj(mlxs->last_selected_obj, translation_vect);
}

void	kb_event_handler_resize_obj(int keycode, t_mlxs *mlxs)
{
	double	diff;

	diff = 0;
	if (keycode == XK_equal)
		diff = 1;
	else if (keycode == XK_minus)
		diff = -1;
	resize_obj_2(mlxs->last_selected_obj, diff);
}
