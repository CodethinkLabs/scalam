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

import logging

#Set up loggers
logger = logging.getLogger(__name__)

##Define logging to file behaviour
# All levels are logged to a single debug.log file
fh = logging.FileHandler('debug.log',mode='w')
formatter = logging.Formatter('[%(levelname)s] - %(message)s')
fh.setFormatter(formatter)
fh.setLevel(logging.DEBUG)
logger.addHandler(fh)

##Define logging out to stdout
ch = logging.StreamHandler()
ch.setLevel(logging.WARN)
formatter = logging.Formatter('[%(name)s] %(levelname)s - %(message)s')
ch.setFormatter(formatter)
logger.addHandler(ch)

#Set minimum level for the global setting.
logger.setLevel(logging.DEBUG)
logger.debug("Logger init")