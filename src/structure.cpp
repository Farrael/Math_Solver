#include <iostream>
#include <string>
#include <vector>

/* Internal dependencies */
#include "structure.h"
#include "utils.h"

using namespace std;

Arbre* get_structure(string input){
	Arbre* arbre = new Arbre;
	int id = 0;

	if(input[0] == 'x') {
		toInteger(input.erase(0,1), id);
		arbre->typ_terme = 1;
		arbre->value = id;
	} else if(input[0] == 'f') {
		toInteger(input.erase(0,1), id);
		if(id < 0 || id > 3){
			arbre->typ_terme = 0;
			return arbre;
		}

		Arguments* head = NULL;
		Arguments* tail = NULL;
		arbre->typ_terme = 30 + id;

		// Get arguments by recursion
		// Return typ {0} invalidate the entire recursion
		vector<string> arguments = cut(input, bracket, ',', 1);
        for(size_t i = 0; i < arguments.size(); ++i) {
        	Arbre *recu = get_structure(arguments[i]);
        	if(recu->typ_terme == 0){
        		arbre->typ_terme = 0;
				return arbre;
        	}

        	Arguments* temp = new Arguments;
        	temp->value = recu;
        	temp->next = NULL;

        	if(tail != NULL)
        		tail->next = temp;

        	tail = temp;
        	if(head == NULL)
        		head = tail;
        }

        arbre->args = head;
	} else if(toInteger(input, id)) {
		arbre->typ_terme = 2;
		arbre->value = id;
	} else {
		arbre->typ_terme = 0;
	}

	return arbre;
}