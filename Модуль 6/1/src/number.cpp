#include "../include/number.h"

void Number::create_table_num(pqxx::work& tx, pqxx::connection& c) {
	tx.exec("CREATE TABLE IF NOT EXISTS Number ("
		"id SERIAL PRIMARY KEY, "
		"number TEXT NOT NULL UNIQUE, "
		"client_id INTEGER REFERENCES Client(id))");
	std::cout << "The table (Number) has been successfully created!" << std::endl;

	c.prepare("insert_number", "INSERT INTO Number(number, client_id) VALUES($1, $2)");
}

void Number::insert_number(pqxx::work& tx) {
	std::string number{}, client_id{};
	std::cout << "Enter the client ID who will add a number: ";
	std::cin >> client_id;
	std::cout << "Enter the number: ";
	std::cin >> number;
	tx.exec_prepared("insert_number", number, client_id);
	std::cout << "The Number has been successfully added!" << std::endl;
}

void Number::delete_number(pqxx::work& tx) {
	std::string client_id{ -1 };
	pqxx::result check_client{};
	do {
		std::cout << "Enter the client ID who will delete a number(\"0\" for cancel): ";
		std::cin >> client_id;
		check_client = tx.exec("SELECT id FROM Client WHERE id = " + client_id);
		if (check_client.empty() && client_id != "0") {
			std::cout << "There is no client with such ID! Try again." << std::endl;
		}
	} while (check_client.empty() && client_id != "0");
	if (client_id != "0") {
		std::string num_id{};
		pqxx::result check_number{};
		do {
			std::cout << "Select the number ID you want to delete:\n";
			for (auto [id, number] : tx.query<std::string, std::string>("SELECT id, number FROM Number WHERE client_id = " + client_id)) {
				std::cout << "ID: " << id << ". NUMBER: " << number << std::endl;
			}
			std::cin >> num_id;
			check_number = tx.exec("SELECT id FROM Number WHERE id = " + num_id);
			if (check_number.empty()) {
				std::cout << "There is no number with such ID! Try again." << std::endl;
			}
		} while (check_number.empty());
		tx.exec("DELETE FROM Number WHERE id=" + num_id);
		std::cout << "The number is deleted!" << std::endl;
	}
}