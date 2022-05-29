/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syolando <syolando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 13:54:50 by syolando          #+#    #+#             */
/*   Updated: 2022/05/29 14:20:13 by syolando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	print_action(t_philo *philo, char *action)
{
	time_t time;

	time = get_time() - philo->overall_data->start_time;
	printf("%ld %d %s\n", time, philo->number, action);
}