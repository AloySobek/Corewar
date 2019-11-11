/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_error_object.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 16:00:50 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/07 21:10:40 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cw_error_catcher(int code, const char *section)
{
	ft_printf("Error\n");
	exit(1);
}

// void	cw_error_catcher(const char *obj_name, const char *reason, const char *file, int line)
// {
// 	ft_printf("###ERROR### FOR SOME REASONS AN ERROR OCCURED ###ERROR###\n");
// 	ft_printf("'''''''''''''''''''''''''''''''''''''''''''''''''''''''''\n");
// 	ft_printf("In >>>%s<<< file\n", line);
// 	ft_printf("At >>>%d<<< line\n", line);
// 	ft_printfn("Object: >>>%s<<<", )
// }