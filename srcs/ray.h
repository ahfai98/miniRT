/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyap <jyap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:01:39 by jyap              #+#    #+#             */
/*   Updated: 2024/10/01 11:26:16 by jyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vect.h"
# include "intersect.h"

typedef struct s_ray
{
	t_vect	dir;
	t_vect	pos;
	t_inter	inter;
}	t_ray;

#endif