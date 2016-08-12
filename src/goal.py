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

from system import System

class Goal:
    def __init__(self, system):
        '''
        @param  system (System) The system to set as the goal
        '''
        
        ##Type checking params
        if not isinstance(system, System):
            raise TypeError(u"Goal 'system' expects a System instance")
    
        self.system=system
    
    @staticmethod
    def latestVersion(system):
        '''
        Creates a goal based on the latest versions of software in the System
        
        @param system (System) Set of programs to upgrade
        @returns Goal instance
        '''
 
        ##Type checking params
        if not isinstance(system, System):
            raise TypeError(u"Goal 'system' expects a System instance")       

        #Create an empty system and popululate one by one with highest version
        #of each software
        goal_system=System()  
        for prog in system.getPrograms():
            #Make a copy of the object and set version to the max
            max_version=prog.clone()
            latest_version=max_version.getCurrentHead()
            max_version.setVersion(latest_version)
            
            #Add this to our goal system
            goal_system.addProgram(max_version)
            
            
        return Goal(goal_system)
    
    def getMaxScore(self):
        '''
        Calculates what the ideal end goal score is
        
        @returns float
        '''
        return 1.0