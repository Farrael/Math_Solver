#include <iostream>
#include <string>
#include <vector>

/* Internal dependencies */
#include "solver.h"
#include "utils.h"

using namespace std;

int main() {
    string input = "";
    char pattern[2] = {'[',']'};

    // Display logo
    logo();

    // Ask for equation
    printf("\nEquation a resoudre : ");
    getline(cin, input);

    // Split usage ( exemple )
    vector<string> try1 = split(input, "=");
	for(size_t i = 0; i < try1.size(); ++i)
        cout << try1[i] << endl;

    // Regex usage ( exemple )
    vector<string> try2 = regex(input, pattern, 1);
	for(size_t i = 0; i < try2.size(); ++i)
        cout << try2[i] << endl;

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