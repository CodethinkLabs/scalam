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

int lines_in_file(char * filename)
{
	FILE * fp;
	int ctr = 0;
	char linestr[SC_MAX_STRING];

	fp = fopen(filename, "r");
	if (!fp) return 0;

	while (!feof(fp)) {
		if (fgets(linestr , SC_MAX_STRING-1 , fp) != NULL) {
			if (linestr == NULL) continue;
			ctr++;
		}
	}
	fclose(fp);
	return ctr;
}

int get_line_from_file(char * filename, int line_number, char * line)
{
	FILE * fp;
	int ctr = 0, i;
	char linestr[SC_MAX_STRING];
	int total_lines, target_line;

	line[0] = 0;

	total_lines = lines_in_file(filename);

	fp = fopen(filename, "r");
	if (!fp) return 1;

	target_line = total_lines - line_number - 1;

	while (!feof(fp)) {
		if (fgets(linestr , SC_MAX_STRING-1 , fp) != NULL) {
			if (linestr == NULL) continue;
			if (ctr == target_line) {
				for (i = 0; i < strlen(linestr); i++) {
					if ((linestr[i] == ' ') || (linestr[i] == '\t')) break;
					line[i] = linestr[i];
				}
				line[i] = 0;
				break;
			}
			ctr++;
		}
	}
	fclose(fp);

	if (line[0] == 0) {
		return 2;
	}

	return 0;
}

int run_shell_command(char * commandstr)
{
	if (system(commandstr) != -1)
		return 0;
	else
		return 1;
}

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

int program_get_versions_tarball(char * repos_dir, char * repo_url, char * program_name)
{
	/* TODO */
	return 0;
}

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
