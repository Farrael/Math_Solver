#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * Split string with delimiter
 * text : String to split
 * delimiter : split delimiter
 */
vector<string> split(string text, string delimiter) {
	vector<string> result;
	size_t position = 0;
	string token;
	while ((position = text.find(delimiter)) != string::npos) {
	    token = text.substr(0, position);
	    if(token != "")
	    	result.push_back(token);
	    text.erase(0, position + delimiter.length());
	}

	result.push_back(text);
	return result;
}

/**
 * Search pattern in string
 * text : String to split
 * pattern : 2d array of characters
 * depth : depth recursion
 */
vector<string> regex(string text, char* pattern, int depth) {
	size_t i = 0, pos = 0, diff = 0;
	int dep = 0;

	vector<string> result;
	string token;

	while (i < text.size()) {
	    if(text[i] == pattern[0] && ++dep == depth){
	    	pos = i;
	    } else if(text[i] == pattern[1] && dep-- == depth) {
	    	diff = i - pos;
	    	token = text.substr(pos+1, diff - 1);
	    	if(token != "")
	    		result.push_back(token);
	    	text.erase(pos, diff + 1);
	    	i = pos - 1;
	    }
	    i++;
	}

	result.push_back(text);
	return result;
}