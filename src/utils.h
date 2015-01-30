/*
utils.h
-----

Role : Utility function
*/

#ifndef H_UTILS
#define H_UTILS

	extern char hook[2];
	extern char bracket[2];

    std::string trim(std::string&);
    std::vector<std::string> split(std::string, std::string);
    std::vector<std::string> regex(std::string, char*, int);
    std::vector<std::string> cut(std::string, char*, char);

#endif