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
 * @brief Gets a list of commits as a file called versions.txt
 * @param repos_dir Directory where the git repo will be checked out
 * @param repo_url URL of the git repo
 * @param program_name Name of the program
 * @returns zero on success
 */
int program_get_versions_git(char * repos_dir, char * repo_url, char * program_name)
{
	char commandstr[SC_MAX_STRING];

	sprintf(commandstr, "cd %s && git clone %s \"%s\"", repos_dir, repo_url, program_name);
	if (run_shell_command(commandstr) != 0) return 5;
	sprintf(commandstr, "cd \"%s/%s\" && git log --all --oneline > versions.txt",
			repos_dir, program_name);
	if (run_shell_command(commandstr) != 0) return 6;
	return 0;
}

/**
 * @brief Gets a list of versions from a changelog within a tarball
 * @param repos_dir Directory where the git repo will be checked out
 * @param tarball_url URL of the tarball
 * @param program_name Name of the program
 * @returns zero on success
 */
int program_get_versions_tarball(char * repos_dir, char * tarball_url, char * program_name)
{
	/* TODO */
	return 0;
}

/**
 * @brief Gets a list of versions as a file valled versions.txt
 * @param repos_dir Directory where the git repo will be checked out
 * @param repo_url URL of the git repo or tarball
 * @param program_name Name of the program
 * @returns zero on success
 */
int program_get_versions(char * repos_dir, char * repo_url, char * program_name)
{
	/* check for empty strings */
	if (strlen(repos_dir) == 0) return 1;
	if (strlen(repo_url) == 0) return 2;
	if (strlen(program_name) == 0) return 3;

	/* remove trailing slash if needed */
	if (strlen(repos_dir) > 1)
		if (repos_dir[strlen(repos_dir)-1]=='/')
			repos_dir[strlen(repos_dir)-1] = 0;

	/* handle git repos */
	if (strstr(repo_url, "git") != NULL) {
		return program_get_versions_git(repos_dir, repo_url, program_name);
	}

	/* handle tarballs */
	if (strstr(repo_url, "tar.gz") != NULL) {
		return program_get_versions_tarball(repos_dir, repo_url, program_name);
	}
	return 4;
}
