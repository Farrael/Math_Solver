/*
utils.h
-----

Role : Utility function
*/

#ifndef H_UTILS
#define H_UTILS

	extern char hook[2];
	extern char bracket[2];

	/**
	 * List of String
	 */
	struct Array {
		char* value;
		Array* next;
	};

	void toInteger(char*, int&);
	int pow(int);

	char* addChar(char*, const char*);
	char* substr(char*, int, int);

    void trim(char*);
    Array* regex(char*, char*, int);
    Array* cut(char*, char*, char, int);

	Array* push_back(Array*, char*);
    int size(Array*);

#endif