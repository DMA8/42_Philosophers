/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syolando <syolando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 23:32:26 by syolando          #+#    #+#             */
/*   Updated: 2022/05/30 01:44:43 by syolando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct s_philo t_philo;
typedef struct s_overall t_overall;

typedef struct s_philo
{
	pid_t		pid_philo;
	pthread_t	death_monitor;
	int			philo_number;
	time_t		last_supper;
	sem_t		*sem_eat;
	t_overall	*overall_data;
}	t_philo;


typedef struct s_overall
{
	t_philo		**philo;
	pthread_t	monitor_meal;
	int			n_philos;
	time_t		start_time;
	time_t		time_to_die;
	time_t		time_to_eat;
	time_t		time_to_sleep;
	int			n_suppers;
	sem_t		*sem_voice;
	sem_t		*sem_meal;
	sem_t		*sem_forks;
} t_overall;

t_overall	*init_overall(char **argv, int argc);
int			validate_inputs(int argc, char **argv);
int			not_int_limits(char *s);
int			ft_atoi(const char *s);
int			ft_strlen(char *s);
time_t		get_time(void);
void		start_philo(t_overall *all);
void		msg(t_overall *all, int philo_number, char *msg);
void		my_usleep(time_t time_in_ms);
void		kill_processes(t_overall *all);







#endif