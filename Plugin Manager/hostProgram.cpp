#include "os_call.h"
#include "api.h"
#include "hostProgam.h"
#include <stdio.h>

//HINSTANCE handle; // Handle to the DLL
void *handle;



// SOME TERMINOLOGY
// Host Application : this is the applcaition that wil load an use the plugins
// Plugin: This is a dynamically loaded DLL that the host application can use
// A symbol starting with T is a type

// These two structs much be declared in both teh Host applciation and any plugin
typedef void* (*pluginInterfacePtr) ();
typedef void* (*hostInterfacePtr) (THostInterface*);
typedef void* (*makePluginTalkToHostPtr) ();

pluginInterfacePtr getPluginInterface;
hostInterfacePtr   setHostInterface;

makePluginTalkToHostPtr makePluginTalkToHost;

// These are the three methods that the host will export to a plugin

int getHostVersion () {
	return 4321;
}

int mult (int a, int b) {
	return a * b;
}


// We can't call printf inside the dll so when
// ever the dll needs to print something it calls this. 
void hostPrint (int x) {
	printf ("Host Print Function: %d\n", x);
}




void main () {

	// Two pointers to the host and plugin interfaces
	TPluginInterface* pluginInterface;
	THostInterface*   hostInterface;

	// Fill the interface method pointers with the actual methods
	hostInterface = (THostInterface*) malloc (sizeof (THostInterface));
	hostInterface->getHostVersion = getHostVersion;
	hostInterface->multPtr = mult;
	hostInterface->printPtr = hostPrint;

	printf ("Starting main program\n");
	// Load the DLL
	handle = LoadLibraryA ("myplugin"); //dont add extension to plugin name

	// If loaded ok then retrieve the exported methods
	if (handle != NULL) {
		getPluginInterface = (pluginInterfacePtr)GetFunction (handle, "getPluginInterface");
		setHostInterface = (hostInterfacePtr) GetFunction (handle, "setHostInterface");

		makePluginTalkToHost = (makePluginTalkToHostPtr) GetFunction (handle, "makePluginTalkToHost");

		if (getPluginInterface != NULL) {
			// Get the plugin interface
			pluginInterface = (TPluginInterface*) getPluginInterface ();
			
			printf ("Call dll function: %d\n", pluginInterface->add (3, 4));
			printf ("Version = %d\n", pluginInterface->getVersion ());
			printf ("Author = %s\n", pluginInterface->getAuthor ());
		} else
		   printf ("Unable to get plugin interface");

		// Next sent a pointer to the host interface to the plugin
		if (setHostInterface != NULL) {
			setHostInterface (hostInterface);
			// Call the dll test method that will test the call back to the host
			makePluginTalkToHost ();
		} else
			printf ("Unable to set host interface");

		FreeSharedLibrary(handle);
	} else
		printf ("Error: Unable to open plugin dll\n");

	getchar ();
}