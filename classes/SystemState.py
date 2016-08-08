class SystemState:
    def __init__(self):
        """
        Version index for each possible program corresponds to a
        version number or commit within versions_file
        """
        self.version = []

        """
        Whether each possible program is installed or not.
        Some upgrade sequences might require uninstalls and
        reinstalls at a later step in the sequence
        """
        self.installed = []
