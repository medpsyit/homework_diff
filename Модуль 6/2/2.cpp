#include "tables.h"

int main() {
	try {
		std::string connectionString =
			"host=localhost "
			"port=5432 "
			"dbname=lesson2 "
			"user=postgres "
			"password=100895";
		
		auto postgres = std::make_unique<Wt::Dbo::backend::Postgres>(connectionString);
		Wt::Dbo::Session session;
		session.setConnection(std::move(postgres));
		session.mapClass<Publisher>("Publisher");
		session.mapClass<Book>("Book");
		session.mapClass<Shop>("Shop");
		session.mapClass<Stock>("Stock");
		session.mapClass<Sale>("Sale");
		session.createTables();

		fill_tables(session);

		publisher_info(session);
	}
	catch (const Wt::Dbo::Exception& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}