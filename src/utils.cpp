#include <iostream>
#include <string>
#include <sstream>

/* Internal dependencies */
#include "utils.h"

using namespace std;

char hook[2] = {'[',']'};
char bracket[2] = {'(',')'};

//converts s into n. Returns if it was "successful"
bool toInteger(string &str, int &n){
  istringstream ss(str);
  ss >> n;
  return ss.eof(); //all characters read 
}

/**
 * Remove unexpected space
 * str : String to trim
 */
string trim(string& str) {
	str.erase(0, str.find_first_not_of(' '));
	str.erase(str.find_last_not_of(' ') + 1);
	return str;
}

/**
 * Split string with delimiter
 * text : String to split
 * delimiter : split delimiter
 */
Array* split(string text, string delimiter) {
	Array *result = NULL;
	size_t position = 0;
	string token;
	while ((position = text.find(delimiter)) != string::npos) {
	    token = text.substr(0, position);
	    if(token != "")
	    	result = push_back(result, trim(token));
	    text.erase(0, position + delimiter.length());
	}

	return push_back(result, text);
}

/**
 * Search pattern in string
 * text : String to split
 * pattern : 2d array of characters
 * depth : depth recursion
 */
Array* regex(string text, char* pattern, int depth) {
	size_t i = 0, pos = 0, diff = 0;
	int dep = 0;

	Array *result = NULL;
	string token;

	while (i < text.size()) {
	    if(text[i] == pattern[0] && ++dep == depth){
	    	pos = i;
	    } else if(text[i] == pattern[1] && dep-- == depth) {
	    	diff = i - pos;
	    	token = text.substr(pos+1, diff - 1);
	    	if(token != "")
	    		result = push_back(result, trim(token));
	    	text.erase(pos, diff + 1);
	    	i = pos - 1;
	    }
	    i++;
	}

	return result;
}

/**
 * Split string with delimiter
 * text : String to cut
 * pattern : Pattern to validate
 * delimiter : Cut delimiter
 * depth : Depth to valide
 */
Array* cut(string text, char* pattern, char delimiter, int depth) {
	size_t i = 0, pos = 0;
	int dep = 0;

	Array *result = NULL;
	string token;

	while (i < text.size()) {
		if(text[i] == pattern[0] && ++dep == depth){
		  	pos = i + 1;
		} else if((text[i] == pattern[1] && dep-- == depth)
		   			|| (text[i] == delimiter && dep == depth)) {
		  	token = text.substr(pos, i - pos);
		  	if(token != "")
		  		result = push_back(result, trim(token));
		  	text.erase(0, i + 1	);
		  	i = pos = 0;
		}
		i++;
	}

	if(text != "" && depth == 0)
	    result = push_back(result, trim(text));

	return result;
}

/**
 * Add element at the end of the list
 * list : List to modify
 * value : Element to add
 */
Array* push_back(Array *list, string value){	
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