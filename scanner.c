//
//  scanner.c
//  Lab3
//
//  Created by Bryce Holton.
//  Copyright (c) 2014 Bryce Holton. All rights reserved.
//

#include <stdio.h>
#include "scanner.h"
#include <ctype.h>


/*******************
 Static functions needed for the scanner
 You need to design the proper parameter list and
 return types for functions with ???.
 ******************/


typedef enum
{
    LETTER, DIGIT, QUOTE, SPECIAL, EOF_CODE,
}
CharCode;

typedef struct
{
    char *string;
    TokenCode token_code;
}
RwStruct;

const RwStruct rw_table[9][10] = {
    {{"do",DO},{"if",IF},{"in",IN},{"of",OF},{"or",OR},{"to",TO},{NULL,0}}, //Reserved words of size 2
    {{"and",AND},{"div",DIV},{"end",END},{"for",FOR},{"mod",MOD},{"nil",NIL},{"not",NOT},{"set",SET},{"var",VAR},{NULL,0}}, //Reserved words of size 3
    {{"case",CASE},{"else",ELSE},{"file",FFILE},{"goto",GOTO},{"then",THEN},{"type",TYPE},{"with",WITH},{NULL,0}}, //Reserved words of size 4
    {{"array",ARRAY},{"begin",BEGIN},{"const",CONST},{"label",LABEL},{"until",UNTIL},{"while",WHILE},{NULL,0}},  //Reserved words of size 5
    {{"downto",DOWNTO}, {"packed",PACKED},{"record",RECORD}, {"repeat",REPEAT},{NULL,0}},  // Reserved words of size 6
    {{"program", PROGRAM},{NULL,0}}, // Reserved words of size 7
    {{"function", FUNCTION},{NULL,0}}, // Reserved words of size 8
    {{"procedure", PROCEDURE},{NULL,0}}  // Reserved words of size 9
};


BOOLEAN get_source_line(char source_buffer[])
{
    char print_buffer[MAX_SOURCE_LINE_LENGTH + 9];
    //    char source_buffer[MAX_SOURCE_LINE_LENGTH];  //I've moved this to a function parameter.  Why did I do that?
    static int line_number = 0;
    
    if (fgets(source_buffer, MAX_SOURCE_LINE_LENGTH, src_file) != NULL)
    {
        ++line_number;
        sprintf(print_buffer, "%4d: %s", line_number, source_buffer);
        print_line(print_buffer, src_name, todays_date);
        //strcpy(sourceline,source_buffer);
        return (TRUE);
    }
    else
    {
        return (FALSE);
    }
}
Token* get_token(char *stringtotoken)
{
    char source_buffer[MAX_TOKEN_STRING_LENGTH];
    char ch = source_buffer[0]; //This can be the current character you are examining during scanning.
    int chint = (int)ch;
    char token_string[MAX_TOKEN_STRING_LENGTH]; //Store your token here as you build it.
    char *token_ptr =token_string; //write some code to point this to the beginning of token_string
    
    //if(sourceline[0]=='\n');
    //{get_source_line(source_buffer);}
    
    //struct stack * newptr=(struct stack*)malloc(sizeof(struct stack));
    struct Token * token1 = (struct Token*)malloc(sizeof(Token));
    //???;  //I am missing the most important variable in the function, what is it?  Hint: what should I return?
    
    //2.  figure out which case you are dealing with LETTER, DIGIT, QUOTE, EOF, or special, by examining ch
    if (isdigit(chint))
    {
        if (isalpha(chint))
        {
            token1 =get_word(source_buffer,token1);
        }
        else
        {
            if (chint == 39)
                token1 = get_string(source_buffer,token1);
        }
        token1 = get_number(source_buffer,token1);
    }
    else
        token1 = get_special(source_buffer,token1);
    
    //3.  Call the appropriate function to deal with the cases in 2.
    strcpy(sourceLine,source_buffer);
    return &token1; //What should be returned here?
}
static char get_char(char stringwithOutSpaces[])
{
    char returnchar;
    if(sourceLine[0]=='\n')
    {
        get_source_line(stringwithOutSpaces);
    }
    skip_blanks(stringwithOutSpaces);
    skip_comment(stringwithOutSpaces);
    returnchar=stringwithOutSpaces[0];
    return returnchar;
    /*if(stringwithOutSpaces[0]=='\n')
     {}
     }
     else if (stringwithOutSpaces[0]=='EOF'){return 'EOF'};
     else if (isdigit(stringwithOutSpaces[0]))
     /*
     If at the end of the current line (how do you check for that?),
     we should call get source line.  If at the EOF (end of file) we should
     set the character ch to EOF and leave the function.
     */
    
    /*
     Write some code to set the character ch to the next character in the buffer
     */
}
void skip_blanks(char stringwithspaces[])
{
    
    char *str=stringwithspaces;
    int i;
    for (i=0;stringwithspaces[i]==' ';i++)
    {}
    
    str=str+i;
    strcpy(stringwithspaces,str);
}
void skip_comment(char stringwithcomment[])
{
    /*
     Write some code to skip past the comments in the program and return a pointer
     to the first non blank character.  Watch out for the EOF character.
     */
    
    /*
     char stringwithoutcomment[];
     for(i = 0; i < strlen(stringwithcomment) - 2; i++)
     {
     if(stringwithcomment[i] == '/' && stringwithcomment[i+1] == '/')
     stringwithoutcomment[i] = '\0';
     else
     stringwithoutcomment[i] = stringwithcomment[i];
     }
     return stringwithoutcomment;
     */
    //Sorry this is wrong as comments are cretaed in pascel with '{' and end with '}'
    if(stringwithcomment[0] == '{')
    {
        int i;
        for(i = 0; stringwithcomment[i]!='}' || stringwithcomment[i]!='\n'; i++)
        {}
        strcpy(stringwithcomment,&stringwithcomment[i]);
        
    }
    
    
}
static struct Token* get_word(char stringwithuppercase[], struct Token *addtoken)
{
    /*
     Write some code to Extract the word
     */
    
