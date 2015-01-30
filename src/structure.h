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
		Arbre *arg1;
		Arbre *arg2;
		Equation *next;
	};

	/**
	 * Arguments structure
	 */
	struct Arguments {
		Arbre *value;
		Arguments *next;
	};

	Arbre* get_structure(std::string);

#endif