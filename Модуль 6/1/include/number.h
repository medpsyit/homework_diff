#ifndef NUMBER_H
#define NUMBER_H

#include <iostream>
#include <pqxx/pqxx>

class Number {
public:
	void create_table_num(pqxx::work& tx, pqxx::connection& c);

	void insert_number(pqxx::work& tx);

	void delete_number(pqxx::work& tx);
};

#endif /* NUMBER_H */