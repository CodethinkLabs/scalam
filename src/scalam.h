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
#include <time.h>
#include <math.h>

#define APPNAME "scalam"
#define VERSION "0.1"

/* The maximum number of programs in a system */
#define SC_MAX_SYSTEM_SIZE            3000

/* maximum length of strings used for program names */
#define SC_MAX_STRING                  256

#define SC_MAX_POPULATION_SIZE         256

/* The maximum number of state changes to get from the
   starting system to the reference system.
   This is assumed to be fairly small. */
#define SC_MAX_CHANGE_SEQUENCE         32

/* default evolution parameters */
#define SC_DEFAULT_MUTATION_RATE       0.2
#define SC_DEFAULT_CROSSOVER           0.5
#define SC_DEFAULT_REBELS              0.05

/* when converting probabilities into integer values */
#define SC_MUTATION_SCALAR             1000

/* The maximum number of tries when creating new unique genomes */
#define SC_MAX_TRIES_FOR_UNIQUE_GENOME 1000

/* Defines a program and its possible versions */
typedef struct {
    char name[SC_MAX_STRING];

    char repo_url[SC_MAX_STRING];

    /* File containing list of versions
       For example, coule be the result of:
       git log --pretty=tformat:"%H" --all --first-parent master > versions.txt
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
    /* Version index for each possible program corresponds to a
       version number or commit within versions_file */
    int version_index[SC_MAX_SYSTEM_SIZE];

    /* Whether each possible program is installed or not.
       Some upgrade sequences might require uninstalls and
       reinstalls at a later step in the sequence */
    unsigned char installed[SC_MAX_SYSTEM_SIZE];
} sc_system_state;

/* A genome defines a sequence of changes to get to the reference state.
   After evaluation a score is assigned to it */
typedef struct {
    /* the number of steps in the sequence */
    int steps;

    /* The list of program versions at each step */
    sc_system_state change[SC_MAX_CHANGE_SEQUENCE];

    /* score for this sequence after evaluation */
    float score;

    /* the probability of reproduction when creating the next generation */
    float spawning_probability;

    /* seed for PRNG */
    unsigned int random_seed;
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

    sc_genome ** individual;
    sc_genome ** next_generation;

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

    /* seed for PRNG */
    unsigned int random_seed;
} sc_population;


/* The largest number of rows in our dataframe */
#define SC_MAX_DF_SIZE      10000

/* Partial set of rows in a dataframe, generated per step */
typedef struct {
    int cycle_no;
    float scores[SC_MAX_POPULATION_SIZE];
    int population_size;

} sc_dataframe_slice;

typedef struct {
    /* As score data is only known per iteration, generate a slice per iteration */
    int slice_no;
    sc_dataframe_slice slice[SC_MAX_CHANGE_SEQUENCE];

    /* List of params used for the simulation */

    /* Range  0.0 - 1.0 */
    int population_size;
    float mutation_rate;
    float crossover;
    float rebels;

    /* Seed used for simulation */
    unsigned int random_seed;


} sc_dataframe;



void show_help();
void run_tests();
int run_shell_command(char * commandstr);
int run_shell_command_with_output(char * commandstr, char * output);
int file_exists(char * filename);
int lines_in_file(char * filename);
int get_line_number_from_string_in_file(char * filename, char * line);
int program_name_is_valid(sc_program * prog);
int program_version_from_index(sc_program * prog, int version_index, char * version);
int software_installed(char * softwarename);
int rand_num(unsigned int * seed);

/* functions to get versions of commits for a program */
int program_get_versions_from_repo(char * repos_dir, char * repo_url, sc_program * prog);
int program_get_versions_from_changelog(char * changelog_filename, sc_program * prog);
int program_get_versions_from_tarball(char * repos_dir, char * tarball_url, sc_program * prog);
int program_get_versions_from_deb_package(char * repos_dir, char * deb_url, sc_program * prog);
int program_get_versions_from_rpm_package(char * repos_dir, char * deb_url, sc_program * prog);
int program_get_versions_from_aptitude(char * repos_dir, sc_program * prog);
int program_repo_get_commits(char * repo_dir, sc_program * prog);
int program_repo_get_current_checkout(char * repo_dir, char * commit);
int program_repo_get_head(char * repo_dir, char * commit);

int genome_mutate(sc_population * population, sc_genome * individual);
int genome_spawn(sc_population * population,
                 sc_genome * parent1, sc_genome * parent2,
                 sc_genome * child);
int genome_create(sc_population * population, sc_genome * individual);
int genome_unique(sc_population * population,
                  sc_genome * genome, int genome_index,
                  int next_generation);

int population_create(int size, sc_population * population,
                      sc_system * system_definition,
                      sc_goal * goal);
void population_free(sc_population * population);
int population_copy(sc_population * destination, sc_population * source);
int population_next_generation(sc_population * population);
float population_average_score(sc_population * population);
int population_set_test_passes(sc_population * population, int index, int test_passes);
float population_get_score(sc_population * population, int index);
int population_best_index(sc_population * population);
int population_worst_index(sc_population * population);
float population_best_score(sc_population * population);
float population_variance(sc_population * population);

void plot_create_df_slice(sc_dataframe * df, sc_population * population);
void plot_create_dataframe(sc_dataframe * df, sc_population * population);
void plot_dataframe_save(sc_dataframe * df);

void run_program_tests();
void run_genome_tests();
void run_population_tests();
void run_system_tests();

int system_create_from_repos(sc_system * sys, char * repos_dir);

int goal_create_latest_versions(sc_system * sys, sc_goal * goal);

#endif
