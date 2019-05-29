/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <tnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 16:23:42 by tnicolas          #+#    #+#             */
/*   Updated: 2019/05/29 13:27:44 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

t_a		*g_a = NULL;

int		main(int ac, char **av)
{
	if (ac < 2)
		ft_error(true, "Usage: ./scop <file.obj>\n");
	init();
	parse(av[1]);
	loop();
	quit();
	return (EXIT_SUCCESS);
}
