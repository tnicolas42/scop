/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <tnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 18:10:37 by tim               #+#    #+#             */
/*   Updated: 2019/05/27 11:27:42 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

static void compil_shader(GLuint *shader_id, GLenum type, char *filename)
{
    char    *file_content;
    GLint   compile_error;

    *shader_id = glCreateShader(type);

    if (*shader_id == 0)
    {
        ft_printf("error when creating shader\n");
        exit(EXIT_FAILURE);
    }
    if (ft_read_file(filename, &file_content) == 0)
    {
        ft_printf("error when readind shader: %s\n", filename);
        exit(EXIT_FAILURE);
    }
    glShaderSource(*shader_id, 1, (const GLchar *const *)&file_content, 0);
    glCompileShader(*shader_id);
    compile_error = 0;
    glGetShaderiv(*shader_id, GL_COMPILE_STATUS, &compile_error);
    if (compile_error != GL_TRUE)
    {
        char *error;
        glGetShaderiv(*shader_id, GL_INFO_LOG_LENGTH, &compile_error);
        if (!(error = malloc(sizeof(char) * (compile_error + 1))))
            exit(EXIT_FAILURE);
        glGetShaderInfoLog(*shader_id, compile_error, &compile_error, error);
        error[compile_error] = '\0';
        ft_printf("in file: %s -> %s", filename, error);
        free(error);
        glDeleteShader(*shader_id);
        exit(EXIT_FAILURE);
    }
}

void        init_shader(void)
{
    compil_shader(&(g_a->shader.vert_id), GL_VERTEX_SHADER, SHADER_VERTEX_PATH);
    compil_shader(&(g_a->shader.frag_id), GL_FRAGMENT_SHADER, SHADER_FRAGMENT_PATH);
}