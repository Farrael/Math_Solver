#include <iostream>
#include <string>
#include <vector>
#include <sstream>

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
vector<string> split(string text, string delimiter) {
	vector<string> result;
	size_t position = 0;
	string token;
	while ((position = text.find(delimiter)) != string::npos) {
	    token = text.substr(0, position);
	    if(token != "")
	    	result.push_back(trim(token));
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
	    		result.push_back(trim(token));
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
vector<string> cut(string text, char* pattern, char delimiter, int depth) {
	size_t i = 0, pos = 0;
	int dep = 0;

	vector<string> result;
	string token;

	while (i < text.size()) {
		if(text[i] == pattern[0] && ++dep == depth){
		  	pos = i + 1;
		} else if((text[i] == pattern[1] && dep-- == depth)
		   			|| (text[i] == delimiter && dep == depth)) {
		  	token = text.substr(pos, i - pos);
		  	if(token != "")
		  		result.push_back(trim(token));
		  	text.erase(0, i + 1	);
		  	i = pos = 0;
		}
		i++;
	}

	if(text != "" && depth == 0)
	    result.push_back(trim(text));

	return result;
}