#include<stdlib.h>
#include<stdio.h>

#include"commit.h"

static int nextId;

/**
  * new_commit - alloue et initialise une structure commit correspondant aux
  *              parametres
  *
  * @major: numero de version majeure
  * @minor: numero de version mineure
  * @comment: pointeur vers une chaine de caracteres contenant un commentaire
  *
  * @return: retourne un pointeur vers la structure allouee et initialisee
  */
struct commit *new_commit(unsigned short major, unsigned long minor,
			  char *comment)
{
	struct commit *c = malloc(sizeof(struct commit));

	c->id = nextId++;
	c->version.major = major;
	c->version.minor = minor;
	c->version.flags = 0;
	c->comment = comment;
	c->major_parent = c;
	INIT_LIST_HEAD(&c->minor_head);
	INIT_LIST_HEAD(&c->major_head);
	return c;
}

/**
  * insert_commit - insere sans le modifier un commit dans la liste doublement
  *                 chainee
  *
  * @from: commit qui deviendra le predecesseur du commit insere
  * @new: commit a inserer - seuls ses champs next et prev seront modifies
  *
  * @return: retourne un pointeur vers la structure inseree
  */
static struct commit *insert_commit(struct commit *from, struct commit *new)
{
	list_add(&new->minor_head, &from->minor_head);
	if (new->major_parent == new)
		list_add(&new->major_head, &from->major_parent->major_head);
	return new;
}

/**
  * add_minor_commit - genere et insere un commit correspondant a une version
  *                    mineure
  *
  * @from: commit qui deviendra le predecesseur du commit insere
  * @comment: commentaire du commit
  *
  * @return: retourne un pointeur vers la structure inseree
  */
struct commit *add_minor_commit(struct commit *from, char *comment)
{
	struct commit *new = new_commit(
		from->version.major,
		from->version.minor + 1,
		comment
	);
	new->major_parent = from->major_parent;
	return insert_commit(from, new);
}

/**
	* add_major_commit - genere et insere un commit correspondant a une version
  *                    majeure
  *
  * @from: commit qui deviendra le predecesseur du commit insere
  * @comment: commentaire du commit
  *
  * @return: retourne un pointeur vers la structure inseree
  */
struct commit *add_major_commit(struct commit *from, char *comment)
{
	struct commit *new = new_commit(
		from->version.major + 1,
		0,
		comment
	);
	return insert_commit(from, new);
}

/**
  * del_commit - extrait le commit de l'historique
  *
  * @victim: commit qui sera sorti de la liste doublement chainee
  *
  * @return: retourne un pointeur vers la structure extraite
  */
struct commit *del_commit(struct commit *victim)
{
	list_del(&victim->minor_head);
	return victim;
}

/**
  * display_commit - affiche un commit : "2:  0-2 (stable) 'Work 2'"
  *
  * @c: commit qui sera affiche
  */
void display_commit(struct commit *c)
{
	printf("%3lu: ", c->id);
	display_version(&c->version, is_unstable_bis);
	printf("'%s'\n", c->comment);
}

/**
  * commitOf - retourne le commit qui contient la version passee en parametre
  *
  * @version: pointeur vers la structure version dont on recherche le commit
  *
  * @return: un pointeur vers la structure commit qui contient 'version'
  *
  * Note:      cette fonction continue de fonctionner meme si l'on modifie
  *            l'ordre et le nombre des champs de la structure commit.
  */
struct commit *commitOf(struct version *version)
{
	return container_of(version, struct commit, version);
}
