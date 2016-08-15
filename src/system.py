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

import copy
import os

from logger import logger
from utils import *
from program import *
from repo_type import *


try:
    import git
except ImportError:
    print("Error: GitPython libary missing. For installation instructions "
           "see: https://github.com/gitpython-developers/GitPython")
    sys.exit()

class System:
    def __init__(self, repo_path=None, definitions=None, programs=None):
        '''
        A system (collection of programs) can be created in at least 4 ways

        - (repo_path) Local directory containing git checkouts of programs
        - (definitions) Baserock stratam file
        - (programs) List of Program instances
        - Empty system - Programs to add later

        @param repo_path String Path to the directory that contains the system
        @param definitions String Path to definitions file that describes the system
        @param program Program[] List of programs in a system
        '''

        # Check that more than one entry hasn't been given
        if [repo_path, definitions, programs].count(None) < 2:
            logger.error(list2str([repo_path, definitions, programs]))
            raise TypeError(u"System expects ONLY a repo_path, definitions or programs, parameter")

        # Scan directory for programs (git)
        if repo_path is not None:
            logger.debug("Creating System from repo_path")
            self.programs=System.programsFromGitDirectory(repo_path)

        # Parse definitions
        elif definitions is not None:
            #TODO
            logger.debug("Creating System from baserock definitions")
            self.programs=[]

        # List of program instances given
        elif programs is not None:
            #TODO check that this is a list and all members are Programs
            logger.debug("Creating System from list")
            self.programs=programs

        # Empty system, expected to use addProgram() after creation
        else:
            logger.debug("Creating an empty System")
            self.programs=[]

        logger.debug("Program list for this system: %s"%(list2str(self.programs)))

    @staticmethod
    def programsFromGitDirectory(repo_path):
        '''
        Get a list of Programs from a base directory that contains Git repos

        @param repo_path String Path to the directory where git checkouts are
        @return Program[]
        '''

        program_list=[]

        #Scan all the directories for git repos
        logger.debug("Searching inside %s"%repo_path)
        for d in list_dirs(repo_path):

            program_name=d

            program_path=os.path.join(repo_path, d)
            logger.debug("-%s : %s"%(program_name,program_path))

            try:
                program=Program(repo=DirType(program_path), name=program_name)
                program_list.append(program)
            except git.InvalidGitRepositoryError:
                #Not a git repo so skip over it
                logger.debug("Not a valid git repo")
                continue

        return program_list

    def addProgram(self, program):
        '''
        Adds a program to a system

        @param program Program The proram you wish to add to the System
        '''

        ##Type checking params
        if not isinstance(program, Program):
            raise TypeError(u"System.addProgram 'program' expects a Program instance")

        logger.debug("Adding %s to the system list"%program)
        self.programs.append(program)

    def getPrograms(self):
        '''
        Getter for the list of programs

        @return Program[]
        '''

        return self.programs
    
    def count(self):
        '''
        Counts the number of programs in the system
        
        @return int
        '''
        
        return len(self.programs)
 
    def dependencyMatrix(self):
        '''
        Create a dependency matrix for a system

        TODO
        '''
        pass

    def build(self):
        '''
        Tries to build each component of the system. Scores for each program/genome
        are set based on build success and number of automated tests passed

        TODO
        '''

        for prog in self.programs:
            #TODO do something
            pass


    def clone(self):
        '''
        Makes a copy of the current System instance

        @return System
        '''

        #TODO shallow or deep copy? Does it matter?

        # Make a shallow copy
        return copy.copy(self)

    def __eq__(self, sys):
        # If sys isn't a System, then it is clearly not equal
        if not isinstance(sys, System):
            return False

        return self.programs == sys.programs
