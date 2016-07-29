/*
	Smart search for upgrade paths
	Copyright (C) 2016 Andrew Leeming <andrew.leeming@codethink.co.uk> and
					   Bob Mottram <bob.mottram@codethink.co.uk>

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <assert.h>
#include "../src/scalam.h"

int test_create_system(sc_system * system_definition, char * repo_dir)
{
	int retval, p;
	char * repo_url1 = "https://github.com/CodethinkLabs/frepo";
	char * checkout1 = "618e913171d2cf8e731bc0c4ab4516f395dddba0";
	char * repo_url2 = "https://github.com/CodethinkLabs/firehose";
	char * checkout2 = "c2bf2f9961bea6c382fe17bbf1057a58ce6a3d2b";
	char commandstr[SC_MAX_STRING];

	/* clone repos into a test directory */
	sprintf(commandstr,"git clone %s %s/frepo",repo_url1, repo_dir);
	run_shell_command(commandstr);
	/* do a checkout so that we're not at the HEAD of master */
	sprintf(commandstr,"cd %s/frepo\ngit checkout %s -b %s",
			repo_dir,checkout1,checkout1);
	run_shell_command(commandstr);

	sprintf(commandstr,"git clone %s %s/firehose",repo_url2, repo_dir);
	run_shell_command(commandstr);
	/* do a checkout so that we're not at the HEAD of master */
	sprintf(commandstr,"cd %s/firehose\ngit checkout %s -b %s",
			repo_dir,checkout2,checkout2);
	run_shell_command(commandstr);

	return system_create_from_repos(system_definition, repo_dir);
}

void test_population_create()
{
	sc_population population;
	sc_system system_definition;
	sc_goal goal;
	char commandstr[SC_MAX_STRING];
	char * repo_dir;
	char template[] = "/tmp/scalam.XXXXXX";

	printf("test_population_create...");

	/* create a test directory which will contain repos */
	repo_dir = mkdtemp(template);

	/* make a test system with some repositories */
	assert(test_create_system(&system_definition, repo_dir) == 0);

	/* make a goal to get to the latest commits */
	assert(goal_create_latest_versions(&system_definition, &goal) == 0);

	/* generate the population */
    assert(population_create(100, &population, &system_definition, &goal) == 0);

	/* deallocate population */
	population_free(&population);

	sprintf(commandstr,"rm -rf %s", repo_dir);
	run_shell_command(commandstr);

	printf("Ok\n");
}

void test_population_next_generation()
{
	printf("test_population_next_generation...");

	/* TODO
	sc_population before, after;
	sc_goal goal;
	sc_system system_definition;

	test_create_goal(&goal);
	test_create_system(&system_definition);

    assert(population_create(100, &before, &system_definition, &goal) == 0);
	memcpy(&after, &before, sizeof(sc_population));
	assert(memcmp(&before, &after, sizeof(sc_population)) == 0);

    assert(population_next_generation(&after) == 0);
	assert(memcmp(&before, &after, sizeof(sc_population)) != 0);
	*/

	printf("Ok\n");
}

void run_population_tests()
{
	test_population_create();
	test_population_next_generation();
}
