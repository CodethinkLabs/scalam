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

import os
from utils import unify
from repo_type import *



class Program:
    def __init__(self, repo, name="", installed=False):
        '''
        @param repo (AbsRepoType) Instance of
        @param name (String) Name of the program
        @param installed (bool) If the program is installed or not
        '''

        ##Type checking params
        if not isinstance(repo, AbsRepoType):
            raise TypeError(u"Program 'repo' expects a repo type e.g. GitType")

        # TODO name could be obmitted and recovered from directory/repo?
        if not isinstance(name,str):
            raise TypeError(u"Program 'name' expects a string")

        if not isinstance(installed,bool):
            raise TypeError(u"Program 'installed' expects a bool")

        self.repo_ref=repo
        self.name=unify(name)
        self.installed=installed
        
        # Version is mutable
        #TODO how to seed version? HEAD?
        self.version=repo.getHead()   

    def checkout(self,commit):
        '''
        checks out to the given commit
        '''

        self.version=commit
        return self.repo_ref.checkout(commit)
        
    def getVersion(self):
        '''
        Fetches the current version the program is at/checked out
        '''
        
        return self.version
    
    
    def getCurrentHead(self):
        '''
        Returns the latest version or commit for the software
        '''

        return self.repo_ref.getHead()

    def getName(self):
        '''
        Gets the name of the repo/program
        '''

        return self.name

    def getVersions(self):
        '''
        Gets a list of versions/commits for this piece of software
        '''
        
        return self.repo_ref.getVersions()

    @staticmethod
    def isValidName(name):
        '''
        Checks whether the name of the given program is valid
        @return bool
        '''

        if not isinstance(name,str):
            raise TypeError(u"Program.isValidName 'name' expects a string")

        if len(name) == 0:
            return False

        # TODO do we only care if the first char is a letter?
        if not name[0].isalpha():
            return False

        return True
    
    def __str__(self):
        return unicode(self)
    def __unicode__(self):
        return "%s"%(self.getName(),)
