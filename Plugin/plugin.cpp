#include "entryPoint.h"
#include "api.h"
#include "plugin.h"
#include "pl_exporter.h"
#include <stdlib.h>
#include <stdio.h>

// Pointers to the two interfaces
TPluginInterface* pluginInterface;
THostInterface* hostInterface;

// These are the methods in the interface that the plugin will expose to the 
//host application via TPluginInterface

int add (int a, int b) {
    return a + b;
}


int getVersion () {
    return 1234;
}

const char* getID() {
    return "id23";
}

const char* getDisplayName () {
    return "MakeCoffee";
}

const char* getAuthor () {
    return "John Smith";
}

const char* getDescription () {
    return "This plugin makes coffee";
}


// There are three exportable methods from the DLL plugin.
// 1. A method that the host applciation can call to get a pointer to the plugin interface
// 2. A method that passes a pointer to the host interface to the plugin
// 3. A test method that the host application calls which in turn calls a
//    method in the host. 

extern "C" {

    // Create the plugin interface and return a pointer to it 
    EXPORTED TPluginInterface* getPluginInterface () {
        pluginInterface = (TPluginInterface*) malloc (sizeof (TPluginInterface));
        // Initialize the method pointers with the actual methods. 
        pluginInterface->add = add;
        pluginInterface->getVersion = getVersion;
        pluginInterface->getAuthor = getAuthor;
        pluginInterface->getDescription = getDescription;
        pluginInterface->getDisplayName = getDisplayName;
        pluginInterface->getID = getID;
        return pluginInterface;
    }

    // The host application can call this to pass over to the DLL a 
    // pointer to the host interface
    EXPORTED void setHostInterface (THostInterface* _hostInterface) {
        hostInterface = _hostInterface;
    }


    // A test method the host application can call which in turn calls
    // two other host methods. A DLL can't use printf to print messages to the
    // console, so we expose a print method in the host that the DLL can use instead. 
    EXPORTED void makePluginTalkToHost () {
        int hostversion;

        hostversion = hostInterface->getHostVersion ();
        hostInterface->printPtr (hostversion);
    }
}