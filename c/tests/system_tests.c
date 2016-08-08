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
 * @brief Creates a simple system to use in other test functions
 * @param sys System object
 * @returns zero on success
 */
void test_system_dummy(sc_system *sys)
{
    int retval, p;
    char * repo_url = "https://github.com/CodethinkLabs/frepo";
    char * checkout = "618e913171d2cf8e731bc0c4ab4516f395dddba0";
    char template[] = "/tmp/scalam.XXXXXX";
    char * repo_dir;
    char commandstr[SC_MAX_STRING];

    /* create a test directory which will contain repos */
    repo_dir = mkdtemp(template);

    /* clone repos into a test directory */
    sprintf(commandstr,"git clone %s %s/frepo 2> /dev/null",repo_url, repo_dir);
    run_shell_command(commandstr);
    /* do a checkout so that we're not at the HEAD of master */
    sprintf(commandstr,"cd %s/frepo\ngit checkout %s -b %s 2> /dev/null",
            repo_dir,checkout,checkout);
    run_shell_command(commandstr);

    retval = system_create_from_repos(sys, repo_dir);
    if (retval != 0) {
        printf("\nsystem_create_from_repos err %d\n", retval);
        sprintf(commandstr,"rm -rf %s", repo_dir);
        run_shell_command(commandstr);
    }
    assert(retval == 0);

    /* check that programs were actually created */
    for (p = 0; p < sys->no_of_programs; p++) {
        /* has a name */
        assert(sys->program[p].name[0] != 0);

        /* has some commits */
        assert(sys->program[p].no_of_versions > 0);

        /* has a versions.txt file */
        assert(sys->program[p].versions_file[0] != 0);

        /* non-zero current commit index */
        assert(sys->program[p].version_index > 0);

        /* check that we are not at HEAD of master */
        if (sys->program[p].version_index == sys->program[p].no_of_versions) {
            printf("\nversion_index is the same as the head of master\n");
            sprintf(commandstr,"rm -rf %s", repo_dir);
            run_shell_command(commandstr);
        }
        assert(sys->program[p].version_index < sys->program[p].no_of_versions);

        /* check that versions.txt file exists */
        assert(file_exists(sys->program[p].versions_file));
    }

    /*  remove the test directory.
        since this is only for testing we won't need
        to keep the files after struct creation (?).
    */
    sprintf(commandstr,"rm -rf %s", repo_dir);
    run_shell_command(commandstr);

}

void test_system_create_from_repos()
{
    sc_system sys;
    int retval, p;
    char * repo_url1 = "https://github.com/CodethinkLabs/frepo";
    char * checkout1 = "618e913171d2cf8e731bc0c4ab4516f395dddba0";
    char * repo_url2 = "https://github.com/CodethinkLabs/firehose";
    char * checkout2 = "c2bf2f9961bea6c382fe17bbf1057a58ce6a3d2b";
    char template[] = "/tmp/scalam.XXXXXX";
    char * repo_dir;
    char commandstr[SC_MAX_STRING];

    printf("test_system_create_from_repos...");

    /* create a test directory which will contain repos */
    repo_dir = mkdtemp(template);

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

    retval = system_create_from_repos(&sys, repo_dir);
    if (retval != 0) {
        printf("\nsystem_create_from_repos err %d\n", retval);
        sprintf(commandstr,"rm -rf %s", repo_dir);
        run_shell_command(commandstr);
    }
    assert(retval == 0);

    if (sys.no_of_programs != 2) {
        printf("sys.no_of_programs %d\n",sys.no_of_programs);
    }
    assert(sys.no_of_programs == 2);

    /* check that programs were actually created */
    for (p = 0; p < sys.no_of_programs; p++) {
        /* has a name */
        assert(sys.program[p].name[0] != 0);

        /* has some commits */
        assert(sys.program[p].no_of_versions > 0);

        /* has a versions.txt file */
        assert(sys.program[p].versions_file[0] != 0);

        /* non-zero current commit index */
        assert(sys.program[p].version_index > 0);

        /* check that we are not at HEAD of master */
        if (sys.program[p].version_index == sys.program[p].no_of_versions) {
            printf("\nversion_index is the same as the head of master\n");
            sprintf(commandstr,"rm -rf %s", repo_dir);
            run_shell_command(commandstr);
        }
        assert(sys.program[p].version_index < sys.program[p].no_of_versions);

        /* check that versions.txt file exists */
        assert(file_exists(sys.program[p].versions_file));
    }

    /* deallocate */
    system_free(&sys);

    /* remove the test directory */
    sprintf(commandstr,"rm -rf %s", repo_dir);
    run_shell_command(commandstr);

    printf("Ok\n");
}

void test_system_from_baserock()
{
    char * temp_dir;
    char definitions_dir[SC_MAX_STRING];
    char * definitions_url = "http://git.baserock.org/git/baserock/baserock/definitions.git";
    sc_system sys;
    char commandstr[SC_MAX_STRING];
    char template[] = "/tmp/scalam.XXXXXX";
    int retval = 0;

    printf("test_system_from_baserock...");

    /* temporary location for cloning definitions */
    temp_dir = mkdtemp(template);

    /* create the temporary directory */
    sprintf(commandstr,"mkdir -p %s", temp_dir);
    run_shell_command(commandstr);
    if (!directory_exists(temp_dir)) {
        printf("\nDirectory %s not found\n", temp_dir);
        assert(0);
    }

    /* path where definitions will exist */
    sprintf(definitions_dir,"%s/definitions", temp_dir);

    /* get the baserock definitions */
    sprintf(commandstr, "git clone %s %s --quiet",
            definitions_url, definitions_dir);
    run_shell_command(commandstr);

    if (!directory_exists(definitions_dir)) {
        printf("\nDirectory %s not found\n", definitions_dir);
        retval = 100;
    }
    else {
        retval = system_create_dependency_matrix(&sys);
        system_free(&sys);
    }

    /* remove the definitions directory */
    sprintf(commandstr,"rm -rf %s", definitions_dir);
    run_shell_command(commandstr);

    /* did the test work? */
    if (retval != 0)
        printf("\nretval = %d\n", retval);
    assert(retval == 0);

    printf("Ok\n");
}

void test_system_copy()
{
    printf("test_system_copy...");

    /* TODO */

    printf("Ok\n");
}

void test_system_cmp()
{
    printf("test_system_cmp...");

    /* TODO */

    printf("Ok\n");
}

void test_system_from_baserock_get_string()
{
    printf("test_system_from_baserock_get_string...");

    /* TODO */

    printf("Ok\n");
}

void test_system_program_index_from_name()
{
    printf("test_system_program_index_from_name...");

    /* TODO */

    printf("Ok\n");
}

void test_system_from_baserock_update_dependencies()
{
    printf("test_system_from_baserock_update_dependencies...");

    /* TODO */

    printf("Ok\n");
}

void test_system_program_install_sequence_probability()
{
    printf("test_system_program_install_sequence_probability...");

    /* TODO */

    printf("Ok\n");
}

void run_system_tests()
{
    test_system_copy();
    test_system_cmp();
    test_system_from_baserock_get_string();
    test_system_program_index_from_name();
    test_system_create_from_repos();
    test_system_from_baserock_update_dependencies();
    test_system_from_baserock();
    test_system_program_install_sequence_probability();
}
