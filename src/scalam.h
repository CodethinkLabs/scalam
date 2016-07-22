#ifndef SCALAM_H
#define SCALAM_H

#define MAX_SYSTEM_SIZE           99999
#define MAX_STRING                  256
#define MAX_VERSION_STRING_LENGTH   512

/* Defines a program and its possible versions */
typedef struct {
	char name[MAX_STRING];

	char repo_url[MAX_STRING];

	/* File containing list of versions
	   For example, coule be the result of:
	       git log --all --oneline > versions.txt
	   or could be created from a debian changelog */
	char * versions_file;

	/* The number of possible versions.
	   For exported git commit this would just be the line count */
	int no_of_versions;

	/* index within the list of the current version
	   which this program is on */
	int version_index;

	/* is the program installed or not */
	unsigned char installed;
} sc_program;

/* A collection of programs defines the state of a system */
typedef struct {
	int no_of_programs;
	sc_program program[MAX_SYSTEM_SIZE];
} sc_system;

/* A minimal description of a change to a system.
   Some version indexes could be the same as the previous state.
   Indexes could also go either forwards or backwards. */
typedef struct {
	int version_index[MAX_SYSTEM_SIZE];
	int installed[MAX_SYSTEM_SIZE];
} sc_system_change;

#endif