    //Downshift the word, to make it lower case
    
    /*
     Write some code to Check if the word is a reserved word.
     if it is not a reserved word its an identifier.
     */ int settokencode;
        LiteralType setliteraltype;
		int i,j;
        char stringwithoutuppercase[80];
        strcpy(stringwithoutuppercase, stringwithuppercase);
	downshift_word(stringwithoutuppercase);
       
    
       // int i,j;
        for (i = 0; i < 9; i++)
        {
            for(j = 0; j < 1-0; j++)
            {
                if(strcmp(stringwithoutuppercase,rw_table[i][j].string) == 0)
                    settokencode = rw_table[i][j].token_code;
            }
        }
        addtoken->tokenCode = settokencode;
        strcpy((addtoken->LiteralValue),stringwithoutuppercase);
        return addtoken;
}
static struct Token* get_number(char stringnum[], struct Token *addtoken)
{
    
	//char WordNumber[80];
	//char *saveptr;
	//strcpy(WordNumber,strtok_r(stringnum,' ',saveptr));
    
    
    /*
     Write some code to Extract the number and convert it to a literal number.
     */
    int numlength = strlen(stringnum);
    int realorint = 0; // 0 if stringnum is an integer, 1 if it is a real number
    char currentchar;
    int i;
    TokenCode settokencode = NUMBER;
    LiteralType setliteraltype = INTEGER_LIT; // initialize LiteralType
    addtoken->tokenCode = settokencode;             // with default as integer
    strcpy(addtoken->LiteralValue, stringnum);
    
    for(i=0; i<numlength; i++)
    {
        currentchar = stringnum[i];
        if(currentchar == 'e' || currentchar == '.') // check for real number
        {
            LiteralType setliteraltype = REAL_LIT;
            i = i + numlength; // exits while loop
            realorint=1;
        }
        
    }
    addtoken->typeOfLiteral = setliteraltype;
    return addtoken;
    
    
    
}
static struct Token* get_string(char stringwithquotes[],struct Token *addstring)
{
	char stringwithoutquotes[80];
    int i;
    /*
     Write some code to Extract the string
     */
    LiteralType setliteraltype = STRING_LIT;
    TokenCode settokencode = STRING;
    addstring->typeOfLiteral = setliteraltype;
    addstring->tokenCode = settokencode;
    //int strl = strlen(stringwithquotes)-2;
    
    for(i = 0; i < strlen(stringwithoutquotes); i++)
    {
        stringwithoutquotes[i] = stringwithoutquotes[i+1];
    }
	stringwithoutquotes[i+1]='\0';
    strcpy(addstring->LiteralValue,stringwithoutquotes);
    return addstring;
 }

static struct Token* get_special(char stringspecial[], struct Token *addtoken)
{
    /*
     Write some code to Extract the special token.  Most are single-character
     some are double-character.  Set the token appropriately.
     */
    int chint = stringspecial[0];
    TokenCode settokencode;
    switch(chint) // set TokenCode
    {
        case 94:
            settokencode = UPARROW;
            break;
        case 42:
            settokencode = STAR;
            break;
        case 40:
            settokencode = LPAREN;
            break;
        case 41:
            settokencode = RPAREN;
            break;
        case 45:
            settokencode = MINUS;
            break;
        case 91:
            settokencode = LBRACKET;
            break;
        case 93:
            settokencode = RBRACKET;
            break;
        case 58:
            if(stringspecial[1] == '=')
                settokencode = COLONEQUAL;
            else
                settokencode = COLON;
            break;
        case 59:
            settokencode = SEMICOLON;
            break;
        case 60:
            if(stringspecial[1] == '=')
                settokencode = LE;
            else
                settokencode = LT;
            break;
        case 62:
            if(stringspecial[1] == '=')
                settokencode = GE;
            else
                settokencode = GT;
            break;
        case 44:
            settokencode = COMMA;
            break;
        case 46:
            if(stringspecial[1] == '.')
                settokencode = DOTDOT;
            else
                settokencode = PERIOD;
            break;
        case 47:
            settokencode = SLASH;
            break;
    }
    addtoken->tokenCode = settokencode;
    strcpy(addtoken->LiteralValue, stringspecial);
    return addtoken; 
}
static void downshift_word(char stringuppercase[])
{
    /*
     Make all of the characters in the incoming word lower case.
     */
	int i;
    char stringlowercase[80];
    strcpy(stringlowercase, stringuppercase);
    
    for(i=0; i<strlen(stringlowercase); i++)
    {
        stringlowercase[i] = tolower(stringlowercase[i]);
    }
    strcpy(stringuppercase,stringlowercase);
    // return stringlowercase;
    
}
static BOOLEAN is_reserved_word(char stringsearchword[])
{
    /*
     Examine the reserved word table and determine if the function input is a reserved word.
     */
    int i,j;
	//char * strings;
    for(i = 0; i < 9; i++)
	        {
            for(j = 0; j < 1-0; j++)
            {

				//strings=rw_table[i][j]->string;
                if(strcmp(stringsearchword,(rw_table[i][j].string)) == 0)
                    return TRUE;
            }
        }
    return FALSE;
}
