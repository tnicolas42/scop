/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <tnicolas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 18:10:37 by tim               #+#    #+#             */
/*   Updated: 2019/05/27 15:20:43 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

static void compil_shader(GLuint *shader_id, GLenum type, char *filename)
{
    char    *file_content;
    GLint   compile_error;
    char *error;

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
        glGetShaderiv(*shader_id, GL_INFO_LOG_LENGTH, &compile_error);
        if (!(error = malloc(sizeof(char) * (compile_error + 1))))
            exit(EXIT_FAILURE);
        glGetShaderInfoLog(*shader_id, compile_error, &compile_error, error);
        error[compile_error] = '\0';
        ft_printf("in file %s:\n%s", filename, error);
        free(error);
        glDeleteShader(*shader_id);
        exit(EXIT_FAILURE);
    }
}

void        set_material(t_material m)
{
    GLfloat ambient[4] = {m.ambient.x, m.ambient.y, m.ambient.z, 1.0};
    GLfloat diffuse[4] = {m.diffuse.x, m.diffuse.y, m.diffuse.z, 1.0};
    GLfloat specular[4] = {m.specular.x, m.specular.y, m.specular.z, 1.0};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m.shininess);
}

void        init_shader(void)
{
    GLint  success;
    char    infoLog[512];

    compil_shader(&(g_a->shader.vert_id), GL_VERTEX_SHADER, SHADER_VERTEX_PATH);
    compil_shader(&(g_a->shader.frag_id), GL_FRAGMENT_SHADER, SHADER_FRAGMENT_PATH);
    g_a->shader.program = glCreateProgram();
    glAttachShader(g_a->shader.program, g_a->shader.vert_id);
    glAttachShader(g_a->shader.program, g_a->shader.frag_id);
    glLinkProgram(g_a->shader.program);
    glGetProgramiv(g_a->shader.program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(g_a->shader.program, 512, NULL, infoLog);
        ft_printf("%s", infoLog);
        exit(EXIT_FAILURE);
    }
    glDeleteShader(g_a->shader.vert_id);
    glDeleteShader(g_a->shader.frag_id);
    glUseProgram(g_a->shader.program);
    set_material(g_a->object.material);
}