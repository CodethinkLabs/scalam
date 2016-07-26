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

void test_population_create()
{
	printf("test_population_create...");

	/* TODO
	sc_population population;
	sc_goal goal;
	sc_system system_definition;

	test_create_goal(&goal);

	test_create_system(&system_definition);

    assert(population_create(100, &population, &system_definition, &goal) == 0); */

	printf("Ok\n");
}

void test_population_next_generation()
{
	printf("test_population_next_generation...");

	/* TODO
	sc_population before, after;
	sc_goal goal;
	sc_system system_definition;

	test_create_goal(&goal);
	test_create_system(&system_definition);

    assert(population_create(100, &before, &system_definition, &goal) == 0);
	memcpy(&after, &before, sizeof(sc_population));
	assert(memcmp(&before, &after, sizeof(sc_population)) == 0);

    assert(population_next_generation(&after) == 0);
	assert(memcmp(&before, &after, sizeof(sc_population)) != 0);
	*/

	printf("Ok\n");
}

void run_population_tests()
{
	test_population_create();
	test_population_next_generation();
}
