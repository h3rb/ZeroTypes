/*

 ZeroTypes Library 
 Open source license: BSD 
 (See accompanying License.txt for details)

 Author: H. Elwood Gilliland III
 Copyright (c) 2007-2017

*/
#pragma once
#pragma warning (disable:4100)


#if defined(WIN32) || defined(WIN32_LEAN_AND_MEAN) || defined(WINVER)
#include <Windows.h>
#endif
#include "main.h"

#include "string_functions.h"
#include "LinkedList.h"
#include "Randoms.h"

#include "Examples.h"

// WINMAIN ////////////////////////////////////////////////

#if defined(WIN32) || defined(WIN32_LEAN_AND_MEAN) || defined(WINVER)
int WINAPI WinMain(_In_ HINSTANCE hinstance,
                   _In_opt_ HINSTANCE hprevinstance,
                   _In_ LPSTR lpCmdLine,
                   _In_ int ncmdshow)
#else
int main ( int argc, char **argv ) 
#endif
{
 InitWorkStrings();
 randoms.LoadRandomDotOrg("data/random.org/random-0.dat");  // I have 10 of these special files I made, pm me on handmade for the other 9
 ZeroTypesTest();
 Examples();
 ZIndexed_Rigorous_Test();
 return (int) (0); // return to Windows
} // end WinMain
