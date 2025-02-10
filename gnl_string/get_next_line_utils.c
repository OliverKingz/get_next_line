/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:35:11 by ozamora-          #+#    #+#             */
/*   Updated: 2025/01/09 14:46:31 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);

/**
 * ft_strdup - Duplicates a string by allocating memory for it first.
 * 
 * @s: The string to duplicate.
 * 
 * Return: Pointer to the newly allocated duplicate string, or NULL 
 *         if memory allocation fails.
 * 
 * Edge cases checked:
 * - Does not handle NULL input, to replicate the origina function.
 */
char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	s_len;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	dup = (char *)malloc((s_len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && i < s_len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

/**
 * ft_strchr - Locates the first occurrence of a character in a string.
 * 
 * @s: The string to be searched.
 * @c: The character to locate in the string.
 * 
 * Return: A pointer to the first occurrence of the character 'c' in the 
 *         string 's', or NULL if the character is not found.
 * 
 * Edge cases checked:
 * - Handles NULL string input.
 */
char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (1)
	{
		if (*s == (char)c)
			return ((char *)s);
		if (*s == '\0')
			break ;
		s++;
	}
	return (NULL);
}

/**
 * ft_strjoin - Allocates (with malloc) and returns a new string,
 *              which is the result of the concatenation of 's1' and 's2'.
 *
 * @s1: The first string. If NULL, treated as an empty string.
 * @s2: The string to add to 's1'. If NULL, treated as an empty string.
 *
 * Return: The newly allocated string resulting from the concatenation
 *         of 's1' and 's2'. Returns NULL if the memory allocation fails.
 *
 * Note: Uses malloc, so the caller is responsible for freeing the memory
 * allocated for the resulting string when it is no longer needed.
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	int		s1_len;
	int		s2_len;
	int		i;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	joined = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!joined)
		return (NULL);
	i = 0;
	while (i < s1_len)
	{
		joined[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < s2_len)
	{
		joined[s1_len + i] = s2[i];
		i++;
	}
	joined[s1_len + s2_len] = '\0';
	return (joined);
}

/**
 * ft_strlen - Calculates the length of a string.
 * 
 * @s: The string to measure.
 * 
 * Return: The length of the string.
 */
size_t	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return ((size_t)len);
}

/**
 * ft_substr - Creates a substring from a string.
 * 
 * @s: The string to create a substring from.
 * @start: The index of the character in 's' to start from.
 * @len: The maximum length of the substring.
 * 
 * Return: The resulting substring, or NULL if memory allocation fails.
 * 
 * Notes:
 * - If 'start' is beyond the length of 's', an empty string is returned.
 * - The function adjusts 'len' to ensure it does not exceed the length of 's' 
 *   starting from 'start'.
 * - Handles NULL input by returning NULL.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	s_len;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		len = 0;
	else if (len > s_len - start)
		len = s_len - start;
	subs = (char *) malloc((len + 1) * sizeof(char));
	if (!subs)
		return (NULL);
	i = 0;
	if (start < s_len)
	{
		while (s[start + i] != '\0' && i < len)
		{
			subs[i] = s[start + i];
			i++;
		}
	}
	subs[i] = '\0';
	return (subs);
}
