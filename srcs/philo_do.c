/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_do.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 16:25:27 by agiraude          #+#    #+#             */
/*   Updated: 2022/02/09 11:12:01 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_use_fork(t_philo *self, int fork_id, int use)
{
	if (use == PICK_FORK)
	{
		pthread_mutex_lock(&(self->forkmaster->forks[fork_id]));
		msg_put(self, time_getstamp(), "has taken a fork");
		if (fork_id == self->fork_l)
			self->hold[0] = 1;
		else
			self->hold[1] = 1;
	}
	else if (use == PUT_FORK)
	{
		pthread_mutex_unlock(&(self->forkmaster->forks[fork_id]));
		forkmaster_tell(self, fork_id);
		if (fork_id == self->fork_l)
			self->hold[0] = 0;
		else
			self->hold[1] = 0;
	}
}

void	philo_sleep(t_philo *self)
{
	long int	ms;

	if (self->death->dead)
		return ;
	ms = time_getstamp();
	self->last_sleep = ms;
	msg_put(self, ms, "is sleeping");
	philo_wait(self, self->ruleset->tm_to_sleep);
}

void	philo_think(t_philo *self)
{
	long int	ms;

	if (self->death->dead)
		return ;
	ms = time_getstamp();
	msg_put(self, ms, "is thinking");
}

void	philo_eat(t_philo *self)
{
	long int	ms;

	if (self->death->dead)
		return ;
	ms = time_getstamp();
	self->last_meal = ms;
	self->ruleset->meals[self->id - 1] += 1;
	msg_put(self, ms, "is eating");
	philo_wait(self, self->ruleset->tm_to_eat);
}

int	philo_loop(t_philo *self)
{
	while (philo_is_alive(self))
	{
		if (forkmaster_ask(self))
		{
			philo_use_fork(self, self->fork_l, PICK_FORK);
			philo_use_fork(self, self->fork_r, PICK_FORK);
			philo_eat(self);
			philo_letgo(self);
			if (!philo_is_alive(self))
				break ;
			philo_sleep(self);
			if (!philo_is_alive(self))
				break ;
			philo_think(self);
		}
	}
	return (0);
}
