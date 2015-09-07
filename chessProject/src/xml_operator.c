/*
 * xml_operator.c
 *
 *  Created on: Sep 7, 2015
 *      Author: sivan
 */

#include <stdio.h>
#include <stdlib.h>

#define ONE_LINE 100;

enum xml_markups{next_turn, game_mode, difficulty, user_color};

struct xml_file_data{
	char next_turn[];
	int game_mode;
	int difficulty;
	char user_color[];
};

typedef struct xml_file_data xml_t;

xml_t* exctruct_xml_file(char* slot, ){
	xml_t* xml_data_file = NULL;
	File * input_file = NULL;
	char line[];
	int line_contains_enum = 0, i = 0;

	input_file = fopen("projext_file_name/xml_files/" + slot, "r");
	line = fscanf(input_file, "\n%s");
	while( line != EOF){
		for(i = next_turn; i < user_color; i++){
			//need to add conversion enum i to string
			line_contains_enum = strstr(line,"i");
			if (line_contains_enum != NULL){
				switch(i){
					case next_turn:
						xml_data_file->next_turn = strtok(line, "><"); //make sure output is correct
						break;
					case game_mode:
						xml_data_file-> game_mode = strtok(line, "><"); //need to convert to init, make sure output is correct
						break;
					case difficulty:
						xml_data_file-> difficulty = strtok(line, "><"); //need to convert to init, make sure output is correct
						break;
					case user_color:
						xml_data_file-> user_color = strtok(line, "><"); //make sure output is correct
						break;
						}
			}
		}
	}
	return xml_data_file;
}
