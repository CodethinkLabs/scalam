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
        
        ##Type checking params
        if not isinstance(system, System):
            raise TypeError(u"Goal 'system' expects a System instance")
    
        self.system=system
    
    @staticmethod
    def latestVersion(system):
        '''
        * @brief Creates a goal to try to get to the latest versions
        * @param sys System object
        * @param goal Returned goal object
        * @returns zero on success
        int goal_create_latest_versions()
        '''
 
        ##Type checking params
        if not isinstance(system, System):
            raise TypeError(u"Goal 'system' expects a System instance")       

        #Create an empty system and popululate one by one with highest version
        #of each software
        goal_system=System()  
        for prog in system.getPrograms():
            latest_version=prog.getCurrentHead()
            
            
            prog.checkout(latest_version)
           
                
        goal=Goal(goal_system)
        
        return goal
    
    def getMax(self):
        '''
        * @brief Calculates what the ideal end goal score is
        * @param goal Goal object
        * @returns score or negative on error
        float goal_max_score()
        '''
        pass