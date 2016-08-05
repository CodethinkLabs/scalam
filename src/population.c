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
 * @brief Assigns one genome in the population to try going straight
 *        to the goal, with no intermediate upgrade steps
 * @param population The population object
 * @returns The array index of the genome which was selected
 */
int population_create_direct_ascent_genome(sc_population * population)
{
    int index, ctr = 0;

    /* is there already a genome with zero upgrade steps? */
    for (index = 0; index < population->size; index++) {
        if (population->individual[index]->steps == 0) return index;
    }

    /* Pick a random genome in the population.
       Possibly this index could be zero if we are evaluating
       genomes sequentially. */
    index = rand_num(&population->random_seed) % population->size;

    /* set its steps to zero so that it tries to go straight to the goal */
    population->individual[index]->steps = 0;

    return index;
}

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
    population->next_generation =
        (sc_genome**)malloc(population->size*sizeof(sc_genome*));
    if (population->next_generation == NULL)
        return 4;
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
            return 5;
        population->next_generation[i] = (sc_genome*)malloc(sizeof(sc_genome));
        if (population->next_generation[i] == NULL)
            return 6;
        retval = genome_create(population, population->individual[i]);
        if (retval != 0) {
            population_free(population);
            return 70 + retval;
        }
    }

    population_create_direct_ascent_genome(population);

    return 0;
}

/**
 * @brief Deallocates memory for a population
 * @param population Population object
 */
void population_free(sc_population * population)
{
    int i;

    /* free the individual genomes */
    for (i = 0; i < population->size; i++) {
        free(population->individual[i]);
        free(population->next_generation[i]);
    }

    free(population->individual);
    free(population->next_generation);

    /* free the system */
    system_free(&population->sys);
}

/**
 * @brief Returns true if the given genome is unique.
 *        This is used during creation of the next generation to ensure that the
 *        same upgrade hypothesis doesn't get evaluated more than once
 * @param population The population object
 * @param genome The genome to be tested
 * @param genome_index Index for the current number of next generation genomes
 *                     which have been created thus far
 * @param next_generation Use the next generation (1) or the current generation (0)
 * @returns True if the given genome is unique
 */
int genome_unique(sc_population * population,
                  sc_genome * genome, int genome_index,
                  int next_generation)
{
    int i;
    sc_genome ** genome_array = population->next_generation;

    if (next_generation == 0)
        genome_array = population->individual;

    for (i = 0; i < genome_index; i++) {
        if (genome_array[i]->steps != genome->steps)
            continue;
        if (memcmp((void*)&genome_array[i]->change,
                   genome->change, genome->steps*sizeof(sc_system_state)) == 0)
            return 0;
    }
    return 1;
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
    system_copy(&destination->sys, &source->sys);

    /* allocate memory for the destination population */
    destination->individual =
        (sc_genome**)malloc(source->size*sizeof(sc_genome*));
    if (destination->individual == NULL)
        return 3;

    destination->next_generation =
        (sc_genome**)malloc(source->size*sizeof(sc_genome*));
    if (destination->next_generation == NULL)
        return 4;

    /* copy individuals */
    for (i = 0; i < source->size; i++) {
        destination->individual[i] = (sc_genome*)malloc(sizeof(sc_genome));
        if (destination->individual[i] == NULL)
            return 5;

        destination->next_generation[i] = (sc_genome*)malloc(sizeof(sc_genome));
        if (destination->next_generation[i] == NULL)
            return 6;

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
 * @brief sorts the current generation in order of their spawning probability
 * @param population The population to be updated after evaluation of genomes
 * @returns zero on success
 */
int population_sort(sc_population * population)
{
    int i, j, winner;
    float max;
    sc_genome * temp_genome;

    for (i = 0; i < population->size-1; i++) {
        /* look for the highest spawning probability */
        max = population->individual[i]->spawning_probability;
        winner = i;
        for (j = i+1; j < population->size; j++) {
            if (population->individual[j]->spawning_probability > max) {
                max = population->individual[j]->spawning_probability;
                winner = j;
            }
        }
        if (winner != i) {
            /* genomes swap places */
            temp_genome = population->individual[winner];
            population->individual[winner] = population->individual[i];
            population->individual[i] = temp_genome;
        }
    }
    return 0;
}

/**
 * @brief Randomly picks a parent genome with a bias towards
 *        higher scores
 * @param population The population to be updated after evaluation of genomes
 * @returns Pointer to the parent genome
 */
sc_genome * population_parent(sc_population * population)
{
    /* a random value between 0.0 and 1.0 */
    float r = (rand_num(&population->random_seed)%100000)/100000.0f;

    /* Get a population array index from this random number,
       biasing towards small values. Different functions could
       be used here. */
    int index = (int)(r*r*(population->size-1));

    return population->individual[index];
}

/**
 * @brief Creates the next generation
 * @param population The population to be updated after evaluation of genomes
 * @returns zero on success
 */
int population_next_generation(sc_population * population)
{
    sc_genome ** temp_buffer;
    int i, retval, tries;

    /* update spawning probabilities */
    if (population_spawning_probabilities(population) != 0)
        return 1;

    /* sort the population in order of spawning probability */
    if (population_sort(population) != 0)
        return 2;

    /* create the children of the next generation */
    for (i = 0; i < population->size; i++) {
        tries = 0;
        do {
            retval = genome_spawn(population,
                                  population_parent(population),
                                  population_parent(population),
                                  population->next_generation[i]);
            if (retval != 0)
                return 30 + retval;

            /* if there is repeated failure to create a unique
               child genome */
            tries++;
            if (tries > SC_MAX_TRIES_FOR_UNIQUE_GENOME)
                return 4;
        } while (!genome_unique(population,
                                population->next_generation[i], i, 1));
    }

    /* swap the arrays over, so the new generation is now
       the current one */
    temp_buffer = population->next_generation;
    population->next_generation = population->individual;
    population->individual = temp_buffer;

    /* one genome tries to go straight to the goal */
    population_create_direct_ascent_genome(population);

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
    if (index < 0)
        return -1;

    if (index >= population->size)
        return -2;

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
 * @brief Returns the best score for the given population
 * @param population The population after individuals have been evaluated
 * @returns The best score within the population
 */
float population_best_score(sc_population * population)
{
    int index = population_best_index(population);
    if (index > -1)
        return population->individual[index]->score;
    return 0;
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

/**
 * @brief Returns the RMS variance of scores within the population
 * @param population The population after individuals have been evaluated
 * @returns RMS score variance
 */
float population_variance(sc_population * population)
{
    int i;
    float average_score = population_average_score(population);
    float diff, variance = 0;

    if ((population->size <= 0) || (average_score <= 0))
        return 0;

    for (i = 0; i < population->size; i++) {
        diff = population->individual[i]->score - average_score;
        variance += diff*diff;
    }
    return (float)sqrt(variance / (float)population->size);
}
