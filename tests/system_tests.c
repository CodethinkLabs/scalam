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

/**
 * @brief Creates a simple system to use in other test functions
 * @param sys System object
 * @returns zero on success
 */
void test_system_dummy(sc_system *sys)
{
	int retval, p;
	char * repo_url = "https://github.com/CodethinkLabs/frepo";
	char * checkout = "618e913171d2cf8e731bc0c4ab4516f395dddba0";
	char template[] = "/tmp/scalam.XXXXXX";
	char * repo_dir;
	char commandstr[SC_MAX_STRING];

	/* create a test directory which will contain repos */
	repo_dir = mkdtemp(template);

	/* clone repos into a test directory */
	sprintf(commandstr,"git clone %s %s/frepo 2> /dev/null",repo_url, repo_dir);
	run_shell_command(commandstr);
	/* do a checkout so that we're not at the HEAD of master */
	sprintf(commandstr,"cd %s/frepo\ngit checkout %s -b %s 2> /dev/null",
			repo_dir,checkout,checkout);
	run_shell_command(commandstr);

	retval = system_create_from_repos(sys, repo_dir);
	if (retval != 0) {
		printf("\nsystem_create_from_repos err %d\n", retval);
		sprintf(commandstr,"rm -rf %s", repo_dir);
		run_shell_command(commandstr);
	}
	assert(retval == 0);
	
	/* check that programs were actually created */
	for (p = 0; p < sys->no_of_programs; p++) {
		/* has a name */
		assert(sys->program[p].name[0] != 0);

		/* has some commits */
		assert(sys->program[p].no_of_versions > 0);

		/* has a versions.txt file */
		assert(sys->program[p].versions_file[0] != 0);

		/* non-zero current commit index */
		assert(sys->program[p].version_index > 0);

		/* check that we are not at HEAD of master */
		if (sys->program[p].version_index == sys->program[p].no_of_versions) {
			printf("\nversion_index is the same as the head of master\n");
			sprintf(commandstr,"rm -rf %s", repo_dir);
			run_shell_command(commandstr);
		}
		assert(sys->program[p].version_index < sys->program[p].no_of_versions);

		/* check that versions.txt file exists */
		assert(file_exists(sys->program[p].versions_file));
	}

	/*  remove the test directory.
		since this is only for testing we won't need
		to keep the files after struct creation (?).
	*/
	sprintf(commandstr,"rm -rf %s", repo_dir);
	run_shell_command(commandstr);	
	
}

void test_system_create_from_repos()
{
	sc_system sys;
	int retval, p;
	char * repo_url1 = "https://github.com/CodethinkLabs/frepo";
	char * checkout1 = "618e913171d2cf8e731bc0c4ab4516f395dddba0";
	char * repo_url2 = "https://github.com/CodethinkLabs/firehose";
	char * checkout2 = "c2bf2f9961bea6c382fe17bbf1057a58ce6a3d2b";
	char template[] = "/tmp/scalam.XXXXXX";
	char * repo_dir;
	char commandstr[SC_MAX_STRING];

	printf("test_system_create_from_repos...");

	/* create a test directory which will contain repos */
	repo_dir = mkdtemp(template);

	/* clone repos into a test directory */
	sprintf(commandstr,"git clone %s %s/frepo 2> /dev/null",repo_url1, repo_dir);
	run_shell_command(commandstr);
	/* do a checkout so that we're not at the HEAD of master */
	sprintf(commandstr,"cd %s/frepo\ngit checkout %s -b %s 2> /dev/null",
			repo_dir,checkout1,checkout1);
	run_shell_command(commandstr);

	sprintf(commandstr,"git clone %s %s/firehose 2> /dev/null",repo_url2, repo_dir);
	run_shell_command(commandstr);
	/* do a checkout so that we're not at the HEAD of master */
	sprintf(commandstr,"cd %s/firehose\ngit checkout %s -b %s 2> /dev/null",
			repo_dir,checkout2,checkout2);
	run_shell_command(commandstr);

	retval = system_create_from_repos(&sys, repo_dir);
	if (retval != 0) {
		printf("\nsystem_create_from_repos err %d\n", retval);
		sprintf(commandstr,"rm -rf %s", repo_dir);
		run_shell_command(commandstr);
	}
	assert(retval == 0);

	if (sys.no_of_programs != 2) {
		printf("sys.no_of_programs %d\n",sys.no_of_programs);
	}
	assert(sys.no_of_programs == 2);

	/* check that programs were actually created */
	for (p = 0; p < sys.no_of_programs; p++) {
		/* has a name */
		assert(sys.program[p].name[0] != 0);

		/* has some commits */
		assert(sys.program[p].no_of_versions > 0);

		/* has a versions.txt file */
		assert(sys.program[p].versions_file[0] != 0);

		/* non-zero current commit index */
		assert(sys.program[p].version_index > 0);

		/* check that we are not at HEAD of master */
		if (sys.program[p].version_index == sys.program[p].no_of_versions) {
			printf("\nversion_index is the same as the head of master\n");
			sprintf(commandstr,"rm -rf %s", repo_dir);
			run_shell_command(commandstr);
		}
		assert(sys.program[p].version_index < sys.program[p].no_of_versions);

		/* check that versions.txt file exists */
		assert(file_exists(sys.program[p].versions_file));
	}

	/* remove the test directory */
	sprintf(commandstr,"rm -rf %s", repo_dir);
	run_shell_command(commandstr);

	printf("Ok\n");
}

void run_system_tests()
{
    test_system_create_from_repos();
}
