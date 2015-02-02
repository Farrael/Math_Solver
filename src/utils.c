#include <iostream>
#include <string.h>
#include <stdlib.h>

/* Internal dependencies */
#include "utils.h"

using namespace std;

char hook[2] = {'[',']'};
char bracket[2] = {'(',')'};

/**
 * Converts array of char into n. 
 * Returns if it was "successful"
 */
void toInteger(char* str, int& n){
	unsigned int size = strlen(str);
	n = 0;
	bool first = true;

	for(unsigned int i = 0; i < size; i++){
		if(!isdigit(str[i]))
			first = false;

		if(first && str[i] >= '0' && (char)str[i] <= '9')
			n += (str[i] - 48) * pow(size - i - 1);
		else
			n /= 10;
	}
}

/**
 * Mathematical function : pow
 */
int pow(int a) {
    int mult = 1;
    for(int b = 0; b < a; b++)
        mult *= 10;

    return mult;
}

/**
 * Remove unexpected space
 * str : String to trim
 */
void trim(char* str) {
    int start = 0;
    char* buffer = str;
    while(*str && *str++ == ' ')
    	++start;

    while(*str++);
    int end = str - buffer - 1; 

    while (end > 0 && buffer[end - 1] == ' ') 
    	--end;

    buffer[end] = 0;
    if (end <= start || start == 0)
    	return;

    str = buffer + start;
    while ((*buffer++ = *str++));
}

/**
 * Add characters to char[]
 * source : Char[] source
 * add : Characters to add
 */
char* addChar(char* source, const char* add){
	char* result = (char*) malloc(strlen(source) + strlen(add) + 1);
	strcpy(result, source);
	strcat(result, add);
	return result;
}

/**
 * Remove characters from char[]
 * text : Array of char to split
 * position : Split position
 * size : Size of split
 */
char* substr(char* text, int position, int size){
	char* token = (char*) malloc(size+1);
	strncpy(token, text + position, size);
	token[size] = '\0';
	return token;
}

/**
 * Search pattern in string
 * text : String to split
 * pattern : 2d array of characters
 * depth : depth recursion
 */
Array* regex(char* text, char* pattern, int depth) {
	int dep = 0, pos = 0;
	depth++; // Initial depth to 1

	Array *result = NULL;
	for(unsigned int i = 0; i < strlen(text); i++) {
	    if(text[i] == pattern[0] && ++dep == depth){
	    	pos = i;
	    } else if(text[i] == pattern[1] && dep-- == depth) {
	    	char* token = substr(text, pos+1, i - pos - 1);
	    	if(token != '\0'){
	    		trim(token);
	    		result = push_back(result, token);
	    	}
	    }
	}

	return result;
}

/**
 * Split string with delimiter
 * text : String to cut
 * pattern : Pattern to validate
 * delimiter : Cut delimiter
 * depth : Depth to validate
 */
Array* cut(char* text, char* pattern, char delimiter, int depth) {
	bool valid = true;
	Array *result = NULL;
	int dep = 0, pos = 0;

	for(unsigned int i = 0; i <= strlen(text); i++) {
		if(text[i] == pattern[0] && dep == depth && !valid)
			return NULL;

		if(text[i] == pattern[0] && ++dep == depth){
	    	pos = i+1;
	    } else if((text[i] == pattern[1] && dep-- == depth)
	    			|| (text[i] == delimiter && dep == depth)) {

	    	if(text[i] == delimiter)
				valid = true;
			if(text[i] == pattern[1])
				valid = false;

	    	char* token = substr(text, pos, i - pos);
	    	trim(token);
	    	if(token != '\0' && token[0] != 0)
	    		result = push_back(result, token);

	    	pos = i+1;
	    }
	}

	if(depth == 0){
		char* token = substr(text, pos, strlen(text) - pos);
		trim(token);
		result = push_back(result, token);
	}

	return result;
}

/**
 * Add element at the end of the list
 * list : List to modify
 * value : Element to add
 */
Array* push_back(Array *list, char* value){	
	if(list != NULL){
		Array* temp = list;
		while(temp->next != NULL){
			temp = temp->next;
		}

		temp->next = new Array;
		temp->next->value = value;
		temp->next->next = NULL;
	} else {
		list = new Array;
		list->value = value;
		list->next = NULL;
	}

	return list;
}

/**
 * Return the size of a list
 * list : List to get size
 */
int size(Array *list){
	int i = 0;
	while(list != NULL){
		i++;
		list = list->next;
	}

	return i;
}