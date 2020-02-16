#include "history.h"
#include "commit.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
	struct history *h = new_history("history");
	struct commit *c;

	c = add_minor_commit(h->commit_list, "test 1");
	c = add_minor_commit(c, "test 2");
	c = add_major_commit(c, "test 3");
	c = add_minor_commit(c, "test 4");
	c = add_minor_commit(c, "test 5");
	c = add_minor_commit(c, "test 6");
	c = add_minor_commit(c, "test 7");
	display_history(h);
	freeHistory(h->commit_list);
	free(h);
	exit(0);
}
