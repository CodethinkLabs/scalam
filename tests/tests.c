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

void run_tests()
{
	printf("Running unit tests for %s version %s\n",
		   (char*)APPNAME, (char*)VERSION);

	test_file_exists();
	test_software_exists();
	test_run_shell_command_with_output();
	run_program_tests();
	run_population_tests();
	run_genome_tests();

	printf("All tests passed\n");
}
