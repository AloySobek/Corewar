/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_stack_obj.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 19:20:19 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/03 17:33:17 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_STACK_OBJECT_H
# define CW_STACK_OBJECT_H

#include "cw_obj_container.h"

typedef struct	s_stack
{
	t_counter	size;

	t_carriage	*p_current_carriage;
	t_player	*p_current_player;

	t_method	(*cw_constructor)	(t_stack **);
	t_method	(*cw_push)			(t_stack *, t_carriage *, t_player *);
	t_method	(*cw_pop)			(t_stack *, t_carriage **, t_player **);
	t_method	(*cw_rotate)		(t_stack *);
	t_method	(*cw_reverse_rotate)(t_stack *);
	t_method	(*cw_peek)			(t_stack *, t_carriage **, t_player **);
	t_method	(*cw_print_content)	(t_stack *);
	t_method	(*cw_destructor)	(t_stack **);
}				t_stack;

void			cw_create_instance_stack(t_stack **pp_stack_obj);
void			cw_stack_functions_linker(t_stack *p_stack_instance);

#endif