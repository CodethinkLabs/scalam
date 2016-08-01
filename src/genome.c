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

	/* Depending on the strategy, increment a single or jump to goal */


	/* Pick a random gene (software) to mutate */
	int gene_index =
		rand_num(&individual->random_seed) % population->sys.no_of_programs;

	sc_system_state state = individual->change[individual->steps];
	/* Increment or decrement the version index */
	if (rand_num(&individual->random_seed) % 2 == 0)
		state.version_index[gene_index]++;
	else
		state.version_index[gene_index]--;


	// state->installed[gene_index]=?

	individual->steps++;

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
	int install_step, p;
	sc_genome * parent;

	/* check that objects have been allocated */
	if (population == NULL) return 1;
	if (parent1 == NULL) return 2;
	if (parent2 == NULL) return 3;
	if (child == NULL) return 4;

	/* number of steps in the upgrade sequence inherited from one
	   parent or the other */
	child->steps = parent1->steps;
	if (rand_num(&parent1->random_seed)%100 > 50)
		child->steps = parent2->steps;

	child->score = 0;
	child->spawning_probability = 0;

	/* Set random number generator seed */
	if (rand_num(&parent1->random_seed)%100 > 50)
		child->random_seed = parent1->random_seed + 1;
	else
		child->random_seed = parent2->random_seed + 1;

	/* At every install step */
	for (install_step = 0; install_step < child->steps; install_step++) {

		/* for each program (gene) in the system */
		for (p = 0; p < population->sys.no_of_programs; p++) {

			/* choose a parent */
			parent = parent1;
			if (rand_num(&child->random_seed)%100 > 50)
				parent = parent2;

			/* get a program (gene) from this parent */
			child->change[install_step].version_index[p] =
				parent->change[install_step].version_index[p];
			child->change[install_step].installed[p] =
				parent->change[install_step].installed[p];
		}
	}

	return genome_mutate(population, child);
}

/**
 * @brief Ahistorically create a new individual.
 *        This creates a completely random upgrade sequence.
 *        There's no attempt to ratchet through versions/commits and the
 *        scoring function should take care of long redundant sequences.
 * @param population The population in which the genome exists
 * @param individual The genome to be mutated
 * @returns zero on success
 */
int genome_create(sc_population * population, sc_genome * individual)
{
	int upgrade_step, prog_index;

	/* clear all values */
	memset((void*)individual,'\0',sizeof(sc_genome));

	/* Assign a random seed for this individual.
	   Each genome has its own random seed so that evaluations could
	   take place in parallel without compromising determinism */
	individual->random_seed = rand_num(&population->random_seed);

	/* Number of steps in the upgrade.
	   Zero means we just go straight to the goal */
	individual->steps = rand_num(&individual->random_seed) % SC_MAX_CHANGE_SEQUENCE;

	/* check that there are some programs in the system */
	if (population->sys.no_of_programs <= 0) {
		printf("\nNo programs\n");
		return 1;
	}

	/* for every step in the upgrade sequence */
	for (upgrade_step = 0;
		 upgrade_step < individual->steps;
		 upgrade_step++) {

		/* for each possible program within the system */
		for (prog_index = 0;
			 prog_index < population->sys.no_of_programs;
			 prog_index++) {

			/* check that there are some versions/commits for htis program */
			if (population->sys.program[prog_index].no_of_versions <= 0)
				return 2;

			/* assign a random version/commit for this program */
			population->sys.program[prog_index].version_index =
				rand_num(&individual->random_seed) %
				population->sys.program[prog_index].no_of_versions;

			/* assign a random install state for this program, 0 or 1 */
			population->sys.program[prog_index].installed =
				rand_num(&individual->random_seed) % 2;
		}
	}

	return 0;
}
