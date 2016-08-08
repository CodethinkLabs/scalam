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

class Population:
    def __init__(self):
        '''
        * @brief For a given goal create a population of possible upgrade paths
        * @param size Number of individuals in the population.
        *             It's expected that this will remain constant
        * @param population The population to be created
        * @param system_definition Defines all of the programs within the system
        *                          and their possible versions/commits
        * @param goal The given goal
        * @returns zero on success
        int population_create()
        '''
        pass
    
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
        pass
    
    def populationParrent(self):
        '''
        * @brief Randomly picks a parent genome with a bias towards
        *        higher scores
        * @param population The population to be updated after evaluation of genomes
        * @returns Pointer to the parent genome
        sc_genome * population_parent()
        
        TODO Rename/move this method, not clear on purpose at a glance
        '''
        pass
        
    def nextGeneration(self):
        '''
        * @brief Creates the next generation
        * @param population The population to be updated after evaluation of genomes
        * @returns zero on success
        int population_next_generation()
        '''
        pass
    
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