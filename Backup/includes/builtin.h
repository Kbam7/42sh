/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 14:36:17 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/05 14:41:46 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

typedef struct		s_env_func
{
	int	u;	// unsets variable for environment (s->env_var)
	int	i;	// ignores envrironment. temporarily creates an empty environment.
}				t_env_func;

typedef struct			s_echo_func
{
	int	e;		// enable interpretation of backlash escapes
	int	up_e;	// (default) Disable interpretation of backslash escapes
	int	n;		// do  not output trailing newline
}				t_echo_func;

typedef struct			s_cd_func
{
	int	l;	// force symbolic links to be followed
	int	p;	// (default)use the physical directory structure without following symbolic links
}				t_cd_func;

typedef struct			s_func_opt
{
	t_env_func	env;
	t_echo_func	echo;
	t_cd_func	cd;
}				t_func_opt;

/*
**	###=----[ BUILTIN FUNCTIONS ]-----=###
*/

/*
**	ft_cd.c
*/
int				ft_cd(char **args, t_shell *s);

/*
**	ft_echo.c
*/
int				ft_echo(char **args, t_shell *s);

/*
**	ft_env.c
*/
int				ft_env(char **input, t_shell *s);

/*
**	ft_setenv.c
*/
int				ft_set(int env_type, char *name, char *val, t_shell *s);

/*
**	ft_unsetenv.c
*/
int				ft_unsetenv(char *name, t_shell *s);

#endif
