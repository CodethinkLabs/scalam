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
import sys
from logger import logger

# https://github.com/gitpython-developers/GitPython
try:
    import git
except ImportError:
    print("Error: GitPython libary missing. For installation instructions "
           "see: https://github.com/gitpython-developers/GitPython")
    sys.exit()

class AbsRepoType:
    def assertValidDirectory(self, directory):
        if not isinstance(directory,str):
            raise TypeError(u"%s 'directory' expects a string"%self.__class__.__name__)

        #TODO check if exists, fail or create? currently fails
        if not os.path.exists(directory):
            raise IOError(u"%s 'path' given does not exist"%self.__class__.__name__)


    def getVersions(self):
        '''
        Get a list of software version or commits.
        Needs to be implemented by extending class.

        @return String[]
        '''
        raise NotImplementedError

    def getHead(self):
        '''
        Gets the latest version or commit for this software
        Needs to be implemented by extending class.

        @return String
        '''
        raise NotImplementedError

    def checkout(self,commit):
        '''
        checks out to the given commit

        @param commit String Commit or version to fetch
        '''

    def getPath(self):
        raise NotImplementedError

    def setPath(self, path):
        raise NotImplementedError

class GitType(AbsRepoType):
    def __init__(self, url, clone_path):
        '''
        @param url String URL of the git repo
        @param clone_path String Location of where to clone repo to
        '''

        if not isinstance(url,str):
            raise TypeError(u"GitType 'url' expects a string")

        self.assertValidDirectory(clone_path)

        logger.debug("GitType(%s,%s)"%(url,clone_path))
        self.url=url
        self.setPath(clone_path)

        #Do the git clone
        self.git_ref=git.Repo.clone_from(url=url, to_path=clone_path)

    def getVersions(self):
        '''
        Grab all of the version shas of this git repo

        @return List of versions
        '''

        versions=[]
        #Grab all of the shas from this repo
        for commits in self.git_ref.iter_commits():
            versions.append(commits.hexsha)

        return versions

    def getHead(self):
        '''
        Grabs the commit sha of HEAD

        @return String
        '''

        return self.git_ref.head.ref.commit.hexsha

    def checkout(self, commit):
        '''
        checks out to the given commit

        @param commit String
        '''

        past_branch = self.git_ref.create_head(commit, commit)
        self.git_ref.head.reference = past_branch
        assert not self.git_ref.head.is_detached
        # reset the index and working tree to match the pointed-to commit
        self.git_ref.head.reset(index=True, working_tree=True)

    def getPath(self):
        return self.path

    def setPath(self, path):
        self.path = path


class DirType(GitType):
    '''
    Sets up the git referencing given a local path with a repo checked out to it
    '''

    def __init__(self, path):
        '''
        @param path String Path to the directory
        '''

        #Make sure that the path is valid
        self.assertValidDirectory(path)

        #If path is not a valid git repo, this will throw an InvalidGitRepositoryError
        self.git_ref=git.Repo(path)
        self.path=path

class TarType(AbsRepoType):
    pass
class DebType(AbsRepoType):
    pass
class RpmType(AbsRepoType):
    pass
