/*
utils.h
-----

Role : Global structures used to solve system
*/

#ifndef H_VARIABLES
#define H_VARIABLES

	struct Arguments;

	/**
	 * Equation structure
	 */
	struct Arbre {
		int typ_terme;
		int value;
		Arguments *args;
	};

	/**
	 * Equation structure
	 */
	struct Equation {
		Arbre *args[2];
		Equation *next;
	};

	/**
	 * Arguments structure
	 */
	struct Arguments {
		Arbre *value;
		Arguments *next;
	};

	void explore(Arbre*, int, char*, bool);
    void printArbre(Arbre*);
    void printEquation(Equation*);

    Arbre* get_structure(char*);

	Equation* addToEquation(Equation*, Arbre*, Arbre*);

	Arguments* addToArguments(Arguments*, Arbre*, int);
	Arguments* getArgumentsAtIndex(Arguments*, int);
	Arguments* resolve(Equation*);
	Arguments* simplify(Arguments*);

	bool isArgumentOf(Arbre*, Arbre*);

	void freeSystems(Equation*);
    void freeArbre(Arbre*);

#endif