/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_directory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:31:47 by nassm             #+#    #+#             */
/*   Updated: 2023/05/30 15:47:53 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	The function is used to add a new item to an array of strings (items).

	* The function get_next_item takes the following arguments: a string n,
	the array of strings items, a pointer to the size of the array (it_siz),
	and a pointer to the current index (i).

	* It checks if the current size of the array (*it_siz) is equal
	to the current index plus 2 ((*i + 2)). If they are equal,
	it means there is no more space in the array to add a new item.

	* If there is not enough space in the array, the function increases
	the size of the array by 10 (*it_siz += 10) and reallocates memory
	for the expanded array using ft_realloc_str_arr function.

	* If the reallocation fails (i.e., items is NULL),
	the function returns NULL to indicate an error.

	* If there is enough space or the reallocation succeeds, the function
	creates a duplicate of the string n using ft_strdup and assigns it to items[*i].

	* If the duplication fails (i.e., items(*i) is NULL), the function
	frees the memory allocated for the items array using
	ft_free_split function and returns NULL.

	* If the duplication succeeds,
	the function increments the index *i by 1 and returns the updated items array.
*/

static char	**get_next_item(char *n, char *items[], size_t  *it_siz, size_t *i)
{
	if (*it_siz == (*i + 2))
	{
		*it_siz += 10;
		items = ft_realloc_str_arr(items, *it_siz);
		if (items == NULL)
			return (NULL);
	}
	items[*i] = ft_strdup(n);
	if (items[*i] == NULL)
		return (ft_free_split(items));
	(*i)++;
	return (items);
}

/*
	The function is used to sort and concatenate
	an array of strings unsorted into a single string items.

	* It sorts the unsorted array of strings using
	the ft_sort_str_arr function.

	* It then iterates through the
	sorted unsorted array using a while loop until it
	reaches the end (i.e., unsorted[i] is NULL).

	* Inside the loop,
	it appends the current string unsorted[i]
	to the items string using the ft_append function.

	* If the appending operation fails (i.e., items is NULL),
	the function frees the memory allocated for the unsorted array
	using ft_free_split and returns NULL.

	* After appending the string,
	it also appends a space character to separate each item in the items string.

	* If the appending operation of the space character fails (items is NULL),
	the function frees the memory allocated for the unsorted array using
	ft_free_split and returns NULL.

	* After appending the string, it also appends a space character
	to separate each item in the items string.

	* If the appending operation of the space character fails
	(items is NULL), the function frees the memory allocated for the
	unsorted array using ft_free_split and returns NULL.

	* After the loop, it frees the memory allocated for
	the unsorted array using ft_free_split.
	
	* Finally, it returns the items string, which contains
	the sorted and concatenated items.
*/

static char	*get_items_sorted(char **unsorted)
{
	char	*items;
	int		i;
	
	items = NULL;
	unsorted = ft_sort_str_arr(unsorted);
	i = 0;
	while (unsorted[i])
	{
		items = ft_append(&items, unsorted[i]);
		if (items == NULL)
			return (ft_free_split(unsorted));
		items = ft_append(&items, " ");
		if (items == NULL)
			return (ft_free_split(unsorted));
		i++;
	}
	ft_free_split(unsorted);
	return (items);
}

/*
	The function is used to retrieve the namesof items
	in the current directory and return them as a sorted string.

	* It declares variables d of type DIR for the directory stream,
	dir of type struct dirent for directory entries,
	items as an array of strings, items_size for the current size
	of the items array, and i as the current index.
	
	* It opens the current directory using opendir(".")
	and assigns the directory stream to d.

	* It initializes i to 0 and items_size to 10
	
	* It reads the first directory entry using readdir(d)
	and assigns it to dir.

	* It allocates memory for the items array using
	ft_calloc to accommodate items_size strings plus
	an extra element for NULL termination.

	* It enters a loop that iterates while dir is not NULL.
	{
		- Inside the loop, it checks if the first character
		of dir->d_name is not a dot (hidden file/directory).
	
		- If it is not a dot, it calls the get_next_item
		function to add dir->d_name to the items array,
		updating items_size and i accordingly.
		
		- If adding the item fails (items is NULL),
		the function returns NULL.

		- It then reads the next directory entry using readdir(d)
		and updates dir accordingly.
	}
	
	* After the loop, it closes the directory stream using closedir(d).

	* Finally, it calls the get_items_sorted function,
	passing the items array, to sort and concatenate the items into a single string,
	and returns the result.
*/

char    *get_directory_items(void)
{
	DIR             *d;
	struct dirent   *dir;
	char            **items;
	size_t          items_size;
	size_t          i;

	d = opendir(".");
	if (d == NULL)
		return (NULL);
	i = 0;
	items_size = 10;
	dir = readdir(d);
	items = ft_calloc(items_size + 1, sizeof(*items));
	if (items == NULL)
		return (NULL);
	while (dir != NULL)
	{
		if (dir->d_name[0] != '.')
			items = get_next_item(dir->d_name, items, &items_size, &i);
		if (items == NULL)
			return (NULL);
		dir = readdir(d);
	}
	closedir(d);
	return (get_items_sorted(items));
}