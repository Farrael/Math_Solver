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
		std::string value;
		Array* next;
	};

	bool toInteger(std::string &s, int &n);
	bool isInteger(std::string&);
    std::string trim(std::string&);
    Array* split(std::string, std::string);
    Array* regex(std::string, char*, int);
    Array* cut(std::string, char*, char, int);

	Array* push_back(Array*, std::string);
    int size(Array*);

#endif