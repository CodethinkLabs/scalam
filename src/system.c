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
 * @brief Adds a program to a system from a directory containing repos
 * @param sys System object
 * @param repos_dir The directory which contains the repos
 * @param subdirectory The subdirectory of repos_dir currently being scanned
 * @param ctr Character position during scan of the returned directories
 * @returns zero on success
 */
int system_add_program_from_repo_directory(sc_system * sys, char * repos_dir,
                                           char * subdirectory, int ctr)
{
    char full_directory[SC_MAX_STRING];
    char current_checkout[SC_MAX_STRING];
    int line_number;

    if (ctr == 0)
        return 0;

    /* string terminator */
    subdirectory[ctr] = 0;

    /* the full path for the program repo */
    sprintf(full_directory,"%s/%s",repos_dir,subdirectory);

    /* set the name of the program */
    sprintf((&sys->program[sys->no_of_programs])->name, "%s", subdirectory);

    /* update the details for this program */
    if (program_repo_get_commits(full_directory,
                                 &sys->program[sys->no_of_programs]) != 0)
        return 1;

    /* check that there are some commits */
    if (sys->program[sys->no_of_programs].no_of_versions <= 0)
        return 2;

    /* get the current checkout commit */
    if (program_repo_get_current_checkout(full_directory, current_checkout) != 0)
        return 3;

    /* Get the array index from the checkout */
    line_number =
        get_line_number_from_string_in_file((&sys->program[sys->no_of_programs])->versions_file,
                                            (char*)current_checkout);
    if (line_number < 0)
        return 4;

    /* Invert the line number so that the last line in versions_file
       corresponds to version index zero. This just makes incrementing
       through versions more intuitive. */
    sys->program[sys->no_of_programs].version_index =
        sys->program[sys->no_of_programs].no_of_versions -
        line_number;

    /* increment the number of programs in the system */
    sys->no_of_programs++;

    return 0;
}

/**
 * @brief Create a dependency matrix for a system
 * @param sys System definition
 * @returns zero on success
 */
int system_create_dependency_matrix(sc_system * sys)
{
    int i;

    sys->dependency_probability =
        (double**)malloc(sizeof(double*)*SC_MAX_SYSTEM_SIZE);
    if (sys->dependency_probability ==  NULL)
        return 1;

    for (i = 0; i < SC_MAX_SYSTEM_SIZE; i++) {
        sys->dependency_probability[i] =
            (double*)malloc(sizeof(double)*SC_MAX_SYSTEM_SIZE);
        if (sys->dependency_probability[i] == NULL)
            return 2;
    }

    return 0;
}

/**
 * @brief Creates a system definition from a set of git repos within
 *        a given directory
 * @param sys System definition
 * @param repos_dir The directory where the repos exist
 * @returns zero on success
 */
int system_create_from_repos(sc_system * sys, char * repos_dir)
{
    char commandstr[SC_MAX_STRING];
    char directories[SC_MAX_STRING];
    char subdirectory[SC_MAX_STRING];
    char current_commit[SC_MAX_STRING];
    char head_commit[SC_MAX_STRING];
    int i, ctr, retval;

    /* find the subdirectories. This returns a string with directories listed
       such as:

       dir1/
       dir2/
       dir3/
    */
    sprintf(commandstr, "cd %s\nls -F | grep /", repos_dir);
    if (run_shell_command_with_output(commandstr, directories) != 0)
        return 1;
    if (directories[0] == 0)
        return 2;

    subdirectory[0] = 0;
    ctr = 0;

    /* clear the system so that it's initial state is consistent */
    memset((void*)sys, '\0', sizeof(sc_system));

    system_create_dependency_matrix(sys);

    /* scan the directories string extracting individual subdirectories */
    for (i = 0; i < strlen(directories); i++) {
        /* look for carriage returns */
        if ((directories[i] != '\n') && (i < strlen(directories)-1)) {
            /* read the directory name */
            if (directories[i] != '/')
                subdirectory[ctr++] = directories[i];
        }
        else {
            retval = system_add_program_from_repo_directory(sys, repos_dir,
                                                            (char*)subdirectory, ctr);
            if (retval != 0) {
                printf("system_add_program_from_repo_directory err %d", retval);
                return 3;
            }

            /* reset the character counter */
            ctr = 0;
        }
    }

    /* Handle any stragglers if we didn't encounter a final carriage
       return or / character */
    if (system_add_program_from_repo_directory(sys, repos_dir,
                                               (char*)subdirectory, ctr) != 0)
        return 4;

    return 0;
}

/**
 * @brief Tries to build each component of the system in a container.
 *        Scores for each program/genome are set based on build success
 *        and number of automated tests passed
 * @param population Population definition
 * @param pop_ix The index of the population
 * @returns float total score of this system
 */
float system_build(sc_population *population, int pop_ix)
{
    sc_program * program;
    sc_system_state * state;
    float score_sum=0;
    /* TODO */


    state=population->individual[pop_ix]->change;

    /* Cycle through all programs in system */
    int i;
    for(i=0; i<population->sys.no_of_programs; i++)
    {
        program=&population->sys.program[i];

        /* If marked to install, attempt it */
        if(state->installed[i])
        {
            /*
             * TODO
             *
             * Do some install
             * state->version_index[j]
             */
        }

        /* Do some scoring based on build/tests */
        population->individual[i]->score=0.0;    /* TODO */


        score_sum+=population->individual[i]->score;
    }


    return score_sum;
}

/** @brief Copies from one system object to another
 * @param destination Location to copy to
 * @param source Location to copy from
 * @returns zero on success
 */
int system_copy(sc_system * destination, sc_system * source)
{
    int i;

    destination->no_of_programs = source->no_of_programs;

    memcpy((void*)&destination->program, (void*)&source->program,
           sizeof(sc_program)*SC_MAX_SYSTEM_SIZE);

    if (system_create_dependency_matrix(destination) != 0)
        return 1;

    for (i = 0; i < SC_MAX_SYSTEM_SIZE; i++)
        memcpy((void*)destination->dependency_probability[i],
               (void*)source->dependency_probability[i],
               sizeof(double)*SC_MAX_SYSTEM_SIZE);

    return 0;
}

/**
 * @brief Compares two systems
 * @param sys1 The first system object
 * @param sys2 The second system object
 * @returns zero is the systems are the same
 */
int system_cmp(sc_system * sys1, sc_system * sys2)
{
    int i;

    if (sys1->no_of_programs != sys2->no_of_programs)
        return 1;

    if (memcmp((void*)&sys1->program, (void*)&sys2->program,
               sizeof(sc_program)*SC_MAX_SYSTEM_SIZE) != 0)
        return 2;

    for (i = 0; i < SC_MAX_SYSTEM_SIZE; i++)
        if (memcmp((void*)sys1->dependency_probability[i],
                   (void*)sys2->dependency_probability[i],
                   sizeof(double)*SC_MAX_SYSTEM_SIZE) != 0)
            return 3;

    return 0;
}

/**
 * @brief Frees memory for a system
 * @param sys System object
 */
void system_free(sc_system * sys)
{
    int i;

    for (i = 0; i < SC_MAX_SYSTEM_SIZE; i++)
        free(sys->dependency_probability[i]);

    free(sys->dependency_probability);
}
