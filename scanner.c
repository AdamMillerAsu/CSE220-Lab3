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
static char get_char(char*);
static void skip_comment(char*);
static void skip_blanks(char*);
static struct *Token get_word(char*);
static struct *Token get_number(char*);
static struct *Token get_string(char *);
static struct *Token get_special(char*);
static void downshift_word(char*);
static BOOLEAN is_reserved_word(char*);
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
Token* get_token(char *stringtotoken)
{
    char source_buffer[MAX_TOKEN_STRING_LENGTH];
    char ch = source_buffer[0]; //This can be the current character you are examining during scanning.
    int chint = (int)ch;
    char token_string[MAX_TOKEN_STRING_LENGTH]; //Store your token here as you build it.
    char *token_ptr =token_string; //write some code to point this to the beginning of token_string
    
    //if(sourceline[0]=='\n');
    //{get_source_line(source_buffer);}
    
    
    struct Token token1;
    //???;  //I am missing the most important variable in the function, what is it?  Hint: what should I return?
    
    //2.  figure out which case you are dealing with LETTER, DIGIT, QUOTE, EOF, or special, by examining ch
    if (isdigit(chint))
    {
        if (isalpha(chint))
        {
            token1 =get_word(source_buffer);
        }
        else
        {
            if (chint == 39)
                token1 = get_string(source_buffer);
        }
        token1 = get_number(source_buffer);
    }
    else
        token1 = get_special(source_buffer);
    
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
static void skip_blanks(char stringwithspaces[])
{
    
    char *str=stringwithspaces;
    int i;
    for (i=0;stringwithspaces[i]==' ';i++)
    {}
    
    str=str+i;
    strcpy(stringwithspaces,str);
}
static void skip_comment(char stringwithcomment[])
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
        strcpy(stringwithcomment,stringwithcomment[i]);
        
    }
    
    
}
static struct *Token get_word(char stringwithuppercase[])
{
    /*
     Write some code to Extract the word
     */
    
    //Downshift the word, to make it lower case
    
    /*
     Write some code to Check if the word is a reserved word.
     if it is not a reserved word its an identifier.
     */
        char stringwithoutuppercase[];
        strcpy(stringwithoutuppercase))
	downshift_word(stringwithoutuppercase);
        struct Token addtoken = malloc(sizeof(struct Token));
        TokenCode settokencode;
        LiteralType setliteraltype;
    
        for(int c = 0; c < 9; c++)
        {
            for(int r = 0; r < 1-0; r++)
            {
                if(strcmp(stringwithoutuppercase,rw_table[c][r].string == 0))
                    settokencode = rw_table[c][r].token_code;
            }
        }
        addtoken.tokenCode = sttokencode;
        addtoken.LiteralValue = stringwithoutuppercase;
        return addtoken;
}
static struct *Token get_number(char stringnum[])
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
    
    struct Token addtoken = malloc(sizeof(struct Token)); // create new NUMBER Token
    TokenCode settokencode = NUMBER;
    LiteralType setliteraltype = INTEGER_LIT; // initialize LiteralType
    addtoken.tokenCode = settokencode;             // with default as integer
    addtoken.LiteralValue = stringnum;
    int i;
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
    addtoken.typeOfLiteral = setliteraltype;
    return addToken;
    
    
    
}
static struct*Token get_string(char stringwithquotes[])
{
    /*
     Write some code to Extract the string
     */
    struct Token addstring = malloc(sizeof(struct Token)); // create new STRING Token
    LiteralType setliteraltype = STRING_LIT;
    TokenCode settokencode = STRING;
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
static void get_special(char stringspecial[])
{
    /*
     Write some code to Extract the special token.  Most are single-character
     some are double-character.  Set the token appropriately.
     */
    
}
static struct *Token get_special(char stringspecial[])
{
    /*
     Write some code to Extract the special token.  Most are single-character
     some are double-character.  Set the token appropriately.
     */
    int chint = stringsearchword[0];
    struct Token addtoken = malloc(sizeof(struct Token));
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
            if(stringseachword[1] == '=')
                settokencode = COLONEQUAL;
            else
                settokencode = COLON;
            break;
        case 59:
            settokencode = SEMICOLON;
            break
        case 60:
            if(stringsearchword[1] == '=')
                settokencode = LE;
            else
                settokencode = LT;
            break;
        case 62:
            if(stringsearchword[1] == '=')
                settokencode = GE;
            else
                settokencode = GT;
            break
        case 44:
            settokencode = COMMA;
            break;
        case 46:
            if(stringsearchword[1] == '.')
                settokencode = DOTDOT;
            else
                settokencode = PERIOD;
            break;
        case 47:
            settokencode = SLASH;
            break;
    }
    addtoken.tokenCode = settokencode;
    addtoken.LiteralValue = stringsearchword;
    retun addtoken; 
}
static void downshift_word(char stringuppercase[])
{
    /*
     Make all of the characters in the incoming word lower case.
     */
    char stringlowercase[80];
    strcpy(stringlowercase, stringuppercase);
    for(int i=0; i<strlen(stringlowercase); i++)
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
    for(int c = 0; c < 9; c++)
        {
            for(int r = 0; r < 1-0; r++)
            {
                if(strcmp(stringsearchword,rw_table[c][r].string == 0))
                    return TRUE;
            }
        }
    return FALSE;
}
