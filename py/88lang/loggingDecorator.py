'''
I don't feel comfortable with the magic here. I criticized my son for 不求甚解,照猫画虎.
However, Now I feel No need to ask about underlying / internals. This domain is really GTD, not QQ. Unlike c++/java, Few python interviewer will treat it as QQ
'''
def log3(funcOrMsg=None, named_arg=None):
    '''arg is Optional. You can use any of:
    @log3(named_arg='specific msg') # some prefer named argument for clarity
    @log3('msg2') or
    @log3
    '''
    arg1_isCallable = callable(funcOrMsg)
    arg1_isStr      = isinstance(funcOrMsg, basestring)
    arg1_isNone     = funcOrMsg is None
 
    def decorated(func): #returns a decorated func
 
        @functools.wraps(func)
        def wrapper(*args, **kwargs):
            if named_arg: print 'named_arg = ' + str(named_arg)
            tmp = funcOrMsg if arg1_isStr else ''
            logger.info(tmp + ' pym ver = ' + str(logger.pymodelsVer),
              extra={'name_override' : func.__name__})
              ### set name_override to func.__name__ in a kwarg to info()
            return func(*args, **kwargs)
        ## end of wrapper() func definition
        
        return wrapper # decorated() unconditionally returns this callable functor
    ## end of decorated() func definition
    
    if arg1_isCallable:
        return decorated(funcOrMsg) # decorator received no-arg
    else:
        # decorator had kwargs   or   positional arg
        assert     arg1_isNone   or   arg1_isStr
        return decorated
