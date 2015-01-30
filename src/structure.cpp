#include <iostream>
#include <string>
#include <vector>

/* Internal dependencies */
#include "structure.h"
#include "utils.h"

using namespace std;

/**
 * Explore and display Arbre
 * arbre : Arbre to explore
 * depth : Indentation
 */
void explore(Arbre* arbre, int depth, string indent, bool next){
    cout << indent << "+- Arbre : ";
    printArbre(arbre);
    cout << endl;

    if(next)
        indent += "|  ";
    else
        indent += "   ";

    if(arbre->typ_terme != 0){
        if(arbre->typ_terme == 1)
            cout << indent << "+- Type : Variable" << endl;
        else if(arbre->typ_terme == 2)
            cout << indent << "+- Type : Constante" << endl;
        else if(arbre->typ_terme >= 30) {
            cout << indent << "+- Type : Fonction" << endl;
            Arguments* args = arbre->args;
            if(args->next != NULL)
                    indent += "   ";
            while(args != NULL){
                explore(args->value, depth + 1, indent, args->next != NULL);
                args = args->next;
            }
        }
    } else 
        cout << indent << "+- Type : Invalide (Ignored)" << endl;
}

/**
 * Display the string representation of the Arbre
 * arbre : Arbre to display
 */
void printArbre(Arbre* arbre) {
    if(arbre->typ_terme == 1)
        cout << "x" << arbre->value;
    else if(arbre->typ_terme == 2)
        cout << arbre->value;
    else if(arbre->typ_terme >= 30) {
        cout << "f" << arbre->typ_terme - 30 << '(';
        Arguments* args = arbre->args;
        while(args != NULL){
            printArbre(args->value);
            args = args->next;
            if(args != NULL)
                cout << ", ";
        }
        cout << ")";
    }
}

/**
 * Display the string representation of the Equation
 * equation : Equation to display
 */
void printEquation(Equation* equation) {
    Equation *temp = equation;
    cout << "{";
    while(temp != NULL){
        printArbre(temp->args[0]);
        cout << "=";
        printArbre(temp->args[1]);
        temp = temp->next;
        if(temp != NULL)
            cout << "; ";
    }
    cout << "}";
}

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

Arguments* resolve(Equation *equation){
	return NULL;
}