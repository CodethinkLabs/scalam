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
from logger import logger


class Program:
    def __init__(self, repo, name="", installed=False):
        '''
        Program constructor

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
        self.versions_list=[]
        self.versionIndex=-1

    def checkout(self,commit):
        '''
        Checks out to the given commit

        @param commit (String) Commit string you wish to checkout
        @return git.Checkout?
        '''

        if not isinstance(commit,str):
            raise TypeError(u"Program 'commit' expects a string")

        self.versionIndex=self.versionIndexFromString(commit)
        #FIXME do we need to return the git object here?
        #FIXME what if program isn't a git repo?
        return self.repo_ref.checkout(commit)

    def versionIndexFromString(self,versionString):
        '''
        Returns the index of a given version number or commit

        @param String Version or commit as a string
        @returns integer Index of the version or commit, or -1 if not found
        '''

        if not isinstance(versionString,str):
            raise TypeError(u"Program 'commit' expects a string")

        versions_list = self.getVersions();
        if not versions_list:
            return -1
        if not versionString in versions_list:
            return -1
        return versions_list.index(versionString)

    def versionIndexFromCommit(self,commit):
        '''
        This is just to make calls to the method from elsewhere more readable

        @param String Commit as a string
        @returns integer Index of the commit or -1 if not found
        '''
        return self.versionIndexFromString(commit)

    def getVersion(self):
        '''
        Fetches the current version the program is at/checked out

        @return String Current version program instance is on
        '''

        versions_list = self.getVersions()
        return versions_list[self.versionIndex]

    def setVersion(self, commit):
        '''
        Setter for version or commit

        @param commit (String) Version or commit to set
        '''

        if not isinstance(commit,str):
            raise TypeError(u"Program 'commit' expects a string")

        newVersionIndex = self.versionIndexFromString(commit)
        if newVersionIndex == -1:
            return False
        self.versionIndex=newVersionIndex
        return True

    def getCurrentHead(self):
        '''
        Returns the latest version or commit for the software

        @return String version sha
        '''

        return self.repo_ref.getHead()

    def getName(self):
        '''
        Gets the name of the repo/program

        @return String Program name
        '''

        return self.name

    def getVersions(self):
        '''
        Gets a list of versions/commits for this piece of software

        @return List of strings containing versions/commits
                with index zero being the first version/commit
        '''

        # if the list has been created previously
        if self.versions_list:
            return self.versions_list

        # get the list of commits
        possible_versions_list = self.repo_ref.getVersions()
        if possible_versions_list:
            possible_versions_list.reverse()
            self.versions_list = possible_versions_list
        else:
            self.versions_list = []

        return self.versions_list

    def getCommits(self):
        '''
        Makes subsequent calls more readable

        @return List of strings containing commits
                with index zero being the first version/commit
        '''

        return self.getVersions()

    def getNoOfVersions(self):
        '''
        Returns the number of versions of commits in the series
        @returns Integer Number of versions or commits
        '''
        return len(self.getVersions())

    def getNoOfCommits(self):
        '''
        This is just to make calls from elsewhere more readable

        @returns Integer Number of versions or commits
        '''
        return self.getNoOfVersions()

    def getCurrentVersion(self):
        '''
        Gets the current version (text) the program is currenty set to
        
        @return String
        '''
        
        return self.versions_list[self.versionIndex]
        
    def getCurrentVersionIndex(self):
        '''
        Gets the current version index the program is currently set to
        
        @return int
        '''
        
        return self.versionIndex

    def getPath(self):
        '''
        Returns the path where the repo exists
        
        @return String
        '''
        return self.repo_ref.getPath(self)
    
    def canUpgrade(self, jumps=1):
        '''
        Checks to see if the program has a higher version to upgrade to.
        The number of upgrade jumps depends on the `jumps ` parameter
        
        @param jumps (int) Number of jumps to make
        @return bool If it is able to upgrade this many times or not
        '''
        
        return (self.versionIndex+jumps)<=self.getNoOfVersions()
        

    @staticmethod
    def isValidName(name):
        '''
        Checks whether the name of the given program is valid

        @param name String Name to check if valid
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

