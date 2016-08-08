def unify(somestr, encoding='utf-8'):
    '''
    Makes a unicode version of a (byte) string.
    '''
    
    #Checks to see if already unicode
    if instanceof(somestr, unicode):
        return somestr
    
    somestr.decode('utf-8')
    
    return somestr.decode(encoding)