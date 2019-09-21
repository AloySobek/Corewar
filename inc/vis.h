/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <dbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 14:25:33 by dbrady            #+#    #+#             */
/*   Updated: 2019/09/21 19:03:39 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIS_H
# define VIS_H

# include <stdio.h>
# include <stdlib.h>
# include <ncurses.h>
# include <locale.h>
# include <time.h>

# define V_W 260
# define V_H 68
# define V_BSYM "\xe2\x96\x88"
# define V_SEP 200

enum			actions
{
	INIT,
	PAUSE,
	FORWARD	
};

typedef struct	s_vis
{
	int			pause;
	int			exit;
	int			step;
	long int	time;
}				t_vis;

int				cr_vis_printattr(int y, int x, char *str, int colour, int reverse);
t_vis			*cr_vis_initvis(void);
int				cr_vis_initcolour(void);
int				cr_vis_initterm(void);
void			cr_vis_putx(int num, int y, int x, int rev);
int				cr_vis_printattr(int y, int x, char *str, int colour, int reverse);
int				cr_vis_drawborder(void);
int				cr_vis_printmap(int *f, int f_len, t_vis *vis);
int				cr_vis_timer(t_vis	*vis);
int				cr_vis_keys(t_vis *vis);

#endif