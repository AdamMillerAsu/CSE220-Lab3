//
//  scanner.h
//  Lab3
//
//  Created by Bryce Holton.
//  Copyright (c) 2014 Bryce Holton. All rights reserved.
//

//ASUTEAM23
//Adam Miller
//Mike Burgett
//Daniel Wong

#ifndef Lab3_scanner_h
#define Lab3_scanner_h

#include "common.h"
#include "print.h"

Token* get_token(char*);
void skip_comment(char[]);
void skip_blanks(char[]);
char sourceLine[MAX_TOKEN_STRING_LENGTH];

#endif
