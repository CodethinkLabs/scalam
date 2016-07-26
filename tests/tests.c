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

void test_file_exists()
{
	char * test_filename = "/tmp/scalam_test_file_exists";
	char cmdstr[SC_MAX_STRING];

	printf("test_file_exists...");

	sprintf(cmdstr, "touch %s", test_filename);
	run_shell_command(cmdstr);

	assert(file_exists(test_filename));

	sprintf(cmdstr, "rm %s", test_filename);
	run_shell_command(cmdstr);

	assert(!file_exists(test_filename));

	printf("Ok\n");
}

void test_software_exists()
{
	char * test_software = "nano";
	char cmdstr[SC_MAX_STRING];

	printf("test_software_exists...");

	assert(software_installed(test_software));

	char * test_software_non = "fooby_null";
	assert(!software_installed(test_software_non));

	printf("Ok\n");
}

void test_run_shell_command_with_output()
{
	char * commandstr = "echo 'foo'";
	char output[2048];

	printf("test_run_shell_command_with_output...");

	run_shell_command_with_output(commandstr, output);

	assert(strcmp(output, "foo")==0);

	printf("Ok\n");
}

void test_create_goal(sc_goal * goal)
{
	/* TODO make a test goal*/
}

void test_create_system(sc_system * system_definition)
{
	/* TODO create system definition */
}

void test_population_create()
{
	printf("test_population_create...");

	/* TODO
	sc_population population;
	sc_goal goal;
	sc_system system_definition;

	test_create_goal(&goal);

	test_create_system(&system_definition);

    assert(population_create(100, &population, &system_definition, &goal) == 0); */

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

void test_genome_mutate()
{
	printf("test_genome_mutate...");

    /* TODO
	sc_population population;
	sc_genome before, after;
	sc_goal goal;
	sc_system system_definition;

	test_create_goal(&goal);
	test_create_system(&system_definition);

    assert(population_create(100, &population, &system_definition, &goal) == 0);

    assert(genome_create(&population, &before) == 0);

	// copy before genome to after
	memcpy(&after, &before, sizeof(sc_genome));

	// the two genomes should be the same
	assert(memcmp(&after, &before, sizeof(sc_genome)) == 0);

	// now mutate the after genome
    assert(genome_mutate(&population, &after) == 0);

	// the two genomes should be different
	assert(memcmp(&after, &before, sizeof(sc_genome)) != 0); */

	printf("Ok\n");
}

void test_genome_spawn()
{
	printf("test_genome_spawn...");

	/* TODO
	sc_population population;
	sc_genome parent1, parent2, child;
	sc_goal goal;
	sc_system system_definition;

	test_create_goal(&goal);

	test_create_system(&system_definition);

    assert(population_create(100, &population, &system_definition, &goal) == 0);

	// create the parents
	assert(genome_create(&population, &parent1) == 0);
    assert(genome_create(&population, &parent2) == 0);

	// create a child
	assert(genome_spawn(&population, &parent1, &parent2, &child) == 0);

	// parents should be different
	assert(memcmp(&parent1, &parent2, sizeof(sc_genome)) != 0);

	// child should not be exactly like either parent
	assert(memcmp(&child, &parent1, sizeof(sc_genome)) != 0);
	assert(memcmp(&child, &parent2, sizeof(sc_genome)) != 0);
	*/

	printf("Ok\n");
}

void test_genome_create()
{
	printf("test_genome_create...");

	/* TODO
	sc_population population;
	sc_genome individual;
	sc_goal goal;
	sc_system system_definition;

	test_create_goal(&goal);

	test_create_system(&system_definition);

    assert(population_create(100, &population, &system_definition, &goal) == 0);

	assert(genome_create(&population, &individual) == 0); */

	printf("Ok\n");
}

void run_tests()
{
	printf("Running unit tests for %s version %s\n",
		   (char*)APPNAME, (char*)VERSION);

	test_file_exists();
	test_software_exists();
	test_run_shell_command_with_output();
	run_program_tests();

	test_population_create();
	test_population_next_generation();

	test_genome_spawn();
    test_genome_mutate();
	test_genome_create();

	printf("All tests passed\n");
}
