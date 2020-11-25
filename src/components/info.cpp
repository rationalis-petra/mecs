#include <string>

#include "components/info.hpp"

using std::string;

Info::Info() {}
Info::Info(string _name, Tag _tags) : name(_name), tags(_tags) {}

Info::~Info(){}
