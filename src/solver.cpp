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
            cout << indent << "+- Equation : " << equations[j] << endl;
            if(j < (equations.size()-1))
                indent += "|  ";
            else
                indent += "   ";

            vector<string> arbres = cut(equations[j], bracket, ',', 0);
            for(size_t k = 0; k < arbres.size(); ++k) {
                Arbre *arbre = get_structure(arbres[k]);
                explore(arbre, 0, indent, k < (arbres.size()-1));
            }

            indent.erase(indent.end() - 3, indent.end());
        }
        cout << indent << endl;
        indent.erase(indent.end() - 3, indent.end());
    }

    return 0;
}

/**
 * Explore and display Arbre
 * arbre : Arbre to explore
 * depth : Indentation
 */
void explore(Arbre* arbre, int depth, string indent, bool next){
    cout << indent << "+- Arbre : ";
    toString(arbre);
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
        cout << indent << "+- Type : Invalide" << endl;
}

/**
 * Display the string representation of Arbre
 * arbre : Arbre to display
 */
void toString(Arbre* arbre) {
    if(arbre->typ_terme == 1)
        cout << "x" << arbre->value;
    else if(arbre->typ_terme == 2)
        cout << arbre->value;
    else if(arbre->typ_terme >= 30) {
        cout << "f" << arbre->typ_terme - 30 << '(';
        Arguments* args = arbre->args;
        while(args != NULL){
            toString(args->value);
            args = args->next;
            if(args != NULL)
                cout << ", ";
        }
        cout << ")";
    }
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