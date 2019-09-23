/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_on.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <dbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 16:56:17 by vrichese          #+#    #+#             */
/*   Updated: 2019/09/23 19:27:22 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				compute_sum(char target, int trim_byte)
{
	int total;
	int iter;

	total = 2;
	iter = 4;
	while (iter >= 0)
	{
		if (target & (REG_CODE << iter))
			total += 1;
		else if (target & (DIR_CODE << iter))
			trim_byte ? total += 2 : (total += 4);
		else if (target & (IND_CODE << iter))
			total += 2;
		iter -= 2;
	}
	return (total);
}

void	delete_carriage(corewar_t *game)
{
	--game->carriages_amount;
	if (game->carriages->next == game->carriages)
		game->carriages = NULL;
	else
	{
		game->carriages->prev->next = game->carriages->next;
		game->carriages->next->prev = game->carriages->prev;
		game->carriages = game->carriages->next;
	}
}

void			start_checking(corewar_t *game)
{
	int			iter;

	iter = 0;
	while (iter < game->carriages_amount)
	{
		if (game->arena->loop_amount - game->carriages->last_live_loop >= game->arena->cycle_to_die || game->arena->cycle_to_die <= 0)
			delete_carriage(game);
		if (game->carriages)
			game->carriages = game->carriages->prev;
		++iter;
	}
	if (game->arena->live_amount_in_ctd >= NBR_LIVE)
	{
		game->arena->cycle_to_die -= CYCLE_DELTA;
		game->arena->check_amount = 0;
	}
	else
		++game->arena->check_amount;
	if (game->arena->check_amount >= MAX_CHECKS)
	{
		game->arena->check_amount = 0;
		game->arena->cycle_to_die -= CYCLE_DELTA;
	}
	game->arena->live_amount_in_ctd = 0;
}

void			here_we_go(corewar_t *game)
{
	int			iter;

	while (!game->vis->exit)
	{
		iter = 0;
		cr_vis_keys(game->vis);
		cr_vis_timer(game->vis);
		// if ((game->vis->step || game->vis->flow) && game->vis->tick)
		// {
			while (iter < game->carriages_amount)
			{
				if (!game->carriages->waiting_time)
				{
					if (game->arena->field[game->carriages->current_location] > 0 && game->arena->field[game->carriages->current_location] < 17)
						game->carriages->current_command = game->commands[game->arena->field[game->carriages->current_location]];
					else
					{
						game->carriages->current_location += 1;
						game->carriages->current_location %= MEM_SIZE;
						continue;
					}
					game->carriages->waiting_time = game->carriages->current_command->waiting_time;
				}
				if (game->carriages->waiting_time)
					--game->carriages->waiting_time;
				if (!game->carriages->waiting_time)
				{
					game->carriages->current_command->function(game);
					game->carriages->current_location += game->carriages->next_command_location;
					game->carriages->current_location %= MEM_SIZE;
				}
				cr_vis_updatemap(game);
				game->carriages = game->carriages->prev;
				++iter;
			}
			++game->arena->loop_amount;
			if (!(game->arena->loop_amount % game->arena->cycle_to_die) || game->arena->cycle_to_die <= 0)
				start_checking(game);
			if (!game->carriages)
				break;
		// }
	}
	exit(1);
}