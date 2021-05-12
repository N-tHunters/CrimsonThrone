#include "abstractListElement.hpp"

AbstractListElement::AbstractListElement() {}
std::vector<std::string>* AbstractListElement::getValues() {
	std::vector<std::string>* values = new std::vector<std::string>();
	values->push_back("E blya, kakovo huya");
	values->push_back("NULL");

	return values;
}
