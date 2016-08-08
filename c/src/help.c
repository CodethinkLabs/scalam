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

void show_help()
{
    printf("%s version %s\n\n", (char*)APPNAME, (char*)VERSION);

    printf(" -v --version             Show version number\n");
    printf(" -r --run                 Run a simulation\n");
    
    printf("\nSimulation mode:\n");
    printf(" %s -r|--run repos_dir max_generation\n", (char*)APPNAME);
    printf("  repos_dir               Directory where repo is located\n");
    printf("  max_generation          Maximum number of generations to simulate\n");
}
