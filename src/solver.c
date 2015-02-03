#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* Internal dependencies */
#include "structure.h"
#include "solver.h"
#include "utils.h"

#define SIZE 100

using namespace std;

int main() {
    char input[SIZE] = "";
    char* indent = (char*) malloc(sizeof(char) * 4);

    // Display logo
    logo();

    // Ask for equation
    printf("\nEnter a system to solve : ");
    fgets(input, SIZE, stdin);

    // Remove new line of stop if empty
    if(input != NULL){
        size_t len = strlen(input);
        if (len > 0 && input[len-1] == '\n')
            input[--len] = '\0';
    } else {
        printf("Empty systems...\n");
        return 0;
    }

    ///////////////////
    // Explore
    /////

    Equation *head;
    Equation *tail;

    Array *systems = cut(input, hook, ',', 0);
    if(systems == NULL){
        printf("%s\n", input);
        printf(" ^ No systems detected...\n");
        return 0;
    }

	while(systems != NULL) {
        printf("\n+- System : %s\n", systems->value);
        strcpy(indent, "    ");
        systems->value = substr(systems->value, 1, strlen(systems->value) - 2);

        // Default value
        head = tail = NULL;
        bool br = false;

        Array *equations = cut(systems->value, hook, ',', 0);
        while(equations != NULL) {
            printf("%s+- Equation : %s\n", indent, equations->value);
            if(equations->next != NULL)
                indent = addChar(indent, "|  ");
            else
                indent = addChar(indent, "   ");

            equations->value = substr(equations->value, 1, strlen(equations->value) - 2);
            Equation *equation = (Equation*) malloc(sizeof(Equation));
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

        printf("%s\n", indent);
        indent = substr(indent, 0, strlen(indent) - 3);

        ///////////////////
        // Solve
        /////

        printf("Equation : +- ");
        printEquation(head);
        printf("\n");

        // Resolve the system
        Arguments *result = resolve(head);

        printf("Solution : +- ");
        if(result == NULL)
            printf("The system has no solution.\n");
        else {
            int i = 1;
            Arguments *temp = result;
            printf("{");
            while(temp != NULL) {
                if(temp->value != NULL){
                    printf("x%d=", i++);
                    printArbre(temp->value);
                }
                temp = temp->next;
                if(temp != NULL)
                    printf("; ");
            }
            printf("}\n");

            // Simplifie the result
            temp = simplify(result);
            i = 1;

            printf("           +- {");
            while(temp != NULL) {
                if(temp->value != NULL){
                    printf("x%d=", i++);
                    printArbre(temp->value);
                }
                temp = temp->next;
                if(temp != NULL)
                    printf("; ");
            }
            printf("}\n\n");
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
    printf("%s%s\n", spacer, message);
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