#ifndef ABSTRACTLISTELEMENT_H
#define ABSTRACTLISTELEMENT_H

#include <vector>
#include <string>

class AbstractListElement {

public:
	AbstractListElement();
	virtual std::vector<std::string>* getValues();
};

#endif