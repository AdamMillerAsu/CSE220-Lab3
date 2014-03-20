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
static char get_char(char);
static char skip_comment(char);
static void skip_blanks(char);
static Token get_word(char);
static Token get_number(char);
static Token get_string(char);
static Token get_special(char);
static char downshift_word(char);
static BOOLEAN is_reserved_word(char);
char sourceLine[MAX_TOKEN_STRING_LENGTH];

typedef enum
{
    LETTER, DIGIT, QUOTE, SPECIAL, EOF_CODE,
}
CharCode;

/*********************
 Static Variables for Scanner
 Must be initialized in the init_scanner function.
 *********************/
static FILE *src_file;
static char src_name[MAX_FILE_NAME_LENGTH];
static char todays_date[DATE_STRING_LENGTH];
static CharCode char_table[256];  // The character table
//char sourceline[MAX_TOKEN_STRING_LENGTH];

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

void init_scanner(FILE *source_file, char source_name[], char date[])
{
    src_file = source_file;
    strcpy(src_name, source_name);
    strcpy(todays_date, date);
    
    /*******************
     initialize character table, this table is useful for identifying what type of character 
     we are looking at by setting our array up to be a copy the ascii table.  Since C thinks of 
     a char as like an int you can use ch in get_token as an index into the table.
     *******************/
    
}
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
Token* get_token()
{
    char ch; //This can be the current character you are examining during scanning.
    char token_string[MAX_TOKEN_STRING_LENGTH]; //Store your token here as you build it.
    char *token_ptr =???; //write some code to point this to the beginning of token_string
    char source_buffer[MAX_TOKEN_STRING_LENGTH];
    
    
    if(sourceline[0]=='\n');
    {get_source_line(source_buffer);}
    
    
    Token Token1;
    //???;  //I am missing the most important variable in the function, what is it?  Hint: what should I return?
    
    
    //1.  Skip past all of the blanks
    
    skip_blanks(source_buffer);
    //2.  figure out which case you are dealing with LETTER, DIGIT, QUOTE, EOF, or special, by examining ch
    ch=get_char(source_buffer);
        if (ch=='\n');
        {
            {get_source_line(source_buffer);}
            skip_blanks(source_buffer);
            ch=get_char(source_buffer);
            
        }
        else if (isdigit(ch));
        {
            get_number();
        }
        else if (isalpha(ch));
        {
            get_word();
        }
    
    //3.  Call the appropriate function to deal with the cases in 2.
    strcpy(sourceline,source_buffer);
    return Token1; //What should be returned here?
}
static char *get_char(char stringwithOutSpaces)
{
    
    return stringwithOutSpaces[0];
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
static void skip_blanks(char stringwithspaces[])
{

    
    
    //char testString[]="   adfaf";
    //puts(testString);
    char *str=stringwithspaces;
    //char *strPtr;
    //    strcpy(testString,"         hih");
    int i;
    for (i=0;stringwithspaces[i]==' ';i++)
    {}
    //*str=testString;
    str=str+i;
    strcpy(stringwithspaces,str);
    //puts(testString);
    
    
    
    
}
static char *skip_comment(char stringwithcomment[])
{
    /*
     Write some code to skip past the comments in the program and return a pointer
     to the first non blank character.  Watch out for the EOF character.
     */
}
static char *get_word(char stringwithuppercase[])
{
    /*
     Write some code to Extract the word
     */
    
    //Downshift the word, to make it lower case
    
    /*
     Write some code to Check if the word is a reserved word.
     if it is not a reserved word its an identifier.
     */
}
static Token *get_number(char stringnum[])
{
    /*
     Write some code to Extract the number and convert it to a literal number.
     */
    int numlength = strlen(stringnum);
    int realorint = 0; // 0 if stringnum is an integer, 1 if it is a real number
    char currentchar;
    
    Token addtoken = new Token; // create new NUMBER Token
    enum TokenCode settokencode = NUMBER;
    enum LiteralType setliteraltype = INTEGER_LIT; // initialize LiteralType
    addtoken.tokencode = settokencode;             // with default as integer
    addtoken.LiteralValue = stringnum;
    while(i=0; i<numlength; i++)
    {
        currentchar = stringnum[i];
        if(currentchar == 'e' || currentchar == '.') // check for real number
        {
            enum LiteralType setliteraltype = REAL _LIT;
            i = i + numlength; // exits while loop
        }
    }
    addtoken.typeOfLiteral = setliteraltype;
    return addtoken;
}
static Token *get_string(char stringwithquotes[])
{
    /*
     Write some code to Extract the string
     */
    Token addstring = malloc(sizeof(addstring)); // create new STRING Token
    enum LiteralType setliteraltype = STRING_LIT;
    enum TokenCode settokencode = STRING;
    addstring.typeOfLiteral = setliteraltype;
    addstring.tokenCode = settokencode;
    
    char stringwithoutquotes[strlen(stringwithquotes)-2];
    for(i = 0; i < strlen(stringwithoutquotes); i++)
    {
        stringwithoutquotes[i] = stringwithoutquotes[i+1];
    }
    strcpy(addstring.LiteralValue,stringwithoutquotes);
    return addstring;
}
static Token *get_special(char stringspecial[])
{
    /*
     Write some code to Extract the special token.  Most are single-character
     some are double-character.  Set the token appropriately.
     */
}
static char *downshift_word(char stringuppercase[])
{
    /*
     Make all of the characters in the incoming word lower case.
     */
    char stringlowercase[];
    strcpy(stringlowercase, stringuppercase);
    for(i=0; i<strlen(stringlowercase); i++)
    {
        stringlowercase[i] = tolower(stringlowercase[i]);
    }
    return stringlowercase;
     
}
static BOOLEAN is_reserved_word(char stringsearchword[])
{
    /*
     Examine the reserved word table and determine if the function input is a reserved word.
     */
    return FALSE;
}
