'''
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
'''

class System:
    def __init__(self):
        '''
        * @brief Creates a system definition from a set of git repos within
        *        a given directory
        * @param sys System definition
        * @param repos_dir The directory where the repos exist
        * @returns zero on success
        */
        int system_create_from_repos
        
        * @brief Extracts programs and their dependencies from baserock strata files
        * @brief definitions_dir The directory where baserock definitions exist
        * @param sys System object
        * @returns zero on success
        */
        int system_from_baserock()
        '''
        pass
    
    def addProgram(self):
        '''
        * @brief Adds a program to a system from a directory containing repos
        * @param sys System object
        * @param repos_dir The directory which contains the repos
        * @param subdirectory The subdirectory of repos_dir currently being scanned
        * @param ctr Character position during scan of the returned directories
        * @returns zero on success
        */
        int system_add_program_from_repo_directory(
        '''
        pass
    
    def dependencyMatrix(self):
        '''
        * @brief Create a dependency matrix for a system
        * @param sys System definition
        * @returns zero on success
        */
        int system_create_dependency_matrix(
        '''
        pass
    
    def build(self):
        '''
        * @brief Tries to build each component of the system in a container.
        *        Scores for each program/genome are set based on build success
        *        and number of automated tests passed
        * @param population Population definition
        * @param pop_ix The index of the population
        * @returns float total score of this system
        */
        float system_build(
        '''
        pass
    
    def getBaserockString(self):
        '''
        * @brief Extracts a string from a line of a baserock morph file
        * @param sys System object to be updated
        * @param linestr The line of text currently being read within the morph file
        * @param definition_line_prefix What we're looking for at the beginning of the line
        * @param foundstr Returned found string
        * @returns zero on success
        */
        int system_from_baserock_get_string
        
        TODO ?
        '''
        pass
    
    def getBaserockUpdateDepenedencies(self):
        '''
        * @brief Updates the dependency matrix for a system from baserock definitions
        * @brief definitions_dir The directory where baserock definitions exist
        * @param sys System object
        * @returns zero on success
        */
        int system_from_baserock_update_dependencies()
        
        TODO Have a feeling this shouldn't be here. New class/use existing baserock code?
        '''
        
    
    
    def getIndexFromName(self):
        '''
        * @brief Given the name of a program return its array index within a system
        * @param sys System object
        * @param name The program name to search for
        * @returns Array index of the program, or -1 if not found
        */
        int system_program_index_from_name()
        '''
        pass
    
    
    
    def __clone__(self):
        '''
        * @brief Copies from one system object to another
        * @param destination Location to copy to
        * @param source Location to copy from
        * @returns zero on success
        */
        int system_copy(
        '''
        pass
    
    def __cmp__(self, sys):
        '''
        * @brief Compares two systems
        * @param sys1 The first system object
        * @param sys2 The second system object
        * @returns zero is the systems are the same
        */
        int system_cmp
        '''
        pass