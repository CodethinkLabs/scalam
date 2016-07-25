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

#ifndef SCALAM_H
#define SCALAM_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define APPNAME "scalam"
#define VERSION "0.1"

/* The maximum number of programs in a system */
#define SC_MAX_SYSTEM_SIZE           99999

/* maximum length of strings used for program names */
#define SC_MAX_STRING                  256

#define SC_MAX_POPULATION_SIZE         512

/* The maximum number of state changes to get from the
   starting system to the reference system.
   This is assumed to be fairly small. */
#define SC_MAX_CHANGE_SEQUENCE          32

/* Defines a program and its possible versions */
typedef struct {
	char name[SC_MAX_STRING];

	char repo_url[SC_MAX_STRING];

	/* File containing list of versions
	   For example, coule be the result of:
		   git log --all --oneline > versions.txt
	   or could be created from a debian changelog */
	char versions_file[SC_MAX_STRING];

	/* The number of possible versions.
	   For exported git commit this would just be the line count */
	int no_of_versions;

	/* Index within the list of the current version
	   which this program is on */
	int version_index;

	/* Is the program installed or not */
	unsigned char installed;
} sc_program;

/* A collection of programs defines the state of a system */
typedef struct {
	int no_of_programs;
	sc_program program[SC_MAX_SYSTEM_SIZE];
} sc_system;

/* A minimal description of a change to a system.
   Some version indexes could be the same as the previous
   step in the upgrade sequence
   Indexes could also go either forwards or backwards. */
typedef struct {
	int version_index[SC_MAX_SYSTEM_SIZE];
	int installed[SC_MAX_SYSTEM_SIZE];
} sc_system_state;

/* A genome defines a sequence of changes to get to the reference state.
   After evaluation a score is assigned to it */
typedef struct {
	/* the number of steps in the sequence */
	int steps;

	/* The list of program versions at each step */
	sc_system_state change[SC_MAX_CHANGE_SEQUENCE];

	/* score for this sequence after evaluation */
	int score;
} sc_genome;

/* Defines the goal of the upgrade */
typedef struct {
	/* What programs and versions do we have at the start */
	sc_system_state start;

	/* What programs and versions do we want to end up with */
	sc_system_state reference;
} sc_goal;

/* Population of genomes */
typedef struct {
	/* Number of individuals in the population */
	int size;

	sc_genome individual[SC_MAX_POPULATION_SIZE];

	/* in the range 0.0 -> 1.0 */
    float mutation_rate;

	/* Percentage of the population to crossover in the range 0.0 -> 1.0 */
	float crossover;

	/* Percentage of rebel genomes in the range 0.0 -> 1.0 */
	float rebels;

	/* Definition of the system */
	sc_system sys;

	/* The goal transition */
	sc_goal goal;
} sc_population;

void show_help();
void run_tests();
int run_shell_command(char * commandstr);
int run_shell_command_with_output(char * commandstr, char * output);
int file_exists(char * filename);
int lines_in_file(char * filename);
int program_name_is_valid(sc_program * prog);
int program_version_from_index(sc_program * prog, int version_index, char * version);

/* functions to get versions of commits for a program */
int program_get_versions_from_repo(char * repos_dir, char * repo_url, sc_program * prog);
int program_get_versions_from_changelog(char * changelog_filename, sc_program * prog);
int program_get_versions_from_tarball(char * repos_dir, char * tarball_url, sc_program * prog);
int program_get_versions_from_deb_package(char * repos_dir, char * deb_url, sc_program * prog);
int program_get_versions_from_rpm_package(char * repos_dir, char * deb_url, sc_program * prog);
int program_get_versions_from_aptitude(char * repos_dir, sc_program * prog);

int genome_mutate(sc_population * population, sc_genome * individual);
int genome_spawn(sc_population * population,
				 sc_genome * parent1, sc_genome * parent2,
				 sc_genome * child);
int genome_create(sc_population * population, sc_genome * individual);

int population_create(sc_population * population, sc_goal goal);
int population_next_generation(sc_population * population);

#endif
