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

/**
 * @brief Creates a goal to try to get to the latest versions
 * @param sys System object
 * @param goal Returned goal object
 * @returns zero on success
 */
int goal_create_latest_versions(sc_system * sys, sc_goal * goal)
{
	int p;

	/* Clear all values so that we begin with a known state */
	memset((void*)goal, '\0', sizeof(sc_goal));

	/* for every possible program */
	for (p = 0; p < sys->no_of_programs; p++) {
		/* Duplicate the current system state */
		goal->start.version_index[p] = sys->program[p].version_index;
		goal->start.installed[p] = sys->program[p].installed;

		/* goal is just all programs installed and on their final
		   commit (the head of master) */
		goal->reference.version_index[p] = sys->program[p].no_of_versions;
		goal->reference.installed[p] = 1;
	}

	return 0;
}

/**
 * @brief Calculates what the ideal end goal score is
 * @param goal Goal object
 * @returns score or negative on error
 */
float goal_max_score(sc_goal * goal)
{
	/* TODO */
	
	return 0.0;
}
