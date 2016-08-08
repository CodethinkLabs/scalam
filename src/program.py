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

from utils import unify

# https://github.com/gitpython-developers/GitPython
try:
    import git
except ImportError:
    assert("GitPython libary missing. For installation instructions "
           "see: https://github.com/gitpython-developers/GitPython")


class Program:
    def __init__(self, repo, name=None, installed=False):
        '''
        @param name (String) Name of the program
        @param installed (bool) If the program is installed or not
        '''
        
        ##Type checking params
        if not isinstance(repo, AbsRepoType):
            raise TypeError(u"Program 'repo' expects a repo type e.g. GitType")
        
        # TODO name could be obmitted and recovered from directory/repo?
        if not isinstance(name,(str,unicode)):
            raise TypeError(u"Program 'name' expects a string")

        if not isinstance(installed,bool):
            raise TypeError(u"Program 'installed' expects a bool")       

        self.repo_ref=repo
        self.name=unify(name)
        self.directory=directory
        self.installed=installed
    
    def getCurrentHead(self):
        '''
        Returns the latest version or commit for the software
        '''
        
        return self.repo_ref.getHead()
    
    @staticMethod
    def isValidName():
        '''
        * @brief Checks whether the name of the given program is valid
        * @param prog Program object
        * @returns Zero on success
        int program_name_is_valid()
        '''
        pass
    
    def getName(self):
        '''
        Gets the name of the repo/program
        '''
        
        return self.name
    
    
    
    
    ##
    # TODO - Includes renaming/re-factoring into current code
    ##
    
    def getVersionFromChangelog(self):
        '''
        * @brief Gets a list of versions from a changelog
        * @param changelog_filename Filename of the changelog
        * @param prog Program object
        * @returns zero on success
        */
        int program_get_versions_from_changelog()
        '''
        pass
    
    def getVersionFromTarball(self):
        '''
        * @brief Gets a list of versions from a changelog within a tarball
        * @param repos_dir Directory where the git repo will be checked out
        * @param tarball_url URL of the tarball
        * @param prog Program object
        * @returns zero on success
        */
        int program_get_versions_from_tarball()
        '''
        pass
    
    def getVersionFromDeb(self):
        '''
        * @brief Gets a list of versions from a debian package
        * @param repos_dir Directory where the git repo will be checked out
        * @param deb_url URL where the debian package can be downloaded from
        * @param prog Program object
        * @returns zero on success
        */
        int program_get_versions_from_deb_package()
        '''
        pass
    
    def getVersionFromRpm(self):
        '''
        * @brief Gets a list of versions from a RPM package
        * @param repos_dir Directory where the git repo will be checked out
        * @param rpm_url URL where the debian package can be downloaded from
        * @param prog Program object
        * @returns zero on success
        */
        int program_get_versions_from_rpm_package(
        '''
        pass
    
    def getVersionFromRepo(self):
        '''
        * @brief Gets a list of versions from a repo as a file valled versions.txt
        * @param repos_dir Directory where the git repo will be checked out
        * @param repo_url URL of the git repo or tarball
        * @param prog Program object
        * @returns zero on success
        */
        int program_get_versions_from_repo(
        '''
        pass
    
    def getVersionFromAptitude(self):
        '''
        * @brief Gets a list of versions provided by aptitude
        * @param prog Program object
        * @returns zero on success
        */
        int program_get_versions_from_aptitude()
        '''
        pass
    
    def getVersions(self):
        '''
        Gets a list of version/commits from a repo
        '''
        return self.git_ref.getVersions()
    

class AbsRepoType:
    def assertValidDirectory(self, directory):
        if not isinstance(directory,(str,unicode)):
            raise TypeError(u"%s 'directory' expects a string"%self.__class__.__name__)
        
        #TODO check if exists, fail or create? currently fails
        if not os.path.exists(directory):
            raise IOError(u"%s 'path' given does not exist"%self.__class__.__name__)
    
    @abstractmethod
    def getVersions(self):
        pass
    
    @abstractmethod
    def getHead(self):
        pass
    
    
class DirType(AbsRepoType):
    pass
class GitType(AbsRepoType):
    def __init__(self, url, clone_path):
        
        if not isinstance(url,(str,unicode)):
            raise TypeError(u"GitType 'url' expects a string")  
        
        assertValidDirectory(clone_path)
        
        self.url=url
        self.path=clone_path
        
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
        '''
        
        return self.git_ref.head.ref.commit.hexsha

class TarType(AbsRepoType):
    pass
class DebType(AbsRepoType):
    pass
class RpmType(AbsRepoType):
    pass