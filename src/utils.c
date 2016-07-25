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
 * @brief Returns non-zero value if the given file exists
 * @param filename Name of the file
 * @returns True if the file exists
 */
int file_exists(char * filename)
{
	FILE * fp;

	fp = fopen(filename, "r");
	if (fp) {
		fclose(fp);
		return (1 == 1);
	}
	return (1 == 0);
}

/**
 * @brief Returns the total number of lines in a file
 * @param filename Name of the file
 * @returns Number of lines in the file
 */
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

/**
 * @brief Returns a specific line from a file.
 *        Note that commit lists or changelogs are in descending order.
 * @param filename Name of the file
 * @param line_number The line number to get, beginning from the end of the file
 * @param line The returned line
 * @returns Zero on success
 */
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

/**
 * @brief Runs a shell command
 * @param commandstr The command to be run
 * @returns Zero on success
 */
int run_shell_command(char * commandstr)
{
	if (system(commandstr) != -1)
		return 0;
	else
		return 1;
}

/**
 * @brief Runs a command and returns its output as a string
 * @param commandstr The command to be run
 * @param output The returned output of the command
 * @param zero on success
 */
int run_shell_command_with_output(char * commandstr, char * output)
{
	FILE *fp;
	char str[2048];
	int i, ctr = 0;

	fp = popen(commandstr, "r");
	if (fp == NULL) {
		printf("Failed to run command\n" );
		return 1;
	}

	/* Read the output */
	output[0] = 0;
	while (fgets(str, sizeof(str)-1, fp) != NULL) {
		for (i = 0; i < strlen(str); i++) {
			output[ctr++] = str[i];
		}

		/* at the end of each line */
		output[ctr++] = '\n';
	}

	/* string terminator */
	if (ctr > 1) ctr -= 2;
	output[ctr] = 0;

	/* close */
	pclose(fp);
	return 0;
}
