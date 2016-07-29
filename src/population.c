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
 * @param size Number of individuals in the population.
 *             It's expected that this will remain constant
 * @param population The population to be created
 * @param system_definition Defines all of the programs within the system
 *                          and their possible versions/commits
 * @param goal The given goal
 * @returns zero on success
 */
int population_create(int size, sc_population * population,
					  sc_system * system_definition,
					  sc_goal * goal)
{
	int i, retval;

	if (size < 0)
		return 1;

	/* don't exceed array bounds */
	if (size > SC_MAX_POPULATION_SIZE)
		return 2;

	/* clear everything to ensure no stray values */
    memset((void*)population, '\0', sizeof(sc_population));

	population->size = size;
	population->individual =
		(sc_genome**)malloc(population->size*sizeof(sc_genome*));
	if (population->individual == NULL)
		return 3;
	population->mutation_rate = SC_DEFAULT_MUTATION_RATE;
	population->crossover = SC_DEFAULT_CROSSOVER;
	population->rebels = SC_DEFAULT_REBELS;

    /* Possibly this could be the same as an island index
       for deterministic islanded runs */
	population->random_seed = (unsigned int)time(NULL);

	memcpy((void*)&population->goal, (void*)goal, sizeof(sc_goal));
	memcpy((void*)&population->sys, (void*)system_definition,
		   sizeof(sc_system));

	/* Create an initially random population */
	for (i = 0; i < population->size; i++) {
		population->individual[i] = (sc_genome*)malloc(sizeof(sc_genome));
		if (population->individual[i] == NULL)
			return 30;
		retval = genome_create(population, population->individual[i]);
		if (retval != 0) {
			population_free(population);
			return 40 + retval;
		}
	}

	return 0;
}

/**
 * @brief Deallocates memory for a population
 * @param population Population object
 */
void population_free(sc_population * population)
{
	int i;

	for (i = 0; i < population->size; i++)
		free(population->individual[i]);

	free(population->individual);
}

/**
 * @brief Copies a population object
 *        Note that the destination populaion should *not* have
 *        been previously created
 * @param destination Population object to copy to
 * @param source Population object to copy from
 * @returns zero on success
 */
int population_copy(sc_population * destination, sc_population * source)
{
	int i;

	if (source->size < 1)
		return 1;

	if (source->size > SC_MAX_POPULATION_SIZE)
		return 2;

	destination->size = source->size;
	destination->mutation_rate = source->mutation_rate;
	destination->crossover = source->crossover;
	destination->rebels = source->rebels;
	destination->random_seed = source->random_seed;
	memcpy((void*)&destination->goal, (void*)&source->goal, sizeof(sc_goal));
	memcpy((void*)&destination->sys, (void*)&source->sys, sizeof(sc_system));

	/* allocate memory for the destination population */
	destination->individual =
		(sc_genome**)malloc(source->size*sizeof(sc_genome*));
	if (destination->individual == NULL)
		return 3;

	/* copy individuals */
	for (i = 0; i < source->size; i++) {
		destination->individual[i] = (sc_genome*)malloc(sizeof(sc_genome));
		if (destination->individual[i] == NULL)
			return 4;
		memcpy(destination->individual[i],
			   source->individual[i],sizeof(sc_genome));
	}

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
		population->individual[i]->spawning_probability =
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
	population->individual[index]->score =
		(float)test_passes /
		(float)(1 + population->individual[index]->steps);

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

	return population->individual[index]->score;
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
		score += population->individual[i]->score;
	}
	return score  / (float)population->size;
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
		if (population->individual[i]->score > max_score) {
			max_score = population->individual[i]->score;
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
			(population->individual[i]->score < min_score)) {
			min_score = population->individual[i]->score;
			index = i;
		}
	}
	return index;
}
