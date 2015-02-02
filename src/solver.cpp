#include <iostream>
#include <string>

/* Internal dependencies */
#include "structure.h"
#include "solver.h"
#include "utils.h"

using namespace std;

int main() {
    string input = "";
    string indent = "   ";

    // Display logo
    logo();

    // Ask for equation
    cout << "\nEnter a system to solve : ";
    getline(cin, input);

    cout << endl;

    Equation *head;
    Equation *tail;

    // Explore the system
    Array *systems = regex(input, hook, 1);
	while(systems != NULL) {
        cout << indent << "+- System : " << systems->value << endl;
        indent += "   ";

        // Reset if old value
        head = tail = NULL;

        Array *equations = regex(systems->value, hook, 1);
        while(equations != NULL) {
            Equation *equation = new Equation;
            equation->next = NULL;
            
            cout << indent << "+- Equation : " << equations->value << endl;
            if(equations->next != NULL)
                indent += "|  ";
            else
                indent += "   ";

            Array *arbres = cut(equations->value, bracket, ',', 0);
            int i = size(arbres);
            if(i != 2) {
                if(i < 2)
                    error(" ^ Missing arguments (Two expected)", indent.size());
                else
                    error(" ^ Too many arguments (Two expected)", indent.size());
                return 0;
            }

            bool valid = true;
            int j = 0;
            while(arbres != NULL) {
                Arbre *arbre = get_structure(arbres->value);
                equation->args[j++] = arbre;
                if(arbre->typ_terme == 0)
                    valid = false;
                explore(arbre, 0, indent, arbres->next != NULL);
                arbres = arbres->next;
            }

            // Ignore if not a valid equation (f > 3 for exemple)
            if(valid) {
                if(tail != NULL)
                    tail->next = equation;

                tail = equation;

                if(head == NULL)
                    head = equation;
            }

            indent.erase(indent.end() - 3, indent.end());
            equations = equations->next;
        }
        cout << indent << endl;
        indent.erase(indent.end() - 3, indent.end());


        ///////////////////
        // Solve
        /////

        cout << "Equation : +- ";
        printEquation(head);
        cout << endl;

        // Resolve the system
        Arguments *result = resolve(head);

        cout << "Solution : +- ";
        if(result == NULL)
            cout << "The system has no solution /!\\" << endl;
        else {
            int i = 1;
            Arguments *temp = result;
            cout << "{";
            while(temp != NULL) {
                if(temp->value != NULL){
                    cout << "x" << i++ << "=";
                    printArbre(temp->value);
                }
                temp = temp->next;
                if(temp != NULL)
                    cout << "; ";
            }
            cout << "}" << endl;

            // Simplifie the result
            temp = simplify(result);
            i = 1;

            cout << "           +- " << "{";
            while(temp != NULL) {
                if(temp->value != NULL){
                    cout << "x" << i++ << "=";
                    printArbre(temp->value);
                }
                temp = temp->next;
                if(temp != NULL)
                    cout << "; ";
            }
            cout << "}" << endl << endl;
        }

        systems = systems->next;
    }

    return 0;
}

/**
 * Display error message
 */
void error(string message, int space) {
    string spacer(space, ' ');
    cout << spacer << message << endl;
}

/**
 * Display main logo
 */
void logo(){
	cout << "#----------------------------------------------#      \n";
	cout << "  __  __      _   _      ___      _                   \n";
	cout << " |  \\/  |__ _| |_| |_   / __| ___| |_ _____ _ _      \n";
	cout << " | |\\/| / _` |  _| ' \\  \\__ \\/ _ \\ \\ V / -_) '_|\n";
	cout << " |_|  |_\\__,_|\\__|_||_|_|___/\\___/_|\\_/\\___|_|   \n";
	cout << "                     |___|                            \n";
	cout << "#----------------------------------------------#      \n";
}