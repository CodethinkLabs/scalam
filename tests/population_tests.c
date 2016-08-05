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


/**
 * @brief Creates a simple population to use in other test functions
 * @param population Population object
 * @returns zero on success
 */
int test_population_dummy(sc_population *population)
{
    /* Init the system */
    sc_system sys;
    test_system_dummy(&sys);

    /* Create a goal */
    sc_goal goal;
    goal_create_latest_versions(&sys, &goal);

    /* Population with dummy system and goal */
    population_create(10, population, &sys, &goal);

    return 0;
}


int test_create_system(sc_system * system_definition, char * repo_dir)
{
    int retval, p;
    char * repo_url1 = "https://github.com/CodethinkLabs/frepo";
    char * checkout1 = "618e913171d2cf8e731bc0c4ab4516f395dddba0";
    char * repo_url2 = "https://github.com/CodethinkLabs/firehose";
    char * checkout2 = "c2bf2f9961bea6c382fe17bbf1057a58ce6a3d2b";
    char commandstr[SC_MAX_STRING];

    /* clone repos into a test directory */
    sprintf(commandstr,"git clone %s %s/frepo 2> /dev/null",repo_url1, repo_dir);
    run_shell_command(commandstr);
    /* do a checkout so that we're not at the HEAD of master */
    sprintf(commandstr,"cd %s/frepo\ngit checkout %s -b %s 2> /dev/null",
            repo_dir,checkout1,checkout1);
    run_shell_command(commandstr);

    sprintf(commandstr,"git clone %s %s/firehose 2> /dev/null",repo_url2, repo_dir);
    run_shell_command(commandstr);
    /* do a checkout so that we're not at the HEAD of master */
    sprintf(commandstr,"cd %s/firehose\ngit checkout %s -b %s 2> /dev/null",
            repo_dir,checkout2,checkout2);
    run_shell_command(commandstr);

    return system_create_from_repos(system_definition, repo_dir);
}

void test_population_create()
{
    sc_population population;
    sc_system system_definition;
    sc_goal goal;
    char commandstr[SC_MAX_STRING];
    char * repo_dir;
    char template[] = "/tmp/scalam.XXXXXX";
    int i, is_unique, ctr, retval, population_size = 100;

    printf("test_population_create...");

    /* create a test directory which will contain repos */
    repo_dir = mkdtemp(template);

    /* make a test system with some repositories */
    assert(test_create_system(&system_definition, repo_dir) == 0);

    /* make a goal to get to the latest commits */
    assert(goal_create_latest_versions(&system_definition, &goal) == 0);

    /* generate the population */
    retval = population_create(population_size, &population, &system_definition, &goal);
    if (retval != 0) {
        printf("\nDidn't create population: error %d\n", retval);
    }
    assert(retval == 0);

    /* check that the size is as expected */
    if (population.size != population_size) {
        population_free(&population);
        assert(0);
    }

    /* only one genome goes straight to the goal */
    ctr = 0;
    for (i = 0; i < population.size; i++) {
        if (population.individual[i]->steps == 0)
            ctr++;
    }
    if (ctr != 1)
        population_free(&population);
    assert(ctr == 1);

    /* all genomes are unique */
    for (i = 0; i < population.size-1; i++) {
        is_unique =
            genome_unique(&population, population.individual[i], i, 0);
        if (!is_unique) {
            population_free(&population);
            assert(0);
        }
    }

    /* deallocate population */
    population_free(&population);

    sprintf(commandstr,"rm -rf %s", repo_dir);
    run_shell_command(commandstr);

    printf("Ok\n");
}

