/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_on.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 16:56:17 by vrichese          #+#    #+#             */
/*   Updated: 2019/09/30 17:29:30 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	delete_carriage(corewar_t *game)
{
	--game->carriages_amount;
	if (game->carriages->next == game->carriages)
		game->carriages = NULL;
	else
	{
		if (game->carriages == game->arena->last_carriage)
		{
			game->arena->last_carriage = game->carriages;
			game->arena->last_carriage = game->carriages->prev;
		}
		game->carriages->prev->next = game->carriages->next;
		game->carriages->next->prev = game->carriages->prev;
		game->carriages = game->carriages->next;
	}
}

void		start_checking(corewar_t *game)
{
	int		iter;

	iter = 0;
	while (iter < game->carriages_amount)
	{
		if (game->arena->cycle_amount - game->carriages->last_cycle >= game->arena->cycle_to_die || game->arena->cycle_to_die <= 0)
			delete_carriage(game);
		if (game->carriages)
			game->carriages = game->carriages->prev;
		++iter;
	}
	if (game->arena->live_amount >= NBR_LIVE)
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
	game->arena->live_amount = 0;
}

void		here_we_go(corewar_t *game)
{
	int		carriage_iter;
	char	flag;

	while (game->carriages)
	{
		carriage_iter = 0;
		while (carriage_iter < game->carriages_amount)
		{
			if (!game->carriages->waiting_time)
			{
				if (game->arena->field[game->carriages->current_location] > 0 && game->arena->field[game->carriages->current_location] < 17)
				{
					game->carriages->current_command = game->commands[game->arena->field[game->carriages->current_location]];
						game->carriages->waiting_time = game->carriages->current_command->waiting_time;
				}
				else
				{
					game->carriages->current_location = (game->carriages->current_location + 1) % MEM_SIZE;
 					continue;
 				}
			}
			if (game->carriages->waiting_time)
				--game->carriages->waiting_time;
			if (!game->carriages->waiting_time)
			{
				printf("cycle: %d carriage: %d\n", game->arena->cycle_amount, game->carriages->id);
				game->carriages->current_command->function(game);
				game->carriages->current_location = (game->carriages->current_location + game->carriages->jump) % MEM_SIZE;
				if (game->carriages->current_location < 0)
					game->carriages->current_location = -game->carriages->current_location;
				while (flag != '1')
					read(0, &flag, 1);
				flag = '0';
			}
			game->carriages = game->carriages->prev;
			++carriage_iter;
		}
		if (++game->arena->cycle_amount >= 5000)
		{
			//print_arena(game);
			exit(1);
		}
 		if (!(game->arena->cycle_amount % game->arena->cycle_to_die) || game->arena->cycle_to_die <= 0)
 			start_checking(game);
	}
 	printf("Player %s number %d is WIN!!!\n", game->arena->last_survivor->name, game->arena->last_survivor->id);
}