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
 * @brief Mutates a given genome
 * @param population The population in which the genome exists
 * @param individual The genome to be mutated
 * @returns zero on success
 */
int genome_mutate(sc_population * population, sc_genome * individual)
{
	/* TODO */
	return 0;
}

/**
 * @brief create a child from two parents
 * @param population The population in which the individuals exist
 * @param parent1 First parent
 * @param parent2 Second parent
 * @param child Returned child genome
 * @returns zero on success
 */
int genome_spawn(sc_population * population,
				 sc_genome * parent1, sc_genome * parent2,
				 sc_genome * child)
{
	/* TODO */
	return 0;
}

/**
 * @brief Ahistorically create a new individual
 * @param population The population in which the genome exists
 * @param individual The genome to be mutated
 */
int genome_create(sc_population * population, sc_genome * individual)
{
	/* TODO */
	return 0;
}
