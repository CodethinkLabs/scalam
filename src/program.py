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

class Program:
    def __init__(self):
        pass
    
    def getCurrentCheckout(self):
        '''
        * @brief for a cloned program git repo return the current checkout point
        * @param repo_dir Directory containing the git repo
        * @param commit The returned commit, or an empty string
        * @returns zero on success
        */
        int program_repo_get_current_checkout()
        '''
        pass
    
    def getCurrentHead(self):
        '''
        * @brief for a cloned program git repo return the HEAD commit
        * @param repo_dir Directory containing the git repo
        * @param commit The returned HEAD commit, or an empty string
        * @returns zero on success
        */
        int program_repo_get_head()
        '''
        pass
    
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
        * @brief Sets the program name from the repo information
        * @param prog Program object
        * @param repos_dir Directory where the git repo will be checked out
        * @returns Zero on success
        */
        int program_name_from_repo()
        '''
        pass
    
    def getVersionFromIndex(self):
        '''
        * @brief Returns the commit or version number for the given index number.
        *        Within sc_program an index number indicates what version the program
        *        is currently on.
        * @paam prog Program object
        * @param version_index The desired version index. This could be the same as
        *                      prog->version_index, or might be different
        * @param version The returned commit or version number string
        * @returns zero on success
        */
        int program_version_from_index()
        '''
        pass
    
    def getVersionFromGit(self):
        '''
        * @brief Gets a list of commits from a git repo as a file called versions.txt
        * @param repos_dir Directory where the git repo will be checked out
        * @param repo_url URL of the git repo
        * @param prog Program object
        * @returns zero on success
        */
        int program_get_versions_from_git()
        '''
        pass
    
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
    
    def getCommits(self):
        '''
        * @brief Gets a list of commits from a repo directory
        * @param repo_dir Directory where the git repo exists
        * @param prog Program object
        * @returns zero on success
        */
        int program_repo_get_commits(
        '''
        pass