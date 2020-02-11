#include "version.h"
#include <stdio.h>

struct commit
{
	unsigned long id;
	struct version version;
	char *comment;
	struct commit *next;
	struct commit *prev;
};

void print_commit(struct commit *commit)
{
	printf(
		"id: %p\nversion: %p\n",
		&commit->id,
		&commit->version);
}

struct commit *commit_of(struct version *version)
{
	struct commit c;
	int diff = (char *)&c.version - (char *)&c;
	return (struct commit *) ((char *)version - diff);
}

int main(int argc, char const *argv[])
{
	char comment[10];
	struct commit commit = {
		.id = 2345,
		.version = {
			.major = 3,
			.minor = 5,
			.flags = 0},
		.comment = comment};
	struct version *v = &commit.version;
	print_commit(&commit);
	struct commit *test = commit_of(v);
	print_commit(test);
	return 0;
}
