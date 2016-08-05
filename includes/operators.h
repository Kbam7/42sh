/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 14:38:37 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/05 14:41:01 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATORS_H
# define OPERATORS_H

typedef struct			s_redirs
{
// redirs
	int			**redirs;
	int			n_redirs;
	int			redir_i;

}						t_redirs;

typedef struct			s_pipes
{
// pipes
	int			**pipes;
	int			n_pipes;
	int			pipe_i;
}						t_pipes;

#endif
