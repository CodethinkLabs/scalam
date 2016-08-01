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
 * @brief returns mutation rate expressed as an integer value
 * @param population The population in which the genome exists
 * @returns mutation rate value in the range 0 -> 1000
 */
int genome_mutability(sc_population * population)
{
	return (int)(population->mutation_rate * 1000);
}

/**
 * @brief Mutates existing programs within a genome
 * @param population The population in which the genome exists
 * @param individual The genome to be mutated
 * @returns zero on success
 */
int genome_mutate_existing_programs(sc_population * population, sc_genome * individual)
{
	/* mutate a program in an existing install step */
	int install_step, gene_index, no_of_programs, vindex;

	if (individual->steps <= 0)
		return 0;

	no_of_programs = population->sys.no_of_programs;
	install_step = rand_num(&individual->random_seed) % individual->steps;
	gene_index =
		rand_num(&individual->random_seed) % no_of_programs;

	if (population->sys.program[gene_index].no_of_versions <= 0)
		return 1;

	if (rand_num(&individual->random_seed) % 2 == 0) {

		/* commit of version index within versions_file */
		vindex = individual->change[install_step].version_index[gene_index];

		/* incremental: tweak the version/commit up or down */
		if (rand_num(&individual->random_seed) % 2 == 0) {
			/* don't exceed the number of versions in versions_file */
			if (vindex <
				population->sys.program[gene_index].no_of_versions - 1) {
				individual->change[install_step].version_index[gene_index]++;
			}
		}
		else {
			/* don't index below zero */
			if (vindex > 0)
				individual->change[install_step].version_index[gene_index]--;
		}
	}
	else {
		/* absolute: any version/commit may be selected */
		individual->change[install_step].version_index[gene_index] =
			rand_num(&individual->random_seed) %
			population->sys.program[gene_index].no_of_versions;
	}
}

/**
 * @brief Mutates a given genome by inserting or removing an upgrade step
 * @param population The population in which the genome exists
 * @param individual The genome to be mutated
 * @returns zero on success
 */
int genome_mutate_insertion_deletion(sc_population * population, sc_genome * individual)
{
	int upgrade_step, removal_index;
	int mutation_type = rand_num(&individual->random_seed) % 2;
	if (mutation_type == 1) {
		/* add an upgrade step */
		if (individual->steps < population->sys.no_of_programs-1) {
			individual->steps++;
		}
	}
	else {
		if (individual->steps > 0) {
			/* remove an upgrade step at a random point in the sequence */
			removal_index = rand_num(&individual->random_seed) % individual->steps;

			/* shuffle the subsequent steps down to fill the gap */
			for (upgrade_step = removal_index; upgrade_step < individual->steps; upgrade_step++) {
				memcpy((void*)&individual->change[upgrade_step],
					   (void*)&individual->change[upgrade_step+1],
					   sizeof(sc_system_state));
			}

			/* decrement the number of install steps */
			individual->steps--;
		}
	}
	return 0;
}

/**
 * @brief Mutates a given genome
 * @param population The population in which the genome exists
 * @param individual The genome to be mutated
 * @returns zero on success
 */
int genome_mutate(sc_population * population, sc_genome * individual)
{
	int mutability = genome_mutability(population);

	if (rand_num(&individual->random_seed) % 1000 < mutability)
		if (genome_mutate_existing_programs(population, individual) != 0)
			return 1;

	if (rand_num(&individual->random_seed) % 1000 < mutability)
		if (genome_mutate_insertion_deletion(population, individual) != 0)
			return 2;

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

	/* clear scores */
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

			/* does this install step exceed the number
			   for the parent? */
			if (install_step >= parent->steps)
				if (parent == parent1)
					parent = parent2;
				else
					parent = parent1;

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
