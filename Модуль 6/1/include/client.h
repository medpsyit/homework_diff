#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <pqxx/pqxx>

class Client {
public:
	void create_table_client(pqxx::work& tx, pqxx::connection& c);

	void insert_client(pqxx::work& tx);

	void update_client(pqxx::work& tx);

	void delete_client(pqxx::work& tx);

	void search_client(pqxx::work& tx);
};


#endif /* CLIENT_H */