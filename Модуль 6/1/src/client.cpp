#include "../include/client.h"

void Client::create_table_client(pqxx::work& tx, pqxx::connection& c) {
	tx.exec("CREATE TABLE IF NOT EXISTS Client ("
		"id SERIAL PRIMARY KEY, "
		"first_name TEXT NOT NULL, "
		"last_name TEXT NOT NULL, "
		"email TEXT NOT NULL UNIQUE)");
	std::cout << "The table (Client) has been successfully created!" << std::endl;

	c.prepare("insert_client", "INSERT INTO Client(first_name, last_name, email) VALUES($1, $2, $3)");
}

void Client::insert_client(pqxx::work& tx) {
	std::string first_name{}, last_name{}, email{}, answer{ "none" };
	std::cout << "Enter the first name: ";
	std::cin >> first_name;
	std::cout << "Enter the last name: ";
	std::cin >> last_name;
	std::cout << "Enter the email: ";
	std::cin >> email;
	tx.exec_prepared("insert_client", first_name, last_name, email);

	do {
		std::cout << "Would you like to add a number? Y/N: ";
		std::cin >> answer;
		if (answer == "Y") {
			std::string number{}, client_id{};
			client_id = tx.query_value<std::string>("SELECT id FROM Client WHERE first_name = \'"
				+ first_name + "\' AND last_name = \'"
				+ last_name + "\' AND email = \'"
				+ email + "\'");
			std::cout << "Enter the number: ";
			std::cin >> number;
			tx.exec_prepared("insert_number", number, client_id);
		}
		else if (answer == "N") {
			std::cout << "Okay! You can add a number later." << std::endl;
		}
		else {
			std::cout << "Incorrect command! Try again." << std::endl;
		}
	} while (answer != "N");
	std::cout << "The Client has been successfully added!" << std::endl;
}

void Client::update_client(pqxx::work& tx) {
	std::string id{};
	int answer{};
	std::cout << "Enter the client ID of which you want to change: ";
	std::cin >> id;
	do {
		std::cout << "Choose the action:\n"
			"1. Update the first name;\n"
			"2. Update the last name;\n"
			"3. Update the email;\n"
			"4. Update all client data;\n"
			"5. Update one of the numbers;\n"
			"0. Exit.\n";
		std::cin >> answer;
		switch (answer) {
		case 1: {
			std::string ans{};
			std::cout << "Enter new first name: ";
			std::cin >> ans;
			tx.exec("UPDATE Client SET first_name=\'" + ans + "\' WHERE id=" + id);
			std::cout << "The first name is changed!" << std::endl;
			break;
		}
		case 2: {
			std::string ans{};
			std::cout << "Enter new last name: ";
			std::cin >> ans;
			tx.exec("UPDATE Client SET last_name=\'" + ans + "\' WHERE id=" + id);
			std::cout << "The last name is changed!" << std::endl;
			break;
		}
		case 3: {
			std::string ans{};
			std::cout << "Enter new email: ";
			std::cin >> ans;
			tx.exec("UPDATE Client SET email=\'" + ans + "\' WHERE id=" + id);
			std::cout << "The email is changed!" << std::endl;
			break;
		}
		case 4: {
			std::string f_n{}, l_n{}, email{};
			std::cout << "Enter new first name: ";
			std::cin >> f_n;
			std::cout << "Enter new last name: ";
			std::cin >> l_n;
			std::cout << "Enter new email: ";
			std::cin >> email;
			tx.exec("UPDATE Client SET first_name=\'" + f_n +
				"\', last_name=\'" + l_n +
				"\', email=\'" + email +
				"\' WHERE id = " + id);
			std::cout << "The client data is changed!" << std::endl;
			break;
		}
		case 5: {
			pqxx::result check = tx.exec("SELECT client_id FROM Number WHERE client_id = " + id);
			if (check.empty()) {
				std::cout << "This client has no number yet!" << std::endl;
			}
			else {
				std::string num_id{}, num{};
				std::cout << "Select the number ID you want to update:\n";
				for (auto [id, number] : tx.query<std::string, std::string>("SELECT id, number FROM Number WHERE client_id = " + id)) {
					std::cout << "ID: " << id << ". NUMBER: " << number << std::endl;
				}
				std::cin >> num_id;
				std::cout << "Enter new number: ";
				std::cin >> num;
				tx.exec("UPDATE Number SET number=\'" + num + "\' WHERE id=" + id);
				std::cout << "The number is changed!" << std::endl;
			}
			break;
		}
		case 0:
			break;
		default: {
			std::cout << "There is no such command!" << std::endl;
			break;
		}
		}
	} while (answer != 0);
}

