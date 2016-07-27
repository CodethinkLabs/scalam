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

#include "scalam.h"

int system_create_from_repos(sc_system * sys, char * repos_dir)
{
	char commandstr[SC_MAX_STRING];
	char directories[SC_MAX_STRING];
	char current_directory[SC_MAX_STRING];
	char full_directory[SC_MAX_STRING];
	char current_commit[SC_MAX_STRING];
	char head_commit[SC_MAX_STRING];
	int i, ctr;

	/* TODO */

	/* find the subdirectories */
	sprintf(commandstr, "cd %s\nls -F | grep /", repos_dir);
	if (run_shell_command_with_output(commandstr, directories) != 0)
		return 1;
	if (directories[0] == 0)
		return 2;

	current_directory[0] = 0;
	ctr = 0;
	sys->no_of_programs = 0;
	for (i = 0; i < strlen(directories); i++) {
		if ((directories[i] != '\n') && (i < strlen(directories)-1)) {
			/* read the directory name */
			if (directories[i] != '/')
				current_directory[ctr++] = directories[i];
		}
		else {
			/* string terminator */
			current_directory[ctr] = 0;

			/* the full path for the program repo */
			sprintf(full_directory,"%s/%s",repos_dir,current_directory);

			/* update the details for this program */
			if (program_repo_get_commits(full_directory,
										 &sys->program[sys->no_of_programs]) != 0)
				return 3;

			sys->no_of_programs++;
		}
	}

	return 0;
}
