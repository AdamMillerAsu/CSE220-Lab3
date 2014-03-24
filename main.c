//
//  main.c 
//  Lab3
//
//  Created by Bryce Holton.
//  Copyright (c) 2014 Bryce Holton. All rights reserved.
//

//ASUTEAM23////////
//Adam Miller
//Mike Burgett
//Daniel Wong


#include <stdio.h>
#include "common.h"
#include "print.h"
#include "scanner.h"

void init_scanner(FILE *source_file, char source_name[], char date[]);
BOOLEAN get_source_line(char source_buffer[]);
void quit_scanner(FILE *src_file, Token *list);
void add_token_to_list(Token *list, Token *new_token);
char source_buffer[80];
char wordToken[80];

int main(int argc, const char * argv[])
{
	int i;
    Token *token;
    Token *token_list; //This needs to be implemented as a linked list in scanner.h.
    char source_name[MAX_FILE_NAME_LENGTH];
    char date[DATE_STRING_LENGTH];
    FILE *source_file = init_lister(argv[1], source_name, date);
    init_scanner(source_file, source_name, date);
    
    do{
        
        if (source_buffer[0]=='\n')
        {
            get_source_line(source_buffer);
            skip_blanks(source_buffer);
            skip_comment(source_buffer);
        }
        
        
        
        for(i=0;source_buffer[i]!=' ';++i)
        {
            wordToken[i]=source_buffer[i];
        }
        wordToken[i]='\0';
        sprintf(source_buffer,"%s",&source_buffer[i]);
        skip_blanks(source_buffer);
        skip_comment(source_buffer);
        
        do
    	{
            token = get_token(wordToken);
            add_token_to_list(token_list, token);
            print_token(token);
    	}
    	while (token != NULL);//What is the sentinal value that ends this loop?
        
    }while(wordToken[0]!=' ' || wordToken[0]!='eof' || wordToken[0]!='.');
    
    quit_scanner(source_file, token_list);
    return 0;
}
void add_token_to_list(Token *list, Token *new_token)
{
   Token *current = list;
   Token *token_to_add = new_token;
   
   while (current->next != NULL)
   {
       current = current->next;
   }
   
   //struct Token * token1 = (struct Token*)malloc(sizeof(Token));
   current->next =(struct Token*) malloc(sizeof(Token));
   current->next= token_to_add;
   current->next->next = NULL;
    
    // Add new_token to the list knowing that list is a linked list.
    
}
void quit_scanner(FILE *src_file, Token *list)
{
    Token *temp;
    while (list != NULL)
    {
        temp = list;
        list = list->next;
        free(temp);
    }
    //write code to free all of the memory for the token list

    fclose(src_file);
}
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
        return (TRUE);
    }
    else
    {
        return (FALSE);
    }
}
