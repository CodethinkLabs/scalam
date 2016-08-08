class Program:
    ## Constructor
    # @param name Name of the program
    # @param repoUrl Optional repository URL
    def __init__(self, name, repoUrl=""):
        self.name = name

        ## Where is the repo?
        self.repoUrl = repoUrl

        ## List of versions/commits
        self.versions = []

        ## Index within the list of the current version
        ## which this program is on
        self.versionIndex = 0

        ## Is the program installed or not
        self.installed = False

    ## Create from a repo
    # @param repoURL Repository URL to create from
    def FromRepo(repoUrl):

        this.repoUrl = repoUrl

        ## TODO

    ## Get the current commit or version number as a string
    # @returns Current commit or version number
    def GetCurrent():
        if self.versionsIndex < 0:
            return ""

        if self.versionsIndex >= len(self.versions):
            return ""

        return self.versions[self.versionsIndex]

    ## Get the current version or commit
    # @param index index number within the versions list
    def SetCurrent(index):

        if index >= len(self.versions):
            return False

        if index < 0:
            return False

        self.versionsIndex = index
        return True
