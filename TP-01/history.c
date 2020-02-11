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
	return list_last_entry(&h->commit_list->head, struct commit, head);
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
	list_for_each_entry(commit, &h->commit_list->head, head) {
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
	struct commit *commit;

	list_for_each_entry(commit, &h->commit_list->head, head) {
		if (commit->version.major == major &&
		    commit->version.minor == minor) {
			display_commit(commit);
			return;
		}
	}
	printf("Not here !!!");
}
