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
 * @brief Given a normalised evaluation score for a genome return the probability
 *        of reproduction. That is, the likelihood of being selected as a
 *        parent for the next generation
 * @param normalised_score Evaluation score in the range 0.0 -> 1.0
 * @returns Spawning probability.
 */
float population_reproduction_function(float normalised_score)
{
	return normalised_score * normalised_score;
}

/**
 * @brief Calculate the reproduction probability for each genome
 * @param population The population to be updated
 * @returns zero on success
 */
int population_spawning_probabilities(sc_population * population)
{
	int i, best_index, worst_index;
	float score_variance, normalised_score;

	/* get the indexes of the best and worst individuals */
	best_index = population_best_index(population);
	worst_index = population_worst_index(population);

	/* variation in score */
	score_variance =
		population_get_score(population, best_index) -
		population_get_score(population, worst_index);

	/* if there's no variance then either there's a catastrophic
	   diversity loss or there have been no evaluations yet */
	if (score_variance == 0) return 1;

	for (i = 0; i < population->size; i++) {
		/* score in the range 0.0 -> 1.0 */
		normalised_score =
			(population_get_score(population, i) -
			 population_get_score(population, worst_index))/
			score_variance;

		/* A simple probability of reproduction.
		   This function could be adjustable, so you could have
		   different islands with different reproduction strategies */
		population->individual[i].spawning_probability =
			population_reproduction_function(normalised_score);
	}

	return 0;
}

/**
 * @brief Creates the next generation
 * @param population The population to be updated after evaluation of genomes
 * @returns zero on success
 */
int population_next_generation(sc_population * population)
{
	if (population_spawning_probabilities(population) != 0) return 1;

	/* TODO */

	return 0;
}

/**
 * @brief Sets the evaluation score for a genome with the given array index
 * @param population The population after individuals have been evaluated
 * @param index Array index of the genome for an individual
 * @param test_passes The number of test passes from evaluation
 * @returns zero on success
 */
int population_set_test_passes(sc_population * population, int index, int test_passes)
{
	if (index < 0) return 1;
	if (index >= population->size) return 2;

	/* This division biases the score in favour of shorter upgrade sequences */
	population->individual[index].score =
		(float)test_passes /
		(float)population->individual[index].steps;

	return 0;
}

/**
 * @brief Returns the evaluation score for a genome with the given array index
 * @param population The population after individuals have been evaluated
 * @param index Array index of the genome for an individual
 * @returns Evaluation score (fitness)
 */
float population_get_score(sc_population * population, int index)
{
	if (index < 0) return 1;
	if (index >= population->size) return 2;

	return population->individual[index].score;
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
	float max_score = 0;
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

/**
 * @brief Returns the array index of the lowest scoring genome
 * @param population The population after individuals have been evaluated
 * @returns Array index of the lowest scoring genome, or -1 on failure
 */
int population_worst_index(sc_population * population)
{
	float min_score = 0;
	int i, index = -1;

	if (population->size <= 0) return 0;

	for (i = 0; i < population->size; i++) {
		if ((min_score == 0) ||
			(population->individual[i].score < min_score)) {
			min_score = population->individual[i].score;
			index = i;
		}
	}
	return index;
}