void Client::delete_client(pqxx::work& tx) {
	std::string client_id{ -1 };
	pqxx::result check_client{};
	do {
		std::cout << "Enter the client ID who needs to be removed (\"0\" for cancel): ";
		std::cin >> client_id;
		check_client = tx.exec("SELECT id FROM Client WHERE id = " + client_id);
		if (check_client.empty() && client_id != "0") {
			std::cout << "There is no client with such ID! Try again." << std::endl;
		}
	} while (check_client.empty() && client_id != "0");
	if (client_id != "0") {
		tx.exec("DELETE FROM Number WHERE client_id = " + client_id);
		tx.exec("DELETE FROM Client WHERE id=" + client_id);
		std::cout << "The client is deleted!" << std::endl;
	}
}

void Client::search_client(pqxx::work& tx) {
	std::string answer{ 0 };
	do {
		std::cout << "Choose the action : \n"
			"1. Search by ID;\n"
			"2. Search according to the data (first name, last name, email, number).\n";
		std::cin >> answer;
		if (answer != "1" && answer != "2") {
			std::cout << "Incorrect command! Try again." << std::endl;
		}
	} while (answer != "1" && answer != "2");
	if (answer == "1") {
		std::cout << "Enter the client ID: ";
		std::cin >> answer;
		pqxx::result check_client = tx.exec("SELECT id FROM Client WHERE id = " + answer);
		if (check_client.empty()) {
			std::cout << "There is no client with such ID!" << std::endl;
		}
		else {
			auto data_client = tx.query<std::string, std::string, std::string>(
				"SELECT first_name, last_name, email FROM Client WHERE id = " + answer);
			pqxx::result check_client_number = tx.exec("SELECT id FROM Number WHERE client_id = " + answer);
			for (auto [first_name, last_name, email] : data_client)
			{
				std::cout << "FIRST NAME: " << first_name
					<< "\nLAST NAME: " << last_name
					<< "\nE-MAIL: " << email << std::endl;
				if (check_client_number.empty()) {
					std::cout << "NUMBER: NONE." << std::endl;
				}
				else {
					int c{ 1 };
					auto data_client_number = tx.query<std::string>("SELECT number FROM Number WHERE client_id = " + answer);
					for (auto [number] : data_client_number) {
						std::cout << "NUMBER " << c << ": " << number << std::endl;
						c++;
					}
				}
			}
		}
	}
	else if (answer == "2") {
		std::cout << "Enter the client info(first name, last name, email, number): ";
		std::cin >> answer;
		pqxx::result check_client = tx.exec("SELECT Client.id FROM Client LEFT JOIN Number ON Client.id = Number.client_id "
			"WHERE Client.first_name = \'" + answer +
			"\' OR Client.last_name = \'" + answer +
			"\' OR Client.email = \'" + answer +
			"\' OR Number.number = \'" + answer + "\'");
		if (check_client.empty()) {
			std::cout << "There is no client with such info!" << std::endl;
		}
		else {
			auto data_client = tx.query<std::string, std::string, std::string, std::string>(
				"SELECT DISTINCT Client.id, Client.first_name, Client.last_name, Client.email FROM Client LEFT JOIN Number ON Client.id = Number.client_id "
				"WHERE Client.first_name = \'" + answer +
				"\' OR Client.last_name = \'" + answer +
				"\' OR Client.email = \'" + answer +
				"\' OR Number.number = \'" + answer + "\'");
			for (auto [id, first_name, last_name, email] : data_client)
			{
				std::cout << "FIRST NAME: " << first_name
					<< "\nLAST NAME: " << last_name
					<< "\nE-MAIL: " << email << std::endl;
				pqxx::result check_client_number = tx.exec("SELECT Number.id FROM Client JOIN Number ON Client.id = Number.client_id "
					"WHERE Client.id = " + id);
				if (check_client_number.empty()) {
					std::cout << "NUMBER: NONE." << std::endl;
				}
				else {
					int c{ 1 };
					auto data_client_number = tx.query<std::string>("SELECT Number.number FROM Client JOIN Number ON Client.id = Number.client_id "
						"WHERE Client.id = " + id);
					for (auto [number] : data_client_number) {
						std::cout << "NUMBER " << c << ": " << number << std::endl;
						c++;
					}
				}
			}
		}
	}
}