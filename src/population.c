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
 * @brief For a given goal create a population of possible upgrade paths
 * @param population The population to be created
 * @param goal The given goal
 * @returns zero on success
 */
int population_create(sc_population * population, sc_goal goal)
{
	/* TODO */

	return 0;
}

/**
 * @brief Creates the next generation
 * @param population The population to be updated
 * @returns zero on success
 */
int population_next_generation(sc_population * population)
{
	/* TODO */

	return 0;
}

/**
 * @brief Returns the average fitness score for the population
 * @param population The population after individuals have been evaluated
 * @returns Average score
 */
float population_average_score(sc_population * population)
{
	float score = 0;
	int i;

	if (population->size <= 0) return 0;

	for (i = 0; i < population->size; i++) {
		score += (float)population->individual[i].score;
	}
	return score  / population->size;
}

/**
 * @brief Returns the array index of the top scoring genome
 * @param population The population after individuals have been evaluated
 * @returns Array index of the highest scoring genome, or -1 on failure
 */
int population_best_index(sc_population * population)
{
	int max_score = 0;
	int i, index = -1;

	if (population->size <= 0) return 0;

	for (i = 0; i < population->size; i++) {
		if (population->individual[i].score > max_score) {
			max_score = population->individual[i].score;
			index = i;
		}
	}
	return index;
}
