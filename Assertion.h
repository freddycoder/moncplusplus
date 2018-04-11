// ***************************************************************************
// Description : 
//   Ce fichier contient la déclarations de macros pour les assertions.
//
//  Auteur :
//    Nicolas Richard
// ***************************************************************************


//   ######   N E   P A S   M O D I F I E R   C E   F I C H I E R   ######  

#pragma once

#include <crtdbg.h>

#define PRÉCONDITION(p_Condition)   _ASSERTE(p_Condition)

#define ASSERTION(p_Condition)      _ASSERTE(p_Condition)

#define POSTCONDITION(p_Condition)  _ASSERTE(p_Condition)