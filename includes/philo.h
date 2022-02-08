/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 15:59:07 by agiraude          #+#    #+#             */
/*   Updated: 2022/02/08 15:07:38 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include "fifo.h"

# define PICK_FORK 1
# define PUT_FORK 0
# define MSG_BUF_SIZE 50

typedef struct	s_rules
{
	int			nb_philo;
	long int	tm_to_die;
	long int	tm_to_eat;
	long int	tm_to_sleep;
	int			nb_eat_to_end;
	int			*meals;
	pthread_mutex_t	talk;
}				t_rules;

typedef struct	s_fork_master
{
	int				nb_fork;
	int				*status;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
}				t_fm;

typedef struct	s_death
{
	pthread_mutex_t lock;
	int				dead;
}				t_death;

typedef struct	s_philo
{
	int				id;
	int				fork_l;
	int				fork_r;
	int				hold[2];
	long int		last_meal;
	long int		last_sleep;
	t_rules			*ruleset;
	t_fm			*forkmaster;
	t_death			*death;
}				t_philo;

//fifo
t_fifo		*fifo_create(int size);
int			fifo_read(t_fifo *f, char *buf, int nbytes);
int			fifo_write(t_fifo *f, const char *buf, int nbytes);

//forkmaster
int			forkmaster_ask(t_philo *self);
void		forkmaster_tell(t_philo *self, int fork_id);
void		forkmaster_del(t_fm *forkmaster);
t_fm		*forkmaster_create(int n);

//msg
t_fifo	*msg_fifo(int destroy);
void		msg_put(t_philo *self, long int ms, char *msg);
void		*msg_thread(void *ptr);

//philo
void		philo_use_fork(t_philo *self, int fork_id, int use);
void	philo_letgo(t_philo *self);
int			philo_is_alive(t_philo *self);
void		philo_wait(t_philo *self, long int tm_to_wait);
void		*philo_run(void *self_ptr);
int			philo_loop(t_philo *self);

//room
int			room_play(t_rules *ruleset);

//utils
int			ft_atoi(const char *nptr);
int			ft_strisnb(const char *str);
int			ft_strlen(const char *str);
long int	time_getstamp(void);
char		*ft_strnstr(const char *big, const char *little, size_t len);

#endif
