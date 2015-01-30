#include <iostream>
#include <string>
#include <vector>

/* Internal dependencies */
#include "solver.h"
#include "utils.h"
#include "structure.h"

using namespace std;

int main() {
    string input = "";

    // Display logo
    logo();

    // Ask for equation
    printf("\nEnter a system to solve : ");
    getline(cin, input);

    // Regex usage ( exemple )
    vector<string> systems = regex(input, hook, 1);
    cout << endl << "Number of system found : " << systems.size() << endl << endl;
	for(size_t i = 0; i < systems.size(); ++i) {
        cout << "System : " << systems[i] << endl;

        vector<string> equations = regex(systems[i], hook, 1);
        for(size_t j = 0; j < equations.size(); ++j) {
            cout << "   Equation : " << equations[j] << endl;

            vector<string> arbres = cut(equations[j], bracket, ',');
            for(size_t k = 0; k < arbres.size(); ++k) {
                cout << "      Arbre : " << arbres[k] << endl;
            }
        }

        cout << endl;
    }

    return 0;
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