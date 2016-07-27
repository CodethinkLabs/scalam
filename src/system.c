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
	/* TODO */

	/* find the subdirectories */

    /* set sys->no_of_programs */

	/* for each subdirectory (program repo) */

	/*     get list of commits,
		   similar to program_get_versions_from_repo
	       but for a directory rather than a url */

	/*     get the current checkout hash and convert it to an index number */

	/*     update sys->program[index] */

	return 0;
}
