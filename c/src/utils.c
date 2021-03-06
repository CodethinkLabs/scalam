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
        return 1;
    }
    return 0;
}

/**
 * @brief Returns non-zero value if the given directory exists
 * @param directory Name of the directory
 * @returns True if the directory exists
 */
int directory_exists(char * directory)
{
    struct stat sb;

    if (stat(directory, &sb) == 0 && S_ISDIR(sb.st_mode))
    {
        return 1;
    }
    return 0;
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
 * @brief Given a string corresponding to a line in a file
 *        return the line number for that string
 * @param filename The file to be searched
 * @param search_line The line string to search for
 * @returns The line number for the string,
 *          -1 if not found
 *          -2 if file does not exist
 */
int get_line_number_from_string_in_file(char * filename, char * search_line)
{
    int line_number = -1;
    int i, ctr, index = 0;
    FILE * fp;
    char linestr[SC_MAX_STRING];
    char first_entry[SC_MAX_STRING];

    fp = fopen(filename, "r");
    if (!fp) return -2;

    while (!feof(fp)) {
        if (fgets(linestr , SC_MAX_STRING-1 , fp) != NULL) {
            if (linestr == NULL) continue;
            ctr = 0;
            for (i = 0; i < strlen(linestr); i++) {
                if ((linestr[i] == ' ') || (linestr[i] == '\t') ||
                    (linestr[i] == '\n')) {
                    break;
                }
                else {
                    first_entry[ctr++] = linestr[i];
                }
            }
            first_entry[ctr] = 0;
            if (strstr(first_entry, search_line) != NULL) {
                line_number = index;
                break;
            }
            index++;
        }
    }
    fclose(fp);
    return line_number;
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
                    /* Here we're only looking for the first thing which appears
                       which is typically the commit or version number.
                       The rest is likely to be comments */
                    if ((linestr[i] == ' ') ||
                        (linestr[i] == '\t') ||
                        (linestr[i] == '\n'))
                        break;
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

    pclose(fp);

    return 0;
}

/**
 * @breif Checks to see if software is installed
 * @param softwarename Name of the cli software
 * @returns 1 on success
 */
int software_installed(char * softwarename)
{
    char commandstr[SC_MAX_STRING];

    /* Apparently system runs sh not bash so messes up some of the syntax */
    sprintf(commandstr, "[ $(which %s | wc -c) = 0 ]", softwarename);

    return system(commandstr);
}

/**
 * @brief Lehmer random number generator
 * @param seed Random number generator seed
 * @return Pseudo-random number
 */
int rand_num(unsigned int * seed)
{
    unsigned int v =
        ((unsigned long long)(*seed) * 279470273UL) % 4294967291UL;

    /* avoid the singularity */
    if (v==0) {
        v = *seed;
        while (((unsigned long long)v * 279470273UL) % 4294967291UL == 0) v++;
    }

    *seed = v;
    return abs((int)v);
}
