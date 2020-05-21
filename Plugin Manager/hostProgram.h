// These are the three methods that the host will export to a plugin
#pragma once

int getHostVersion ();

int mult (int a, int b);

// We can't call printf inside the dll so when
// ever the dll needs to print something it calls this. 
void hostPrint (int x);