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

void test_program_get_versions_from_git()
{
	int retval;
	char * repo_url = "https://github.com/CodethinkLabs/frepo";
	char * program_name = "frepo";
	int line_number = 5;
	char * expected_commit = "3c74943";
	char template[] = "/tmp/scalam.XXXXXX";
	char * repos_dir = mkdtemp(template);
	char filename[SC_MAX_STRING];
	char rmcommandstr[SC_MAX_STRING];
	char commitstr[SC_MAX_STRING];
	sc_program prog;

	printf("test_program_get_versions_from_git...");

	sprintf(&prog.name[0],"%s",program_name);
	sprintf(rmcommandstr, "rm -rf %s", repos_dir);
	assert(program_get_versions_from_repo(repos_dir, repo_url, &prog) == 0);

	/* check that the versions file was created */
	sprintf(filename, "%s/%s/versions.txt", repos_dir, program_name);
	assert(file_exists(filename));

	retval=get_line_from_file(filename, line_number, commitstr);
	if (retval != 0) {
		printf("\nCommit line %d not found\n", line_number);
		/* remove the temporary directory */
		run_shell_command(rmcommandstr);
	}
	assert(retval==0);

	retval = strcmp(commitstr,expected_commit);
	if (retval != 0) {
		printf("\nCommit not expected\n");
		/* remove the temporary directory */
		run_shell_command(rmcommandstr);
	}
	assert(retval==0);

	/* tidy up */
	run_shell_command(rmcommandstr);

	printf("Ok\n");
}

void test_program_get_versions_from_changelog()
{
	printf("test_program_get_versions_from_changelog...");

	/* TODO */

	printf("Ok\n");
}

void test_program_get_versions_from_tarball()
{
	printf("test_program_get_versions_from_tarball...");

	/* TODO */

	printf("Ok\n");
}

void test_program_get_versions_from_aptitude()
{
	int retval;
	char * program_name = "vim";
	int line_number = 5;
	char * expected_commit = "4.5-3"; //"2:7.4.488-3";
	char template[] = "/tmp/scalam.XXXXXX";
	char * repos_dir = mkdtemp(template);
	char filename[SC_MAX_STRING];
	char rmcommandstr[SC_MAX_STRING];
	char commitstr[SC_MAX_STRING];
	sc_program prog;

	printf("test_program_get_versions_from_aptitude...");

	sprintf(&prog.name[0],"%s",program_name);
	sprintf(rmcommandstr, "rm -rf %s", repos_dir);
	assert(program_get_versions_from_aptitude(repos_dir, &prog) == 0);

	/* check that the versions file was created */
	sprintf(filename, "%s/%s/versions.txt", repos_dir, program_name);
	assert(file_exists(filename));

	retval=get_line_from_file(filename, line_number, commitstr);
	if (retval != 0) {
		printf("\nCommit line %d not found\n", line_number);
		/* remove the temporary directory */
		run_shell_command(rmcommandstr);
	}
	assert(retval==0);

	/* Remove trailing newline */
	commitstr[strcspn(commitstr, "\n")] = 0;
	retval = strcmp(commitstr,expected_commit);
	if (retval != 0) {
		printf("\nCommit not expected\n");
		/* remove the temporary directory */
		run_shell_command(rmcommandstr);
	}
	assert(retval==0);

	/* tidy up */
	run_shell_command(rmcommandstr);

	printf("Ok\n");
}

void test_program_name_is_valid()
{
	sc_program prog;

	printf("test_program_name_is_valid...");

	sprintf(&prog.name[0], "%s", "validprogram");
	assert(program_name_is_valid(&prog) == 0);

	/* can include capitals */
	sprintf(&prog.name[0], "%s", "ValidProgram");
	assert(program_name_is_valid(&prog) == 0);

	/* empty program name is not valid */
	sprintf(&prog.name[0], "%s", "");
	assert(program_name_is_valid(&prog) != 0);

	/* null program name is not valid */
	prog.name[0] = 0;
	assert(program_name_is_valid(&prog) != 0);

	/* invalid program names */
	sprintf(&prog.name[0], "%s", "^£!");
	assert(program_name_is_valid(&prog) != 0);

	printf("Ok\n");
}

void test_program_get_versions_from_deb_package()
{
	printf("test_program_get_versions_from_deb_package...");

	/* TODO */

	printf("Ok\n");
}

void test_program_get_versions_from_rpm_package()
{
	printf("test_program_get_versions_from_rpm_package...");

	int retval;
	char * repo_url = "http://download1.rpmfusion.org/free/fedora/updates/24/SRPMS/r/rfpkg-1.23.4-1.fc24.src.rpm";
	char * program_name = "rfpkg";
	int line_number = 5;
	char * expected_commit = "1.21-1";
	char template[] = "/tmp/scalam.XXXXXX";
	char * repos_dir = mkdtemp(template);
	char filename[SC_MAX_STRING];
	char rmcommandstr[SC_MAX_STRING];
	char commitstr[SC_MAX_STRING];
	sc_program prog;

	sprintf(&prog.name[0],"%s",program_name);
	sprintf(rmcommandstr, "rm -rf %s", repos_dir);
	assert(program_get_versions_from_rpm_package(repos_dir, repo_url, &prog) == 0);

	/* check that the versions file was created */
	sprintf(filename, "%s/%s/versions.txt", repos_dir, program_name);
	assert(file_exists(filename));

	retval=get_line_from_file(filename, line_number, commitstr);
	if (retval != 0) {
		printf("\nCommit line %d not found\n", line_number);
		/* remove the temporary directory */
		run_shell_command(rmcommandstr);
	}
	assert(retval==0);

	retval = strcmp(commitstr,expected_commit);
	if (retval != 0) {
		printf("\nCommit not expected\n");
		/* remove the temporary directory */
		run_shell_command(rmcommandstr);
	}
	assert(retval==0);

	/* tidy up */
	run_shell_command(rmcommandstr);


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

void test_program_version_from_index()
{
	FILE * fp;
	char * test_filename = "/tmp/test_program_version_from_index";
	sc_program prog;
	char str[SC_MAX_STRING];

	printf("test_program_version_from_index...");

	/* create a test file with a number of lines */
	fp = fopen(test_filename, "w");
	assert(fp);
	fprintf(fp, "%s", "foobars\nfor\nthe\nfoobar\ngod");
	fclose(fp);

	assert(lines_in_file(test_filename) == 5);

	sprintf(&prog.versions_file[0],"%s",test_filename);
	prog.no_of_versions = lines_in_file(test_filename);

	str[0] = 0;
	assert(program_version_from_index(&prog, 0, str) == 0);
	assert(strcmp(str, "god") == 0);

	str[0] = 0;
	assert(program_version_from_index(&prog, 1, str) == 0);
	assert(strcmp(str, "foobar") == 0);

	str[0] = 0;
	assert(program_version_from_index(&prog, 3, str) == 0);
	assert(strcmp(str, "for") == 0);

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
	test_program_name_is_valid();
	test_program_version_from_index();
	test_program_get_versions_from_git();
	test_program_get_versions_from_changelog();
	test_program_get_versions_from_tarball();
	test_program_get_versions_from_deb_package();
	test_program_get_versions_from_rpm_package();
	test_program_version_from_index();
	test_program_get_versions_from_aptitude();

	test_population_create();
	test_population_next_generation();

	test_genome_spawn();
    test_genome_mutate();
	test_genome_create();

	printf("All tests passed\n");
}
