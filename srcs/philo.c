/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 16:25:27 by agiraude          #+#    #+#             */
/*   Updated: 2022/02/05 17:54:10 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_is_alive(t_philo *self)
{
	long int	ms;
	int			ret;

	ms = time_getstamp();
	pthread_mutex_lock(&(self->death->lock));
	if (self->death->count > 0)
		ret = 0;
	else if (self->ruleset.tm_to_die < ms - self->last_meal)
	{
		printf("%ld %d died\n", ms, self->id);
		self->death->count += 1;
		ret = 0;
	}
	else
		ret = 1;
	pthread_mutex_unlock(&(self->death->lock));
	return (ret);
}

void	philo_put_msg(t_philo *self, long int ms, const char *msg)
{
	if (philo_is_alive(self))
		printf("%ld %d %s\n", ms, self->id, msg);
}

void	philo_use_fork(t_philo *self, int fork_id, int use)
{
	long int	ms;

	if (use == PICK_FORK)
	{
		pthread_mutex_lock(&(self->forkmaster->forks[fork_id]));
		ms = time_getstamp();
		printf("%ld %d has taken a fork\n", ms, self->id);
	}
	else if (use == PUT_FORK)
		pthread_mutex_unlock(&(self->forkmaster->forks[fork_id]));
}

void	philo_sleep(t_philo *self)
{
	long int	ms;

	ms = time_getstamp();
	self->last_sleep = ms;
	philo_put_msg(self, ms, "is sleeping");
	//tester
	forkmaster_tell(self);

	usleep(self->ruleset.tm_to_sleep * 1000);
}

void	philo_think(t_philo *self)
{
	long int	ms;

	ms = time_getstamp();
	philo_put_msg(self, ms, "is thinking");
}

void	philo_eat(t_philo *self)
{
	long int	ms;

	ms = time_getstamp();
	self->last_meal = ms;
	self->nb_meal += 1;
	philo_put_msg(self, ms, "is eating");
	usleep(self->ruleset.tm_to_eat * 1000);
}

void	*philo_run(void *self_ptr)
{
	t_philo	*self;
	int		monitor_meals;
	

	if (!self_ptr)
		return (0);
	self = (t_philo *)self_ptr;
	self->last_meal = time_getstamp();
	self->last_sleep = time_getstamp();
	monitor_meals = 0;
	if (self->ruleset.nb_eat_to_end != -1)
		monitor_meals = 1;
	while (philo_is_alive(self))
	{
		if (self->nb_meal >= self->ruleset.nb_eat_to_end && monitor_meals)
			break ;
		if (forkmaster_ask(self))
		{
			philo_use_fork(self, self->fork_l, PICK_FORK);
			philo_use_fork(self, self->fork_r, PICK_FORK);
			philo_eat(self);
			philo_use_fork(self, self->fork_l, PUT_FORK);
			philo_use_fork(self, self->fork_r, PUT_FORK);
			//tester
			//forkmaster_tell(self);
			philo_sleep(self);
			philo_think(self);
		}
	}
	free(self);
	return (0);
}
