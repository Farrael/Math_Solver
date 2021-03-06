#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <sstream>

/* Internal dependencies */
#include "structure.h"
#include "utils.h"

using namespace std;

/**
 * Explore and display Arbre
 * arbre : Arbre to explore
 * depth : Indentation
 */
void explore(Arbre* arbre, int depth, char* indent, bool next){
    cout << indent << "+- Arbre : " << printArbre(arbre) << endl;

    if(next)
        indent = addChar(indent, "|  ");
    else
    	indent = addChar(indent, "   ");

    if(arbre->typ_terme != 0){
        if(arbre->typ_terme == 1)
            cout << indent << "+- Type : Variable" << endl;
        else if(arbre->typ_terme == 2)
            cout << indent << "+- Type : Constante" << endl;
        else if(arbre->typ_terme >= 30) {
            cout << indent << "+- Type : Fonction" << endl;
            Arguments* args = arbre->args;
            if(args->next != NULL)
                    indent = addChar(indent, "   ");
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
string printArbre(Arbre* arbre) {
    std::ostringstream output;
    if(arbre->typ_terme == 1)
        output << "x" << arbre->value;
    else if(arbre->typ_terme == 2)
        output << arbre->value;
    else if(arbre->typ_terme >= 30) {
        output << "f" << arbre->typ_terme - 30 << '(';
        Arguments* args = arbre->args;
        while(args != NULL){
            output << printArbre(args->value);
            args = args->next;
            if(args != NULL)
                output << ", ";
        }
        output << ")";
    }

    return output.str();
}

/**
 * Display the string representation of the Equation
 * equation : Equation to display
 */
void printEquation(Equation* equation) {
    Equation *temp = equation;
    cout << "{";
    while(temp != NULL){
        cout << printArbre(temp->args[0]) << "=" <<  printArbre(temp->args[1]);
        temp = temp->next;
        if(temp != NULL)
            cout << "; ";
    }
    cout << "}";
}

/**
 * Return an Arbre according to a string
 * input : String to read
 */
Arbre* get_structure(char* input){
	Arbre* arbre = new Arbre;
	int id = 0;

	if(input[0] == 'x') {
		toInteger(substr(input, 1, strlen(input)), id);
		arbre->typ_terme = 1;
		arbre->value = id;
	} else if(input[0] == 'f') {
		toInteger(substr(input, 1, strlen(input)), id);
		if(id < 0 || id > 3){
			arbre->typ_terme = 0;
			return arbre;
		}

		Arguments* head = NULL;
		Arguments* tail = NULL;
		arbre->typ_terme = 30 + id;

		// Get arguments by recursion
		// Return type {0} invalidate the entire recursion
		Array* arguments = cut(input, bracket, ',', 1);
        while(arguments != NULL){
        	Arbre *recu = get_structure(arguments->value);
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

        	arguments = arguments->next;
        }

        arbre->args = head;
	} else {
		toInteger(input, id);

		if(id == 0)
			arbre->typ_terme = 0;
		else {
		arbre->typ_terme = 2;
		arbre->value = id;
		}
	}

	return arbre;
}

/**
 * Add element to equation (end)
 * equation : Equation to modfie
 * arg1/2 : Arguments of equation
 */
Equation* addToEquation(Equation *equation, Arbre *arg1, Arbre *arg2){
	Equation *temp = new Equation;
	temp->args[0] = arg1;
	temp->args[1] = arg2;
	temp->next = NULL;

	if(equation != NULL) {
		Equation *loop = equation;
		while(loop->next != NULL) {
			loop = loop->next;
		}

		loop->next = temp;
	} else {
		equation = temp;
	}

	return equation;
}

/**
 * Add element to arguments
 * argument : Arguments to modifie
 * arbre : arbre to add
 * index : Index to place
 */
Arguments* addToArguments(Arguments *arguments, Arbre *arbre, int index){
	if(arguments == NULL){
		arguments = new Arguments;
		arguments->next = NULL;
		arguments->value = NULL;
	}

	Arguments *temp = new Arguments;
	temp->value = arbre;
	temp->next = NULL;

	if(index > 1) {
		Arguments *result = getArgumentsAtIndex(arguments, index - 1);
		if(result->next != NULL && result->next->next != NULL)
			temp->next = result->next->next;

		result->next = temp;
	} else {
		temp->next = arguments->next;
		free(arguments);
		arguments = temp;
	}

	return arguments;
}

/**
 * Return the arguments at index
 */
Arguments* getArgumentsAtIndex(Arguments *arguments, int index){
	Arguments *loop = arguments;

	int i = 1;
	if(index > 1) {
		while(i++ < index){
			if(loop->next == NULL){
				Arguments* next = new Arguments;
				next->next = NULL;
				next->value = NULL;
				loop->next = next;
			}

			loop = loop->next;
		}
	}

	return loop;
}

/**
 * Resolve the equation
 */
Arguments* resolve(Equation *equation){
	Equation *temp = equation;
	Arguments *args = NULL;

	while(temp != NULL) {
		// If S a variable{1}
		if(temp->args[0]->typ_terme == 1) {
			// If S and T a variables {1}
			if(temp->args[1]->typ_terme == 1) {
				// If S and T the same variable
				if(temp->args[0]->value == temp->args[1]->value) {
					// Nothing...

				// If S and T not the same variable
				} else {
					// If S < T
					if(temp->args[0]->value < temp->args[1]->value) {
						// If variable already defined
						Arguments *result = getArgumentsAtIndex(args, temp->args[0]->value);
						if(result->value != NULL)
							args = addToArguments(args, temp->args[0], temp->args[1]->value);
						else
							args = addToArguments(args, temp->args[1], temp->args[0]->value);

					// If S > T
					} else {
						temp = addToEquation(temp, temp->args[1], temp->args[0]);
					}
				}
			// If T is a constante {2}
			} else if(temp->args[1]->typ_terme == 2) {
				args = addToArguments(args, temp->args[1], temp->args[0]->value);

			// If T is a function {30+}
			} else if(temp->args[1]->typ_terme >= 30) {
				if(isArgumentOf(temp->args[0], temp->args[1]))
					return NULL;

				args = addToArguments(args, temp->args[1], temp->args[0]->value);
			}


		// If S is not a variable /{1} but T is a variable {1}
		} else if(temp->args[0]->typ_terme != 1 && temp->args[1]->typ_terme == 1) {
			temp = addToEquation(temp, temp->args[1], temp->args[0]);

		// If T and S not a variables
		} else {
			// If T and S are constante
			if(temp->args[0]->typ_terme == 2 && temp->args[1]->typ_terme == 2
				 && temp->args[0]->value == temp->args[1]->value){
					// Nothing...

			// If T and S are the same function
			} else if(temp->args[0]->typ_terme >= 30 
				 && temp->args[0]->typ_terme == temp->args[1]->typ_terme){

				Arguments* f1 = temp->args[0]->args;
				Arguments* f2 = temp->args[1]->args;
			    while(f1 != NULL){
			    	if(f2 == NULL)
			    		return NULL;

			        temp = addToEquation(temp, f1->value, f2->value);
			        f1 = f1->next;
			        f2 = f2->next;
			    }

			// Else, no solution
			} else {
				return NULL;
			}
		}

		temp = temp->next;
	}

	return args;
}

/**
 * Simplify equation (need recursive)
 */
Arguments* simplify(Arguments *arguments){
	Arguments *temp = arguments;
	Arguments *result;
	Arguments *args;
	bool update = false;

	while(temp != NULL){
		if(temp->value != NULL){
			if(temp->value->typ_terme == 1){
				result = getArgumentsAtIndex(arguments, temp->value->value);
				if(result->value != NULL){
					temp->value = result->value;
					update = true;
				}
			} else if(temp->value->typ_terme > 30){
				args = temp->value->args;
				while(args != NULL){
					if(args->value != NULL && args->value->typ_terme == 1){
						result = getArgumentsAtIndex(arguments, args->value->value);
						if(result->value != NULL){
							args->value = result->value;
							update = true;
						}
					}
					args = args->next;
				} 
			}
		}

		temp = temp->next;
	}

	return update ? simplify(arguments) : arguments;
}

/**
 * Return if a variable is an arguments of a function
 * variable : Arbre{1} to search
 * function : Arbre{30+} to explore
 */
bool isArgumentOf(Arbre *variable, Arbre *function){
	if(function->typ_terme < 30)
		return false;

    Arguments* args = function->args;
    while(args != NULL){
        if(args->value->typ_terme == 1 && variable->value == args->value->value)
        	return true;
        else if(args->value->typ_terme >= 30 && isArgumentOf(variable, args->value))
        	return true;
        args = args->next;
    }

    return false;
}

/**
 * Free systems
 */
 void freeSystems(Equation* equation){
    while(equation){
        if(equation->args[0])
            freeArbre(equation->args[0]);
        if(equation->args[1])
            freeArbre(equation->args[1]);

        Equation* temp = equation->next;
        free(equation);
        equation = temp;
    }
 }

/**
 * Free Arbre
 */
 void freeArbre(Arbre* arbre){
    if(arbre){
        if(arbre->typ_terme < 30)
            free(arbre);
        else if(arbre->typ_terme < 34){
            Arguments* args = arbre->args;
            while(args != NULL){
                if(args->value)
                    freeArbre(args->value);
                Arguments* temp = args->next;
                free(args);
                args = temp;

            }

            free(arbre);
        }
    }
 }