/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 23:13:10 by junghan           #+#    #+#             */
/*   Updated: 2021/09/11 23:13:12 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

void				ft_bzero(void *s, size_t n);
size_t				ft_strlen(char *s);
size_t				ft_strlcpy(char *dest, char *src, size_t dstsize);
size_t				ft_strlcat(char *dest, char *src, size_t dstsize);
int					ft_atoi(char *str);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strdup(char *s1);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_itoa(int n);

#endif
