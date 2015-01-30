/*
utils.h
-----

Role : Global structures used to solve system
*/

#ifndef H_VARIABLES
#define H_VARIABLES

	/**
	 * Equation structure
	 */
	struct Equation {
		struct left;
		struct right;
	};

	/**
	 * Global structure
	 */
	struct Global {
		int type;
		struct value;
	};

	/**
	 * Constante structure (0)
	 */
	struct Constante { 
		int value;
	};

	/**
	 * Variable structure (1)
	 */
	struct Variable {
		std::string name;
		struct value;
	};

    /**
     * Function structure (2)
     */
    struct Function {
		std::string name;
		std::string arg1;
		std::string arg2;
		struct value;
	};

	Constante* to_constante(std::string);
    Variable* to_variable(std::string);
	Function* to_function(std::string);

#endif