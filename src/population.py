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
from system import System
from genome import Genome
from logger import logger

class Population:
    '''maximum number of genomes to have in a population'''
    MAX_POPULATION_SIZE=256

    def __init__(self, size, sys, goal, seed=None, prevgen=None):
        '''
        @param size (int) Number of individuals in the population. It's
            expected that this will remain constant.
        @param sys (System) Defines all of the programs within the system and
            their possible versions/commits.
        @param goal (System) The given goal system
        '''

        ##Type checking params
        if not isinstance(size, int):
            raise TypeError("Population size expects an int");
        if size > Population.MAX_POPULATION_SIZE:
            raise TypeError("Population size larger than MAX_POPULATION_SIZE (%d)"
                            %Population.MAX_POPULATION_SIZE)

        if not isinstance(sys, System):
            raise TypeError("Population sys expects a System instance");

        if not isinstance(goal, System):
            raise TypeError("Population goal expects a System instance");

        # If no seed given, generate a new random seed
        if seed is None:
            self.seed=random.randint(1,9999999)
        else:
            if not isinstance(seed,int):
                raise TypeError(u"Population 'seed' expects an int")
            self.seed=seed

        self.size=size
        self.sys=sys
        self.goal=goal

        if prevgen is not None:
            if not isinstance(prevgen, Population):
                raise TypeError("Population prevgen expects a Population instance");
            self.nextGeneration(prevgen)
        else:
            self.individuals=self._createInitGenomes(self.seed)

    def _createInitGenomes(self, seed):
        '''
        Creates the initial set of Genomes in the population

        @return Genome[]
        '''

        genomes=[]
        for i in range(self.size):
            genomes.append(Genome.createRandom(self.sys, self.goal ,seed))
        #TODO anything else?
        return genomes

    def getGenomes(self):
        '''
        Getter for the genomes in this population

        @return Genome[]
        '''

        return self.individuals

    def isGoalMet(self):
        '''
        Checks to see if any of the genomes meet the goal system
        '''

        # TODO should we return a boolean or a genome (list?) that
        # meet the goal criteria

        for genome in self.getGenomes():
            logger.debug("Current score is {} needs {}?".format(genome.getScore(),self.goal.getMaxScore()))
            if genome.getScore() == self.goal.getMaxScore():
                return True

        return False

    def selectParent(self, prevgen):
        '''
        Randomly selects a parent genome from the previous generation.
        This is biased towards the beginning of the list, and assumes that
        the previous generation have been sorted into descending score order

        @return Genome The parent genome
        '''
        rand=RandNum(self.seed)
        posn=(rand.next() % 100000) / 100000
        return prevgen.individual[int(posn * posn * len(prevgen.getGenomes()))]

    def nextGeneration(self, prevgen):
        '''
        Creates the next generation population

        @return Population
        '''

        prevgen.sort()

        self.individuals=[]
        for gen in range(len(prevgen.getGenomes())):
            individuals.add(child=Genome(self.sys, self.goal, self.selectParent(prevgen), self.selectParent(prevgen)))

    ####

    def createDirectAscentGenome(self):
        '''
        * @brief Assigns one genome in the population to try going straight
        *        to the goal, with no intermediate upgrade steps
        * @param population The population object
        * @returns The array index of the genome which was selected
        int population_create_direct_ascent_genome()
        '''
        pass

    def isGenomeUnique(self):
        '''
        * @brief Returns true if the given genome is unique.
        *        This is used during creation of the next generation to ensure that the
        *        same upgrade hypothesis doesn't get evaluated more than once
        * @param population The population object
        * @param genome The genome to be tested
        * @param genome_index Index for the current number of next generation genomes
        *                     which have been created thus far
        * @param next_generation Use the next generation (1) or the current generation (0)
        * @returns True if the given genome is unique
        int genome_unique()

        TODO Shouldn't this be in Genome? Check
        '''
        pass

    def reproductionFunction(self):
        '''
        * @brief Given a normalised evaluation score for a genome return the probability
        *        of reproduction. That is, the likelihood of being selected as a
        *        parent for the next generation
        * @param normalised_score Evaluation score in the range 0.0 -> 1.0
        * @returns Spawning probability.
        float population_reproduction_function()

        TODO rename this method?
        '''
        pass
    def genomeSpawningProbabilities(self):
        '''
        * @brief Calculate the reproduction probability for each genome
        * @param population The population to be updated
        * @returns zero on success
        int population_spawning_probabilities()
        '''
        pass

    def sort(self):
        '''
        * @brief sorts the current generation in order of their spawning probability
        * @param population The population to be updated after evaluation of genomes
        * @returns zero on success
        int population_sort()
        '''
        # Maybe there is some python way to sort a list based on the getScore function
        for i in range(len(self.getGenomes())):
            for j in range(len(self.getGenomes())-i):
                if self.individual[i].getScore() < self.individual[i+j].getScore():
                    tempgen=self.individual[i]
                    self.individual[i] = self.individual[i+j]
                    self.individual[i+j] = tempgen

    def setTestPasses(self):
        '''
        * @brief Sets the evaluation score for a genome with the given array index
        * @param population The population after individuals have been evaluated
        * @param index Array index of the genome for an individual
        * @param test_passes The number of test passes from evaluation
        * @returns zero on success
        */
        int population_set_test_passes()

        TODO is this needed in python?
        '''
        pass

    def getScore(self):
        '''
        * @brief Returns the evaluation score for a genome with the given array index
        * @param population The population after individuals have been evaluated
        * @param index Array index of the genome for an individual
        * @returns Evaluation score (fitness)
        */
        float population_get_score()
        '''
        pass

    def getAvgScore(self):
        '''
        * @brief Returns the average fitness score for the population
        * @param population The population after individuals have been evaluated
        * @returns Average score
        */
        float population_average_score()

        TODO Needed? Expect to just go something like self.score.mean()
        '''
        pass

    def getBestIndex(self):
        '''
        * @brief Returns the array index of the top scoring genome
        * @param population The population after individuals have been evaluated
        * @returns Array index of the highest scoring genome, or -1 on failure
        int population_best_index()
        '''
        pass
    def getWorstIndex(self):
        '''
        * @brief Returns the array index of the lowest scoring genome
        * @param population The population after individuals have been evaluated
        * @returns Array index of the lowest scoring genome, or -1 on failure
        int population_worst_index()
        '''
        pass

    def getMaxScore(self):
        '''
        * @brief Returns the best score for the given population
        * @param population The population after individuals have been evaluated
        * @returns The best score within the population
        float population_best_score()

        TODO See getAvgScore
        '''
        pass

    def getVariance(self):
        '''
        * @brief Returns the RMS variance of scores within the population
        * @param population The population after individuals have been evaluated
        * @returns RMS score variance
        float population_variance()
        '''
        pass

    def __clone__(self):
        '''
        * @brief Copies a population object
        *        Note that the destination populaion should *not* have
        *        been previously created
        * @param destination Population object to copy to
        * @param source Population object to copy from
        * @returns zero on success
        int population_copy()

        TODO Check that this is the correct syntax for cloning/copying
        '''
        pass
