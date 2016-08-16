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
from system import System

class Genome:
    '''
    A genome is a current instance of some software system and consists
    of many programs that can evolve (change version numbers)
    '''
    
    MAX_CHANGE_SEQUENCE=32
    DEFAULT_MUTATION_RATE=0.2
    DEFAULT_CROSSOVER=0.5
    DEFAULT_REBELS=0.05
    
    
    def __init__(self, system, seed=None):

        # If no seed given, generate a new random seed
        if seed is None:
            self.seed=random.randint(1,9999999)
        else:
            if not isinstance(seed,int):
                raise TypeError(u"Genome 'seed' expects an int")
            self.seed=seed
        
        if not isinstance(system,System):
                raise TypeError(u"Genome 'system' expects a System instance")    
        
        self.rand=RandNum(seed=self.seed)
        
        
        self.system=system
        
        #TODO add option to pass argument in constructor?
        self.mutation_rate=Genome.DEFAULT_MUTATION_RATE
        self.crossover=Genome.DEFAULT_CROSSOVER
        self.rebels=Genome.DEFAULT_REBELS
        
        self.spawning_probability=0.0
        self.steps= 1 + (self.rand.next() % (Genome.MAX_CHANGE_SEQUENCE-1))
        self.score=0
        

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
        genome=Genome(system, seed=seed)
        return genome
    
    def getScore(self):
        '''
        Gets the genome score
        '''
        
        #TODO do evaluation here or somewhere else?
        return self.score
    
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
        
        # Do a random pr check to see if this genome will mutate
        if self.rand.nextNormalised() > 0.5:
            
            # Figure out how many of the programs inside the genome will change
            genome_count=int(self.getMutability()*self.system.count())
            
            logger.debug("Mutating {} programs in {}".format(genome_count, self))
            
            i=0
            while i < genome_count:
                #Figure out which random program to mutate
                prog=self.system.getRandomProgram(self.rand.next())
                
                # Select mutatation strategy
                
                #TODO get distance to the goal. select a random number of
                # versions to change (pareto distribution?)
                #
                # For now, just do a single step
                
                steps=1
                logger.debug("Attempting to mutate {} {} times".format(prog, steps))
                
                if prog.canUpgrade(steps):  #This could fail if steps >1 and ver = last-1
                    prog.upgrade(steps)
                    i+=1
                else:
                    logger.debug("Failed to upgrade {}".format(steps))
            #end while
        #end if
        
        return    
    
    def crossover(self, otherParent):
        '''
        Create a new genome that shares random programs from each parent
        
        @param otherParent Genome 
        @return Genome New child genome
        '''
        
        #TODO 
        skip
    
    ####   

    


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


    def __eq__(self, genome):
        #TODO Criteria for comparing genomes for the unique property
        return False