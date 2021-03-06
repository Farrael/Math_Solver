#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <fstream>

/* Internal dependencies */
#include "structure.h"
#include "solver.h"
#include "utils.h"

#define SIZE 100

using namespace std;

int main(int argc, char *argv[]) {
    char  input[SIZE] = "";
    char* indent = (char*) malloc(sizeof(char) * 4);
    int   test   = 0;

    // Display logo
    logo();

    // Detect arguments
    if(argc >= 2){
        for(int i = 1; i < argc; i++){
            if(strcmp("-t", argv[i]) == 0) {
                test = 1;
            } else {
                strcat(input, argv[i]);
            }
        }
    } else {
        // Ask for equation
        printf("\nEnter a system to solve : ");
        fgets(input, SIZE, stdin);
    }

    // Remove new line of stop if empty
    if(input[0] != '\n'){
        size_t len = strlen(input);
        if (len > 0 && input[len-1] == '\n')
            input[--len] = '\0';
    } else {
        cout << "No system..." << endl;
        return 0;
    }

    ///////////////////
    // Explore
    /////

    Equation *head;
    Equation *tail;

    Array *systems = cut(input, hook, ',', 0);
    if(systems == NULL){
        cout << input << endl;
        cout << " ^ No systems detected..." << endl;
        return 0;
    }

	while(systems != NULL) {
        cout << endl << "+- System : " << systems->value << endl;
        strcpy(indent, "    ");
        systems->value = substr(systems->value, 1, strlen(systems->value) - 2);

        // Reset if old value
        head = tail = NULL;
        bool br = false;

        Array *equations = cut(systems->value, hook, ',', 0);
        while(equations != NULL) {            
            cout << indent << "+- Equation : " << equations->value << endl;
            if(equations->next != NULL)
                indent = addChar(indent, "|  ");
            else
                indent = addChar(indent, "   ");

            equations->value = substr(equations->value, 1, strlen(equations->value) - 2);
            Equation *equation = new Equation;
            equation->next = NULL;

            Array *arbres = cut(equations->value, bracket, ',', 0);
            int i = size(arbres);
            if(i != 2) {
                if(i < 2)
                    error(" ^ Missing arguments (Two expected)", strlen(indent));
                else
                    error(" ^ Too many arguments (Two expected)", strlen(indent));
                
                br = true;
                break;
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

            indent = substr(indent, 0, strlen(indent) - 3);
            equations = equations->next;
        }

        if(br){
            systems = systems->next;
            continue;
        }

        cout << indent << endl;
        indent = substr(indent, 0, strlen(indent) - 3);


        ///////////////////
        // Solve
        /////

        cout << "Equation : +- ";
        printEquation(head);
        cout << endl;

        // Resolve the system
        Arguments *result = resolve(head);

        cout << "Solution : +- ";
        std::ostringstream output;
        if(result == NULL)
            output << "The system has no solution.";
        else {
            int i = 1;
            Arguments *temp = result;
            cout << "{";
            while(temp != NULL) {
                if(temp->value != NULL){
                    cout << "x" << i++ << "=";
                    cout << printArbre(temp->value);
                }
                temp = temp->next;
                if(temp != NULL)
                    cout << "; ";
            }
            cout << "}" << endl;

            // Simplifie the result
            temp = simplify(result);
            i = 1;

            output << "{";
            while(temp != NULL) {
                if(temp->value != NULL){
                    output << "x" << i++ << "=";
                    output << printArbre(temp->value);
                }
                temp = temp->next;
                if(temp != NULL)
                    output << "; ";
            }
            output << "}";
            cout << "           +- ";
        }
    
        cout << output.str() << endl << endl;

        if(test == 1) {
            ofstream file;
            file.open("result.txt");
            file << output.str();
            file.close();
        }

        freeSystems(head);
        systems = systems->next;
    }

    if(indent)
        free(indent);

    return 0;
}

/**
 * Display error message
 */
void error(const char* message, int space) {
    char spacer[space];
    for(int i = 0; i < space; i++)
        spacer[i] = ' ';
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