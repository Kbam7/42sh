/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 14:38:37 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/06 19:43:39 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATORS_H
# define OPERATORS_H

typedef struct			s_redirs
{
	char			**cmd;		// holds each command/path
	char			**rdr;		// for redir operator strings
	int				**pipe;		// for redir pipes
	int				n_rdr;
	int				rdr_i;		// current redir index
	int				in_fd;		// defines fd on right of operator (<,>).
	int				out_fd;		// defines fd on left of operator (<,>)
}						t_redirs;

typedef struct			s_pipes
{
	int				**pipes;
	int				n_pipes;
	int				pipe_i;
}						t_pipes;

#endif
