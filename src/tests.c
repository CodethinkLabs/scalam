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
#include "scalam.h"

int file_exists(char * filename)
{
	FILE * fp;

	fp = fopen(filename, "r");
	if (fp) {
		fclose(fp);
		return 1;
	}
	return 0;
}

void test_program_get_versions()
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

	printf("test_program_get_versions...");

	sprintf(rmcommandstr, "rm -rf %s", repos_dir);
	assert(program_get_versions(repos_dir, repo_url, program_name) == 0);

	/* check that the versions file was created */
	sprintf(filename, "%s/%s/versions.txt", repos_dir, program_name);
	if (file_exists(filename) == 0) {
		/* remove the temporary directory */
		run_shell_command(rmcommandstr);
	}
	assert(file_exists(filename) != 0);

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

void run_tests()
{
	printf("Running unit tests for %s version %s\n",
		   (char*)APPNAME, (char*)VERSION);

	test_program_get_versions();

	printf("All tests passed\n");
}
