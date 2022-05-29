/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syolando <syolando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 13:54:50 by syolando          #+#    #+#             */
/*   Updated: 2022/05/30 01:36:08 by syolando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdio.h>

void	msg(t_overall *all, int philo_number, char *msg)
{
	sem_wait(all->sem_voice);
	printf("%ld philosopher %d %s\n", get_time() - all->start_time,
		philo_number + 1, msg);
}