void test_population_copy()
{
    int i;
    sc_goal goal;
    char commandstr[SC_MAX_STRING];
    char * repo_dir;
    sc_system system_definition;
    sc_population source, destination;
    char template[] = "/tmp/scalam.XXXXXX";
    int population_size = 100;

    printf("test_population_copy...");

    /* create a test directory which will contain repos */
    repo_dir = mkdtemp(template);

    /* make a test system with some repositories */
    assert(test_create_system(&system_definition, repo_dir) == 0);

    /* make a goal to get to the latest commits */
    assert(goal_create_latest_versions(&system_definition, &goal) == 0);

    /* generate the population */
    assert(population_create(population_size, &source, &system_definition, &goal) == 0);

    /* check that the size is as expected */
    if (source.size != population_size) {
        population_free(&source);
        assert(0);
    }

    /* copy to the destination */
    assert(population_copy(&destination, &source) == 0);

    /* check that they are the same size */
    if (destination.size != source.size) {
        population_free(&source);
        population_free(&destination);
        assert(0);
    }

    /* check same mutation rate */
    if ((int)(destination.mutation_rate*1000) != (int)(source.mutation_rate*1000)) {
        population_free(&source);
        population_free(&destination);
        assert(0);
    }

    /* check same crossover */
    if ((int)(destination.crossover*1000) != (int)(source.crossover*1000)) {
        population_free(&source);
        population_free(&destination);
        assert(0);
    }

    /* check same rebels */
    if ((int)(destination.rebels*1000) != (int)(source.rebels*1000)) {
        population_free(&source);
        population_free(&destination);
        assert(0);
    }

    /* check same system */
    if (system_cmp((void*)&source.sys,
                   (void*)&destination.sys) != 0) {
        population_free(&source);
        population_free(&destination);
        assert(0);
    }

    /* check same goal */
    if (memcmp((void*)&source.goal,
               (void*)&destination.goal,
               sizeof(sc_goal)) != 0) {
        population_free(&source);
        population_free(&destination);
        assert(0);
    }

    /* check same random seed */
    if (destination.random_seed != source.random_seed) {
        population_free(&source);
        population_free(&destination);
        assert(0);
    }

    /* check that the genomes are the same */
    for (i = 0; i < source.size; i++) {
        if (memcmp(source.individual[i],
                   destination.individual[i],
                   sizeof(sc_genome)) != 0) {
            population_free(&source);
            population_free(&destination);
            assert(0);
        }
    }

    /* deallocate populations */
    population_free(&source);
    population_free(&destination);

    sprintf(commandstr,"rm -rf %s", repo_dir);
    run_shell_command(commandstr);

    printf("Ok\n");
}

void test_population_next_generation()
{
    printf("test_population_next_generation...");

    sc_system system_definition;
    sc_goal goal;
    sc_population before, after;
    char * repo_dir;
    char template[] = "/tmp/scalam.XXXXXX";
    char template_file[] = "/tmp/scalamfile.XXXXXX";
    char commandstr[SC_MAX_STRING];
    unsigned int random_seed = 63252;
    int i, ctr, is_unique, population_size = 100;
    int gen, fd;
    char log_file[SC_MAX_STRING], str[SC_MAX_STRING];

    /* create a test directory which will contain repos */
    repo_dir = mkdtemp(template);

    /* make a test system with some repositories */
    assert(test_create_system(&system_definition, repo_dir) == 0);

    /* make a goal to get to the latest commits */
    assert(goal_create_latest_versions(&system_definition, &goal) == 0);

    /* create a starting population */
    assert(population_create(population_size, &before,
                             &system_definition, &goal) == 0);

    /* keep a copy of the before population, so that it can be compared later */
    assert(population_copy(&after, &before) == 0);

    /* create a temporary file to store average scores within */
    strcpy(log_file, template_file);
    fd = mkstemp(log_file);
    printf("\nFilename is: %s\n", log_file);

    /* assign some initial scores */
    for (i = 0; i < population_size; i++) {
        assert(population_set_test_passes(&after, i,
                                          rand_num(&random_seed) % 100) == 0);
    }

    /* itterate through a few generations */
    for (gen = 0; gen < 256; gen++) {
        printf(".");

        /* create a new generation */
        assert(population_next_generation(&after) == 0);

        /* Assign some dummy scores to simulate what we have after evaluation.
           This is completely contrived and so perhaps should be replaced with
           something better */
        for (i = 0; i < population_size; i++) {
            assert(population_set_test_passes(&after, i,
                                              rand_num(&random_seed) % 100) == 0);
        }

        /* only one genome goes straight to the goal */
        ctr = 0;
        for (i = 0; i < after.size; i++) {
            if (after.individual[i]->steps == 0)
                ctr++;
        }
        if (ctr != 1) {
            printf("\nctr = %d\n", ctr);
            for (i = 0; i < after.size; i++) {
                if (after.individual[i]->steps == 0)
                    printf("%d ", i);
            }
            printf("\n");
            population_free(&before);
            population_free(&after);
        }
        assert(ctr == 1);

        /* all genomes are unique */
        for (i = 0; i < after.size-1; i++) {
            is_unique = genome_unique(&after, after.individual[i], i, 0);
            if (!is_unique) {
                population_free(&before);
                population_free(&after);
                assert(0);
            }
        }

        /* log to csv file */
        sprintf(str, "%f,", population_average_score(&after));
        write(fd, str, strlen(str));
    }
    close(fd);

    /* TODO plot the csv file */



    /* remove the log file */
    sprintf(commandstr,"rm -f %s", log_file);
    run_shell_command(commandstr);

    /* remove the test system */
    sprintf(commandstr,"rm -rf %s", repo_dir);
    run_shell_command(commandstr);

    /* free memory allocated */
    population_free(&before);
    population_free(&after);

    printf("Ok\n");
}

void run_population_tests()
{
    test_population_create();
    test_population_copy();
    test_population_next_generation();
}
