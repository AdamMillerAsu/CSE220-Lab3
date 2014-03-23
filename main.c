//
//  main.c
//  Lab3
//
//  Created by Bryce Holton.
//  Copyright (c) 2014 Bryce Holton. All rights reserved.
//

#include <stdio.h>
#include "common.h"
#include "print.h"
#include "scanner.h"

FILE *init_lister(const char *name, char source_file_name[], char dte[]);
void quit_scanner(FILE *src_file, Token *list);
void add_token_to_list(Token *list, Token *new_token);
char source_buffer[80];
char wordToken[80];

int main(int argc, const char * argv[])
{
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
        
        
        int i;
        for(i=0;source_buffer[i]!=' ';++i)
        {
            wordToken[i]=source_buffer[i];
        }
        wordToken[i]='\0';
        
        do
    	{
            token = get_token(wordToken);
            add_token_to_list(token_list, token);
            print_token(token);
    	}
    	while (token != ".");//What is the sentinal value that ends this loop?
        
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
   
   
   current->next = malloc(sizeof(Token));
   current->next->new_token = token_to_add;
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
FILE *init_lister(const char *name, char source_file_name[], char dte[])
{
    time_t timer;
    FILE *file;
    
    strcpy(source_file_name, name);
    file = fopen(source_file_name, "r");
    time(&timer);
    strcpy(dte, asctime(localtime(&timer)));
    return file;
}

