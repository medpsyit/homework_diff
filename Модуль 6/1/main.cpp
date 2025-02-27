#include "include/interface.h"
#include <Windows.h>

#pragma execution_character_set("utf-8");

int main() {
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	try {
		pqxx::connection c(
			"host=localhost " 
			"port=5432 " 
			"dbname=dbxx " 
			"user=postgres " 
			"password=100895"); 
		std::cout << "Connection OK\n";
		
		db_interface(c);
	}
	catch (std::exception &e) { 
		std::cout << e.what() << std::endl;
	}
	return 0;
}