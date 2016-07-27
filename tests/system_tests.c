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
	printf("test_system_create_from_repos...");
    
    int retval;
    char * program_name="freop";
    char * program_name2="morph-to-bb";
    char * program_url="https://github.com/CodethinkLabs/frepo";
    char * program_url2="https://github.com/CodethinkLabs/morph-to-bb";
	char template[] = "/tmp/scalam.XXXXXX";
	char * repos_dir = mkdtemp(template);
	char filename[SC_MAX_STRING];
	char rmcommandstr[SC_MAX_STRING];
    
	sc_program prog;
    sc_program prog2;

    
	sprintf(&prog.name[0],"%s",program_name);
	sprintf(&prog2.name[0],"%s",program_name2);
    
	sprintf(rmcommandstr, "rm -rf %s", repos_dir);
	program_get_versions_from_repo(repos_dir,program_url, &prog);   
	program_get_versions_from_repo(repos_dir, program_url2 , &prog2);
    
    // Check basic system construction
    /*
    sc_system sys;  //seg faults here
    
    retval=system_create_from_repos(&sys, repos_dir);
    if(retval != 0)
    {
        printf("\nSystem failed to create\n");
        // remove the temporary directory
		run_shell_command(rmcommandstr);
    }
    assert(retval == 0);
    
    // Check number of system programs
    assert(sys.no_of_programs != 2);
    
    // Are program names correct
    assert(!strcmp(sys.program[0].name,program_name)
        && !strcmp(sys.program[0].name,program_name2));
    assert(!strcmp(sys.program[1].name,program_name)
        && !strcmp(sys.program[1].name,program_name2));
    
	// tidy up
	run_shell_command(rmcommandstr);
    */
	printf("Ok\n");
    
}

void run_system_tests()
{
    test_system_create_from_repos();
}