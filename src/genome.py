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

import random
from randnum import *

class Genome:
    MAX_CHANGE_SEQUENCE=32
    DEFAULT_MUTATION_RATE=0.2
    DEFAULT_CROSSOVER=0.5
    DEFAULT_REBELS=0.05
    
    
    def __init__(self, system, seed=None):

        # If no seed given, generate a new random seed
        if seed is None:
            self.seed=randint(1,9999999)
        else:
            if not isinstance(seed,int):
                raise TypeError(u"Genome 'seed' expects an int")
            self.seed=seed
        
        if not isinstance(system,System):
                raise TypeError(u"Genome 'system' expects a System instance")    
        
        self.rand=RandNum(seed=self.seed)
        
        
        self.system=system
        
        #TODO add option to pass argument in constructor?
        self.mutation_rate=DEFAULT_MUTATION_RATE
        self.crossover=DEFAULT_CROSSOVER
        self.rebels=DEFAULT_REBELS
        
        self.spawning_probability=0.0
        self.steps= 1 + (self.rand.next() % (MAX_CHANGE_SEQUENCE-1))
        

    @staticmethod
    def createRandom(system, seed=None):
        '''
        Ahistorically create a new individual. This creates a completely
        random upgrade sequence. There's no attempt to ratchet through
        versions/commits and the scoring function should take care of long
        redundant sequences.
        
        @param system (System) System to base genome off of
        @param seed (int) Random seed to use
        @returns Genome
        '''

        #TODO
        genome=Genome(seed=seed)
        return genome

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
        Getter for mutation rate
        
        @returns float
        '''
        
        return self.mutation_rate

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

    def __eq__(self, genome):
        #TODO Criteria for comparing genomes for the unique property
        return False