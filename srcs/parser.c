/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <tnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 16:47:35 by tnicolas          #+#    #+#             */
/*   Updated: 2019/05/21 17:07:49 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	parse(void)
{
	double	size;

	size = 10;
	g_a->description.size.x = size;
	g_a->description.size.y = size;
	g_a->description.size.z = size;



	double	max_size;

	max_size = g_a->description.size.x;
	max_size = (g_a->description.size.y > max_size) ? g_a->description.size.y : max_size;
	max_size = (g_a->description.size.z > max_size) ? g_a->description.size.z : max_size;
	if (max_size == 0)
		max_size = 1;
	g_a->description.max_size = max_size;
}