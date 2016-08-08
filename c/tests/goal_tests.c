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

void test_goal_create()
{
    sc_goal goal;
    sc_system sys;


    printf("test_goal_create...");

    //Create system part first
    test_system_dummy(&sys);

    /* TODO */
    goal_create_latest_versions(&sys, &goal);

    int p;
    for (p = 0; p < sys.no_of_programs; p++)
    {
        // All reference programs should be installed
        assert(goal.reference.installed[p] == 1);

        // Reference should be an upgraded version
        assert(goal.start.version_index[p] != goal.reference.version_index[p]);
    }

    printf("Ok\n");
}

void run_goal_tests()
{
    test_goal_create();
}
