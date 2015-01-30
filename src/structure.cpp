#include <iostream>
#include <string>
#include <vector>

/* Internal dependencies */
#include "structure.h"
#include "utils.h"

using namespace std;

Variable* to_variable(string input){
	if(input[0] != 'x')
		return NULL;

	vector<string> splitted = split(input, ",");
	if(splitted.size() != 2)
		return NULL;

	Variable *result = new Variable;
	result->name = splitted[0];
	//result->value = splitted[1];

	return result;
}

Function* to_function(string input){
	if(input[0] != 'f')
		return NULL;

	vector<string> reg = regex(input, hook, 1);
	if(reg.empty())
		return NULL;

	return new Function;

/*	Function *result = new Function;
	result->name = splitted[0];
	result->arg1 = splitted[1];
	result->arg1 = splitted[2];*/

	//return result;
}