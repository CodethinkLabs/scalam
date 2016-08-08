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

class Goal:
    def __init__(self):
        pass
    
    @staticMethod
    def latestVersion():
        '''
        * @brief Creates a goal to try to get to the latest versions
        * @param sys System object
        * @param goal Returned goal object
        * @returns zero on success
        int goal_create_latest_versions()
        '''
        pass
    
    def getMax(self):
        '''
        * @brief Calculates what the ideal end goal score is
        * @param goal Goal object
        * @returns score or negative on error
        float goal_max_score()
        '''
        pass