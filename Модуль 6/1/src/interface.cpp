#include "../include/interface.h"

void db_interface(pqxx::connection& c) {
	pqxx::work tx_{ c };
	Client client;
	Number number;

	client.create_table_client(tx_, c);
	number.create_table_num(tx_, c);

	tx_.commit();
	int answer{ -1 };
	do {
		std::cout << "Choose the option:\n"
			"1. Insert a client;\n"
			"2. Insert a number for an existing client;\n"
			"3. Update a client;\n"
			"4. Delete a client;\n"
			"5. Delete a number of an existing client;\n"
			"6. Search a client.\n"
			"0. Exit." << std::endl;
		std::cin >> answer;
		if (answer != 0) {
			switch (answer) {
			case 1: {
				pqxx::work tx{ c };
				client.insert_client(tx);
				tx.commit();
				break;
			}
			case 2: {
				pqxx::work tx{ c };
				number.insert_number(tx);
				tx.commit();
				break;
			}
			case 3: {
				pqxx::work tx{ c };
				client.update_client(tx);
				tx.commit();
				break;
			}
			case 4: {
				pqxx::work tx{ c };
				client.delete_client(tx);
				tx.commit();
				break;
			}
			case 5: {
				pqxx::work tx{ c };
				number.delete_number(tx);
				tx.commit();
				break;
			}
			case 6: {
				pqxx::work tx{ c };
				client.search_client(tx);
				tx.commit();
				break;
			}
			default: {
				std::cout << "There is no such command!" << std::endl;
				break;
			}
			}
		}
	} while (answer != 0);
	std::cout << "Good bye!" << std::endl;
}