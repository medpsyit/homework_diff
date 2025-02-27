#ifndef INTERFACE_H
#define INTERFACE_H

#include "client.h"
#include "number.h"

void db_interface(pqxx::connection& c);

#endif /* INTERFACE_H */