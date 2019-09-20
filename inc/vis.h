/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <dbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 14:25:33 by dbrady            #+#    #+#             */
/*   Updated: 2019/09/20 18:28:12 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIS_H
# define VIS_H

# include <stdio.h>
# include <stdlib.h>
# include <ncurses.h>
# include <locale.h>

# define V_W 260
# define V_H 68
# define V_BSYM "\xe2\x96\x88"
# define V_SEP 200

enum	actions
{
	INIT,
	PAUSE,
	FORWARD	
};

typedef struct	s_vis
{
	int			action;
}				t_vis;

#endif