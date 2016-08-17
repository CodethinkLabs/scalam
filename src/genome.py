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
    MAX_CHANGE_SEQUENCE=32
    DEFAULT_MUTATION_RATE=0.2
    DEFAULT_CROSSOVER=0.5
    DEFAULT_REBELS=0.05


    def __init__(self, systemStart, systemGoal, seed=None):

        # If no seed given, generate a new random seed
        if seed is None:
            self.seed=random.randint(1,9999999)
        else:
            if not isinstance(seed,int):
                raise TypeError(u"Genome 'seed' expects an int")
            self.seed=seed

        if not isinstance(systemStart,System):
                raise TypeError(u"Genome 'systemStart' expects a System instance")

        if not isinstance(systemGoal,System):
                raise TypeError(u"Genome 'systemGoal' expects a System instance")

        self.rand=RandNum(seed=self.seed)

        # the state of the system at start
        self.systemStart=systemStart

        # the state of the reference system
        self.systemGoal=systemGoal

        #TODO add option to pass argument in constructor?
        self.mutation_rate=Genome.DEFAULT_MUTATION_RATE
        self.crossover=Genome.DEFAULT_CROSSOVER
        self.rebels=Genome.DEFAULT_REBELS

        self.spawning_probability=0.0
        self.steps=self.rand.next() % Genome.MAX_CHANGE_SEQUENCE
        self.score=0

        # This contains a list of system objects which describe the upgrade sequence
        self.upgradeStep = []

    @staticmethod
    def createRandom(systemStart, systemGoal, seed=None):
        '''
        Ahistorically create a new individual. This creates a completely
        random upgrade sequence. There's no attempt to ratchet through
        versions/commits and the scoring function should take care of long
        redundant sequences.

        @param systemStart (System) The starting state of the syetem.
                                    All programs and their versions and
                                    installation status
        @param systemGoal (System)  The reference state for the syetem.
                                    All programs and their versions and
                                    installation status
        @param seed (int) Random seed to use
        @returns Genome
        '''

        genome=Genome(systemStart, systemGoal, seed=seed)
        # create a number of system objects representing the state of
        # the system at each upgrade step
        genome.upgradeStep = []
        for step in range(genome.steps):
            create.createInstallationStep()
        return genome

    def getScore(self):
        '''
        Gets the genome score
        '''

        #TODO do evaluation here or somewhere else?
        return self.score


    def createInstallationStep(self):
        '''
        * @brief Creates a single upgrade step consisting of a set of programs,
        *        their versions/commits and whether they are installed or not
        * @returns zero on success
        '''

        systemState = self.systemGoal.clone()
        self.upgradeStep.append(SystemState)

        # use the systemStart and systemGoal to set programs and versions
        # at each upgrade step randomly
        # Assumption: The list of programs are always in the same sequence
        #             in the starting and goal states
        for programIndex in range(0, len(SystemState.getPrograms())):
            # Distance between the current version and the goal
            distanceToGoal = \
                             self.systemGoal.programs[programIndex].versionIndex - \
                             self.systemStart.programs[programIndex].versionIndex

            # A random version/commit index between the start and the goal
            SystemState.programs[programIndex].versionIndex = \
                                                              self.systemStart.programs[programIndex].versionIndex + \
                                                              (self.rand.next() % distanceToGoal)

            # Random install state
            SystemState.programs[programIndex].installed = (self.rand.next() % 100 > 50)
        return 0

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

    def mutateInsertion(self):
        '''
        genome_mutate_insertion_deletion()
        * @brief Mutates a given genome by inserting or removing an upgrade step
        * @param population The population in which the genome exists
        * @param individual The genome to be mutated
        * @returns zero on success
        '''
        skip
    def mutateDeletion(self):
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
