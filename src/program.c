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
 * @brief Checks whether the name of the given program is valid
 * @param prog Program object
 * @returns Zero on success
 */
int program_name_is_valid(sc_program * prog)
{
	/* null string */
	if (prog->name[0] == 0)
		return 1;

	/* first character is not an ascii letter */
	if (!(((prog->name[0] >= 'a') && (prog->name[0] <= 'z')) ||
		  ((prog->name[0] >= 'A') && (prog->name[0] <= 'Z'))))
		return 2;

	return 0;
}

/**
 * @brief Returns the commit or version number for the given index number.
 *        Within sc_program an index number indicates what version the program
 *        is currently on.
 * @paam prog Program object
 * @param version_index The desired version index. This could be the same as
 *                      prog->version_index, or might be different
 * @param version The returned commit or version number string
 * @returns zero on success
 */
int program_version_from_index(sc_program * prog, int version_index, char * version)
{
	/* TODO */

	return 0;
}

/**
 * @brief Gets a list of commits from a git repo as a file called versions.txt
 * @param repos_dir Directory where the git repo will be checked out
 * @param repo_url URL of the git repo
 * @param prog Program object
 * @returns zero on success
 */
int program_get_versions_from_git(char * repos_dir, char * repo_url, sc_program * prog)
{
	char commandstr[SC_MAX_STRING];

	if (program_name_is_valid(prog) != 0) return 5;

	sprintf(commandstr, "cd %s && git clone %s \"%s\"", repos_dir, repo_url, prog->name);
	if (run_shell_command(commandstr) != 0) return 6;
	sprintf(prog->versions_file, "%s/%s/versions.txt", repos_dir, prog->name);
	sprintf(commandstr, "cd \"%s/%s\" && git log --all --oneline > %s",
			repos_dir, prog->name, prog->versions_file);
	if (run_shell_command(commandstr) != 0) return 7;
	if (!file_exists(prog->versions_file)) return 8;
	prog->no_of_versions = lines_in_file(prog->versions_file);
	return 0;
}

/**
 * @brief Gets a list of versions from a changelog
 * @param changelog_filename Filename of the changelog
 * @param prog Program object
 * @returns zero on success
 */
int program_get_versions_from_changelog(char * changelog_filename, sc_program * prog)
{
	if (program_name_is_valid(prog) != 0) return 5;

	/* do we know where to put the resulting versions list? */
	if (file_exists(prog->versions_file)) return 6;

	/* TODO */
	return 0;
}

/**
 * @brief Gets a list of versions from a changelog within a tarball
 * @param repos_dir Directory where the git repo will be checked out
 * @param tarball_url URL of the tarball
 * @param prog Program object
 * @returns zero on success
 */
int program_get_versions_from_tarball(char * repos_dir, char * tarball_url, sc_program * prog)
{
	if (program_name_is_valid(prog) != 0) return 5;

	/* do we know where to put the resulting versions list? */
	if (file_exists(prog->versions_file)) return 6;

	/* TODO
	   This should untar, find the changelog and then call program_get_versions_from_changelog */

	return 0;
}

/**
 * @brief Gets a list of versions from a debian package
 * @param repos_dir Directory where the git repo will be checked out
 * @param deb_url URL where the debian package can be downloaded from
 * @param prog Program object
 * @returns zero on success
 */
int program_get_versions_from_deb_package(char * repos_dir, char * deb_url, sc_program * prog)
{
	if (program_name_is_valid(prog) != 0) return 5;

	/* do we know where to put the resulting versions list? */
	if (file_exists(prog->versions_file)) return 6;

	/* TODO
	   This should wget the package, extract changelog from the DEBIAN directory then
	   call program_get_versions_from_changelog */

	return 0;
}

/**
 * @brief Gets a list of versions from a RPM package
 * @param repos_dir Directory where the git repo will be checked out
 * @param rpm_url URL where the debian package can be downloaded from
 * @param prog Program object
 * @returns zero on success
 */
int program_get_versions_from_rpm_package(char * repos_dir, char * rpm_url, sc_program * prog)
{
	if (program_name_is_valid(prog) != 0) return 5;

	/* do we know where to put the resulting versions list? */
	if (file_exists(prog->versions_file)) return 6;

	/* TODO
	   This should wget the package, extract changelog from the spec directory then
	   call program_get_versions_from_changelog */

	return 0;
}

/**
 * @brief Gets a list of versions from a repo as a file valled versions.txt
 * @param repos_dir Directory where the git repo will be checked out
 * @param repo_url URL of the git repo or tarball
 * @param prog Program object
 * @returns zero on success
 */
int program_get_versions_from_repo(char * repos_dir, char * repo_url, sc_program * prog)
{
	/* check for empty strings */
	if (strlen(repos_dir) == 0) return 1;
	if (strlen(repo_url) == 0) return 2;

	/* remove trailing slash if needed */
	if (strlen(repos_dir) > 1)
		if (repos_dir[strlen(repos_dir)-1]=='/')
			repos_dir[strlen(repos_dir)-1] = 0;

	/* handle git repos */
	if (strstr(repo_url, "git") != NULL) {
		return program_get_versions_from_git(repos_dir, repo_url, prog);
	}

	/* handle tarballs */
	if (strstr(repo_url, "tar.gz") != NULL) {
		return program_get_versions_from_tarball(repos_dir, repo_url, prog);
	}
	return 4;
}
