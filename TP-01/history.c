#include<stdlib.h>
#include<stdio.h>

#include"history.h"

/**
  * new_history - alloue, initialise et retourne un historique.
  *
  * @name: nom de l'historique
  */
struct history *new_history(char *name)
{
	struct history *history = malloc(sizeof(struct history));

	history->commit_count = 0;
	history->commit_list = new_commit(0, 0, "");
	history->name = name;
	return history;
}

/**
  * last_commit - retourne l'adresse du dernier commit de l'historique.
  *
  * @h: pointeur vers l'historique
  */
struct commit *last_commit(struct history *h)
{
	return list_last_entry(&h->commit_list->minor_head, struct commit,
			       minor_head);
}

/**
  * display_history -
	return c; affiche tout l'historique, i.e. l'ensemble des commits de
  *                   la liste
  *
  * @h: pointeur vers l'historique a afficher
  */
void display_history(struct history *h)
{
	struct commit *commit;

	printf("\nHistorique de '%s' :\n", h->name);
	list_for_each_entry(commit, &h->commit_list->minor_head, minor_head) {
		display_commit(commit);
	}
}

/**
  * infos - affiche le commit qui a pour numero de version <major>-<minor> ou
  *         'Not here !!!' s'il n'y a pas de commit correspondant.
  *
  * @major: major du commit affiche
  * @minor: minor du commit affiche
  */
void infos(struct history *h, int major, unsigned long minor)
{
	struct commit *commit_maj;
	struct commit *commit_min;

	list_for_each_entry(commit_maj, &h->commit_list->major_head,
			    major_head) {
		if (commit_maj->version.major < major)
			continue;
		if (commit_maj->version.major > major)
			break;
		if (commit_maj->version.minor == minor)
			return display_commit(commit_maj);
		list_for_each_entry(commit_min, &commit_maj->minor_head,
				    minor_head) {
			if (commit_min->version.minor < minor)
				continue;
			if (commit_min->version.minor > minor)
				break;
			return display_commit(commit_min);
		}
	}
	printf("Not here !!!");
}

/**
 * freeHistory - Libère la memoire occupée par l'history.
 *
 * @from: le commit à partir duquel on veut libérer l'historique.
 */
void freeHistory(struct commit *from)
{
	struct commit *commit;
	struct commit *tmp;

	list_for_each_entry_safe(commit, tmp, &from->minor_head, minor_head) {
		free(commit);
	}
	free(commit);
}
