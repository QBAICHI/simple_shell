#include "shell.h"

/**
 * _myhistory - displays the history list, one command per line, preceded
 *              by line numbers starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return 0;
}

/**
 * unset_alias - unsets an alias by deleting it from the alias list.
 * @info: parameter struct
 * @str: the string representing the alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *equal_sign, c;
	int ret;

	equal_sign = _strchr(str, '=');
	if (!equal_sign)
		return 1;

	c = *equal_sign;
	*equal_sign = '\0';
	ret = delete_node_at_index(&(info->alias), get_node_index(info->alias,
	                                 node_starts_with(info->alias, str, -1)));
	*equal_sign = c;
	return ret;
}

/**
 * set_alias - sets an alias by adding it to the alias list.
 * @info: parameter struct
 * @str: the string representing the alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *equal_sign;

	equal_sign = _strchr(str, '=');
	if (!equal_sign)
		return 1;

	if (!*++equal_sign)
		return unset_alias(info, str);

	unset_alias(info, str);
	return add_node_end(&(info->alias), str, 0) == NULL;
}

/**
 * print_alias - prints an alias string.
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *equal_sign = NULL, *alias_str = NULL;

	if (node)
	{
		equal_sign = _strchr(node->str, '=');
		for (alias_str = node->str; alias_str <= equal_sign; alias_str++)
			_putchar(*alias_str);
		_putchar('\'');
		_puts(equal_sign + 1);
		_puts("'\n");
		return 0;
	}
	return 1;
}

/**
 * _myalias - mimics the alias builtin (man alias).
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myalias(info_t *info)
{
	int i;
	char *equal_sign = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return 0;
	}

	for (i = 1; info->argv[i]; i++)
	{
		equal_sign = _strchr(info->argv[i], '=');
		if (equal_sign)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return 0;
}

