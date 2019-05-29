/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <tnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 14:01:32 by tnicolas          #+#    #+#             */
/*   Updated: 2019/05/29 14:02:00 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

static void	create_bmp_header(char *filename, t_bmp_texture_lst *texture)
{
	FILE	*file;

	if ((file = fopen(filename, "r")) == NULL)
		ft_error(true, "fail to open file %s\n", filename);
	fseek(file, 18, SEEK_SET);
	fread(&texture->t.w, 4, 1, file);
	fread(&texture->t.h, 4, 1, file);
	fseek(file, 2, SEEK_CUR);
	fread(&texture->t.bpp, 2, 1, file);
	fclose(file);
	texture->t.opp = texture->t.bpp >> 3;
	texture->t.sl = texture->t.w * texture->t.opp;
	texture->t.w < 0 ? texture->t.w = -texture->t.w : 0;
	texture->t.h < 0 ? texture->t.h = -texture->t.h : 0;
	texture->t.size = texture->t.sl * texture->t.h;
}

static void	create_bmp_img(t_bmp_texture_lst *texture, char *buffer, int i)
{
	int	j;
	int k;
	int	l;

	if (!(texture->t.img = malloc(sizeof(unsigned char) * texture->t.size)))
		ft_error(true, NULL);
	l = 0;
	while ((i -= texture->t.sl) >= 0)
	{
		j = -texture->t.opp;
		while ((j += texture->t.opp) < texture->t.sl)
		{
			k = -1;
			while (++k < texture->t.opp)
				texture->t.img[l + j + k] = (unsigned char)buffer[i + j +
					(texture->t.opp - k - 1)];
		}
		l += texture->t.sl;
	}
}

static void	create_gl_texture(t_bmp_texture_lst *texture)
{
	glGenTextures(1, &(texture->t.gl_texture));
	glBindTexture(GL_TEXTURE_2D, texture->t.gl_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->t.w, texture->t.h, 0,
		GL_RGB, GL_UNSIGNED_BYTE, texture->t.img);
}

void		load_bmp(char *filename, bool default_tex)
{
	t_bmp_texture_lst	*texture;
	int					fd;
	int					i;
	char				*buffer;

	if (!(texture = malloc(sizeof(t_bmp_texture_lst))))
		ft_error(true, NULL);
	create_bmp_header(filename, texture);
	buffer = (char*)malloc(sizeof(char) * texture->t.size + 1);
	if ((fd = open(filename, O_RDWR)) == -1)
		ft_error(true, "fail to open file %s\n", filename);
	lseek(fd, 54, SEEK_SET);
	i = read(fd, buffer, texture->t.size);
	create_bmp_img(texture, buffer, i);
	ft_strdel((char**)&buffer);
	close(fd);
	create_gl_texture(texture);
	texture->t.is_default_tex = default_tex;
	texture->next = g_a->object.objects->groups->textures_bmp;
	g_a->object.objects->groups->textures_bmp = texture;
	if (default_tex || g_a->object.objects->groups->used_texture_bmp == NULL)
		g_a->object.objects->groups->used_texture_bmp = texture;
}
