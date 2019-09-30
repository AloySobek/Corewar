/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwDestructor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 18:04:57 by vrichese          #+#    #+#             */
/*   Updated: 2019/09/30 18:45:10 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				cwInitializationDestructor(corewar_t *game)
{
	destructor_t	*new_destructor;

	if (!(new_destructor = (destructor_t *)malloc(sizeof(destructor_t))))
		error_catcher(CW_NOT_ALLOCATED, CW_DESTRUCTOR);
	new_destructor->game_detect			= CW_TRUE;
	new_destructor->keys_detect			= CW_FALSE;
	new_destructor->arena_detect		= CW_FALSE;
	new_destructor->players_detect		= CW_FALSE;
	new_destructor->commands_detect 	= CW_FALSE;
	new_destructor->carriages_detect	= CW_FALSE;
	game->destructor					= new_destructor;
}

void				cwCleanUp(corewar_t *game)
{
	return ;
}