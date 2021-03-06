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
from logger import logger

class Genome:
    '''
    A genome is a current instance of some software system and consists
    of many programs that can evolve (change version numbers)
    '''

    MAX_CHANGE_SEQUENCE=32
    DEFAULT_MUTATION_RATE=1.0#0.2
    DEFAULT_CROSSOVER=0.5
    DEFAULT_REBELS=0.05


    def __init__(self, systemStart, systemGoal, seed=None, steps=None, parent1=None, parent2=None):

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

        # current system that evolves over time
        self.currentSystem=systemStart.clone()

        #TODO add option to pass argument in constructor?
        self.mutation_rate=Genome.DEFAULT_MUTATION_RATE
        self.crossover=Genome.DEFAULT_CROSSOVER
        self.rebels=Genome.DEFAULT_REBELS

        self.spawning_probability=0.0
        if steps is not None:
            self.steps=steps
        else:
            self.steps=self.rand.next() % Genome.MAX_CHANGE_SEQUENCE
        self.score=0

        # This contains a list of system objects which describe the upgrade sequence
        self.upgradeStep = []

        # if parents have been specified then this is their child
        if parent1 is not None:
            if parent2 is not None:
                self.crossover(self, parent1, parent2)
                self.mutate()

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
            genome.createInstallationStep()
        return genome

    def getScore(self):
        '''
        Gets the genome score
        '''

        #TODO do evaluation here or somewhere else?
        return self.currentSystem.getScore()

    def createInstallationStep(self):
        '''
        * @brief Creates a single upgrade step consisting of a set of programs,
        *        their versions/commits and whether they are installed or not
        * @returns zero on success
        '''
        systemState = self.systemGoal.clone()
        self.upgradeStep.append(systemState)

        # use the systemStart and systemGoal to set programs and versions
        # at each upgrade step randomly
        # Assumption: The list of programs are always in the same sequence
        #             in the starting and goal states
        for programIndex in range(0, len(systemState.getPrograms())):
            # Distance between the current version and the goal
            distanceToGoal = \
                             self.systemGoal.programs[programIndex].versionIndex - \
                             self.systemStart.programs[programIndex].versionIndex

            # A random version/commit index between the start and the goal
            systemState.programs[programIndex].versionIndex = \
                                                              self.systemStart.programs[programIndex].versionIndex + \
                                                              (self.rand.next() % distanceToGoal)

            # Random install state
            systemState.programs[programIndex].installed = (self.rand.next() % 100 > 50)
        return 0

    def getMutability(self):
        '''
        Getter for mutation rate

        @returns float
        '''

        return self.mutation_rate

    def mutate(self):
        '''
        Randomly attempts to mutate a genome. Returns true on sucessful mutation
        '''

        # Do a random pr check to see if this genome will mutate
        if self.rand.nextNormalised() > 0.5:

            # Figure out how many of the programs inside the genome will change
            genome_count=int(self.getMutability()*self.currentSystem.count())

            logger.debug("Mutating {} programs in {}".format(genome_count, self))

            i=0
            while i < genome_count:
                #Figure out which random program to mutate

                prog=self.currentSystem.getRandomProgram(self.rand.next())

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

            return True
        #end if

        return False

    def crossover(self, parent1, parent2):
        '''
        Create a new genome that shares random programs from each parent

        @param parent1 Genome
        @param parent2 Genome
        @return Genome New child genome
        '''

        rand=RandNum(self.seed)

        # pick the number of steps from either parent
        self.steps = parent1.steps
        if rand.next() % 100 > 50:
            self.steps = parent2.steps

        for s in range(self,steps):
            # choose to take this step from one parent or the other
            if rand.next() % 100 < 50 and s < parent1.steps:
                systemState = parent1.upgradeStep[s].clone()
            else:
                systemState = parent2.upgradeStep[s].clone()
            self.upgradeStep.append(systemState)

    ####

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


    def __eq__(self, genome):
        #TODO Criteria for comparing genomes for the unique property
        return False
