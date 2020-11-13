#ifndef ABSTRACTLISTELEMENT_H
#define ABSTRACTLISTELEMENT_H

#include <vector>
#include <string>

class AbstractListElement {
	
public:
	AbstractListElement();
	std::vector<std::string>* getHeaders();
	std::vector<std::string>* getValues();
};

#endif