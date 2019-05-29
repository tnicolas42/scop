/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <tnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 16:23:42 by tnicolas          #+#    #+#             */
/*   Updated: 2019/05/29 15:25:19 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

t_a		*g_a = NULL;

void	ft_usage(void)
{
	ft_printf("Usage: ./scop <file.obj>\n"
		"Keyboard shortcuts:\n"
		"\t<up> | <down> | <left> | <right> to move piece in screen\n"
		"\t<w> | <a> | <s> | <d> to move piece in screen\n"
		"\t<+> | <-> to zoom / dezoom\n"
		"\t[Shift] + <xyz> to move piece in axis\n"
		"\t<ctrl> + [Shift] + <xyz> to rotate piece in axis\n"
		"\t<t> to change texture\n"
		"\t<m> to enable or disable auto rotate\n"
		"\t<r> to reset position\n"
		"Mouse control\n"
		"\t<leftClick> to move object\n"
		"\t<ctrl> + leftClick> | <rightClick> to rotate object\n"
		"\t<scrollUp> | <scrollDown> to zoom on object\n");
}

int		main(int ac, char **av)
{
	if (ac < 2)
	{
		ft_usage();
		return (EXIT_SUCCESS);
	}
	init();
	parse(av[1]);
	loop();
	quit();
	return (EXIT_SUCCESS);
}
