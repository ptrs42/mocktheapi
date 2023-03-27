#pragma once

#include <string>
#include "RequestResponse.h"

std::string Serialize(RequestResponse const & file);
RequestResponse Parse(std::string const & s);
