import os 
from CMGTools.Common.Tools.applyJSON_cff import *
from CMGTools.H2TauTau.tools.jsonPick import *

def setupJSON( process ):

    print 'setting up JSON:'

    fileName = process.source.fileNames[0]
    print fileName
    # in case filename is a local filename, removing CMGLOCALBASEDIR
    #Jose: dont know where this var is set
    #fileName = fileName.replace( os.environ['CMGLOCALBASEDIR'],'' ) 
    json = jsonPick( fileName, True )
    applyJSON(process, json )
    return json
