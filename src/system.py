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

class System:
    def __init__(self, repo_dir=None, definitions=None, programs=None):
        '''
        A system (collection of programs) can be created in at least 4 ways
        
        - (repo_dir) Local directory containing git checkouts of programs
        - (definitions) Baserock stratam file
        - (programs) List of Program instances
        - () There was another way honest
        '''
        
        # Check that more than one entry has been given
        if [repo_dir, definitions, programs].count(None) is not 2:
            raise TypeError(u"System expects ONLY a repo_dir, definitions or programs, parameter")
        
        # Scan directory for programs (git)
        if repo_dir is not None:
            #TODO
            self.programs=[]
        # Parse definitions
        elif definitions is not None:
            #TODO
            self.programs=[]
        # List of program instances given
        elif programs is not None:
            #TODO check that this is a list and all members are Programs
            self.programs=programs
    
    def addProgram(self, program):
        '''
        Adds a program to a system
        '''
        
        ##Type checking params
        if not isinstance(program, Program):
            raise TypeError(u"System.addProgram 'program' expects a Program instance")
        
        self.programs.append(program)
    
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
        '''
        
        #TODO shallow or deep copy? Does it matter?
        
        # Make a shallow copy
        return copy.copy(self)
    
    def __eq__(self, sys):
        # If sys isn't a System, then it is clearly not equal
        if not isinstance(sys, System):
            return False
        
        return self.programs == sys.programs