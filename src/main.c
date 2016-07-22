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

#include <stdio.h>
#include <string.h>
#include "scalam.h"

void show_help()
{
	printf("%s version %s\n\n", (char*)APPNAME, (char*)VERSION);

	printf(" -v --version             Show version number\n");
}

int main(int argc, char **argv)
{
	int i;

	if (argc <= 1) {
		show_help();
		return 0;
	}

	for (i = 1; i < argc; i++) {
		/* show help */
		if ((strcmp(argv[i],"-h")==0) ||
			(strcmp(argv[i],"--help")==0)) {
			show_help();
		}
	}

	return 0;
}
