class Program:
    def __init__(self, name, repoUrl=""):
        self.name = name

        """ Where is the repo? """
        self.repoUrl = repoUrl

        """
        List of versions/commits
        """
        self.versions = []

        """
        Index within the list of the current version
        which this program is on
        """
        self.versionIndex = 0

        """
        Is the program installed or not
        """
        self.installed = False

    def FromRepo(repoUrl):
        """
        Create from a repo
        """

        this.repoUrl = repoUrl

        """ TODO """

    def GetCurrent():
        """
        Get the current version or commit
        """

        if self.versionsIndex < 0:
            return ""

        if self.versionsIndex >= len(self.versions):
            return ""

        return self.versions[self.versionsIndex]

    def SetCurrent(index):
        """
        Get the current version or commit
        """

        if index >= len(self.versions):
            return False

        if index < 0:
            return False

        self.versionsIndex = index
        return True
