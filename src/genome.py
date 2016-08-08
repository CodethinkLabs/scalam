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

class Genome:
    def __init__(self):
        '''
        * @brief Ahistorically create a new individual.
        *        This creates a completely random upgrade sequence.
        *        There's no attempt to ratchet through versions/commits and the
        *        scoring function should take care of long redundant sequences.
        * @param population The population in which the genome exists
        * @param individual The genome to be mutated
        * @returns zero on success
        genome_create()
        '''
        skip
        
    def createInstallationStep(self):
        '''
        genome_create_installation_step()
        * @brief Creates a single upgrade step consisting of a set of programs,
        *        their versions/commits and whether they are installed or not
        * @param population The population in which the genome exists
        * @param individual The genome to be mutated
        * @param upgrade_step The index within the upgrade series
        * @returns zero on success
       '''
        skip
        
    def getMutability(self):
        '''
        genome_mutability()
        * @brief returns mutation rate expressed as an integer value
        * @param population The population in which the genome exists
        * @returns mutation rate value in the range 0 -> SC_MUTATION_SCALAR
        '''
        skip
        
    def mutate(self):
        '''
        genome_mutate_existing_programs()
        * @brief Mutates existing programs within a genome
        * @param population The population in which the genome exists
        * @param individual The genome to be mutated
        * @returns zero on success
        genome_mutate()
        * @brief Mutates a given genome
        * @param population The population in which the genome exists
        * @param individual The genome to be mutated
        * @returns zero on success
        '''
        skip
        
    def insert(self):
        '''
        genome_mutate_insertion_deletion()
        * @brief Mutates a given genome by inserting or removing an upgrade step
        * @param population The population in which the genome exists
        * @param individual The genome to be mutated
        * @returns zero on success
        '''
        skip
    def remove(self):
        '''
        genome_mutate_insertion_deletion()
        * @brief Mutates a given genome by inserting or removing an upgrade step
        * @param population The population in which the genome exists
        * @param individual The genome to be mutated
        * @returns zero on success
        '''
        skip
        
    def spawn(self):
        '''
        * @brief create a child from two parents
        * @param population The population in which the individuals exist
        * @param parent1 First parent
        * @param parent2 Second parent
        * @param child Returned child genome
        * @returns zero on success
        int genome_spawn()
        '''
        pass
    
    