#include <iostream>
#include <string>
#include <vector>

/* Internal dependencies */
#include "structure.h"
#include "solver.h"
#include "utils.h"

using namespace std;

int main() {
    string input = "";
    string indent = "";

    // Display logo
    logo();

    // Ask for equation
    printf("\nEnter a system to solve : ");
    getline(cin, input);

    cout << endl;

    Equation *head = NULL;
    Equation *tail = NULL;

    // Explore the system
    vector<string> systems = regex(input, hook, 1);
	for(size_t i = 0; i < systems.size(); ++i) {
        cout << "+- System : " << systems[i] << endl;
        if(i < (systems.size()-1))
            indent += "|  ";
        else
            indent += "   ";

        vector<string> equations = regex(systems[i], hook, 1);
        for(size_t j = 0; j < equations.size(); ++j) {
            Equation *equation = new Equation;
            equation->next = NULL;
            
            cout << indent << "+- Equation : " << equations[j] << endl;
            if(j < (equations.size()-1))
                indent += "|  ";
            else
                indent += "   ";

            vector<string> arbres = cut(equations[j], bracket, ',', 0);
            if(arbres.size() != 2) {
                if(arbres.size() < 2)
                    error(" ^ Missing arguments (Two expected)", indent.size());
                else
                    error(" ^ Too many arguments (Two expected)", indent.size());
                return 0;
            }

            bool valid = true;
            for(size_t k = 0; k < 2; ++k) {
                Arbre *arbre = get_structure(arbres[k]);
                equation->args[k] = arbre;
                if(arbre->typ_terme == 0)
                    valid = false;
                explore(arbre, 0, indent, k < (arbres.size()-1));
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
        }
        cout << indent << endl;
        indent.erase(indent.end() - 3, indent.end());
    }

    // Display to human format
    cout << "System in literal form : " << endl << "   ";
    printEquation(head);
    cout << endl << endl;

    // Resolve the system
    Arguments *result = resolve(head);

    if(result == NULL)
        cout << "The system has no solution /!\\" << endl;
    else {
        int i = 1;
        cout << "{";
        while(result != NULL) {
            if(result->value != NULL){
                cout << "x" << i++ << "=";
                printArbre(result->value);
            }
            result = result->next;
            if(result != NULL)
                cout << "; ";
        }
        cout << "}";
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
	printf("#----------------------------------------------#      \n");
	printf("  __  __      _   _      ___      _                   \n");
	printf(" |  \\/  |__ _| |_| |_   / __| ___| |_ _____ _ _      \n");
	printf(" | |\\/| / _` |  _| ' \\  \\__ \\/ _ \\ \\ V / -_) '_|\n");
	printf(" |_|  |_\\__,_|\\__|_||_|_|___/\\___/_|\\_/\\___|_|   \n");
	printf("                     |___|                            \n");
	printf("#----------------------------------------------#      \n");
}