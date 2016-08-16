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

import sys
import traceback

from system import System
from population import Population
from genome import Genome
from logger import logger
from goal import Goal


# Number of generations to go through
DEFAULT_GEN_SIZE=10

# Number of unique genome instances to have
DEFAULT_POP_SIZE=5

def print_usage():
    usage='''Usage {}: (-t | -r REPO_PATH [GENERATION_MAX])

  -t                  Run test suite
  -r                  Run simulation

Simulation options:
  REPO_PATH           Path to repo to use
  GENERATION_MAX      Max number of generations to run for'''.format(sys.argv[0])

    print(usage)


def parse_args():
    '''
    Parse the arguments. Not using the python argparse library? No,
    it does not seem to support simple inner groups in an intuative
    way, e.g. (-t | -r REPO_PATH [GENERATION_MAX]), gets turned into
    (-t -r REPO_PATH [GENERATION_MAX]), or complex hackary needs to
    done on subparsers.
    '''
    
    try:    
        #Run test suite
        if sys.argv[1]=="-t":
            sys.path.insert(0, "../tests/")
            from test import run_tests
            
            print("Running Tests")
            print("=============")
            run_tests()
            
        
        elif sys.argv[1]=="-r":            
            repo_path = sys.argv[2]
            try:
                gen_max = int(sys.argv[3])
            except:
                gen_max = DEFAULT_GEN_SIZE
                
            run_simulation(repo_path, gen_max)
            
    
    except IndexError:
        print_usage()
    except Exception as e:
        logger.error(traceback.format_exc())
        print(e)
    
def run_simulation(repo_path, gen_max):
    logger.info("Running simulation with: REPO_PATH={}, GENERATION_MAX={}"
                .format(repo_path, gen_max))
    
    # Init base system
    sys=System(repo_path=repo_path)
    
    # Init goal (latest version)
    goal=Goal.latestVersion(sys)
    goal.system.dump()
    
    # Init population
    pop=Population(DEFAULT_POP_SIZE, sys, goal)
    
    # Init dataframe for storing results
    ## TODO

    for i in range(gen_max):
        '''
        For each generation we need to go through all the genomes
        and evolve them (mutate/crossover/rebel) and test. The more
        successful a genome is (more programs installed/tests), the
        more likely it is to create offspring for the next generation
        '''
        
        print("Generation #{}".format(i))
        
        for genome in pop.getGenomes():
            # TODO some evaluation, score, record
            print("\t{}".format(genome))
            pass
        
        #Check if objective has been met yet
        if pop.isGoalMet():
            # TODO
            pass
        
        pop=pop.nextGeneration()
    
    #TODO do some final reporting

if __name__ == '__main__':
    parse_args()
