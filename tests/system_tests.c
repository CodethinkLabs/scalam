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

void test_system_create_from_repos()
{
	sc_system sys;
	int retval, p;
	char * repo_url1 = "https://github.com/CodethinkLabs/frepo";
	char * repo_url2 = "https://github.com/CodethinkLabs/firehose";
	char template[] = "/tmp/scalam.XXXXXX";
	char * repo_dir;
	char commandstr[SC_MAX_STRING];

	printf("test_system_create_from_repos...");

	/* create a test directory which will contain repos */
	repo_dir = mkdtemp(template);

	/* clone repos into a test directory */
	sprintf(commandstr,"git clone %s %s/frepo",repo_url1, repo_dir);
	run_shell_command(commandstr);
	sprintf(commandstr,"git clone %s %s/firehose",repo_url2, repo_dir);
	run_shell_command(commandstr);

	retval = system_create_from_repos(&sys, repo_dir);
	if (retval != 0) {
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
		assert(sys.program[p].name[0] != 0);
		assert(sys.program[p].no_of_versions > 0);
		assert(sys.program[p].versions_file[0] != 0);
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
