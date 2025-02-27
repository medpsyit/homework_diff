#include "tables.h"

void fill_tables(Wt::Dbo::Session& session) {
	Wt::Dbo::Transaction transaction{ session };

	//Publishers
	std::unique_ptr<Publisher> publisher{ new Publisher() };
	publisher->name = "Macmillan";
	Wt::Dbo::ptr<Publisher> publisherPtr = session.add(std::move(publisher));

	std::unique_ptr<Publisher> publisher2{ new Publisher() };
	publisher2->name = "Penguin Random House";
	Wt::Dbo::ptr<Publisher> publisherPtr2 = session.add(std::move(publisher2));

	std::unique_ptr<Publisher> publisher3{ new Publisher() };
	publisher3->name = "Harper Collins";
	Wt::Dbo::ptr<Publisher> publisherPtr3 = session.add(std::move(publisher3));

	//Books
	//1st publisher
	Wt::Dbo::ptr<Publisher> first = session.find<Publisher>().where("name = ?").bind("Macmillan");

	Wt::Dbo::ptr<Book> book = session.add(std::unique_ptr<Book>{new Book()});
	book.modify()->title = "Look again";
	book.modify()->publisher = first;

	Wt::Dbo::ptr<Book> book2 = session.add(std::unique_ptr<Book>{new Book()});
	book2.modify()->title = "The Way Nature Works";
	book2.modify()->publisher = first;

	Wt::Dbo::ptr<Book> book3 = session.add(std::unique_ptr<Book>{new Book()});
	book3.modify()->title = "School Dictionary";
	book3.modify()->publisher = first;

	//2nd publisher
	Wt::Dbo::ptr<Publisher> second = session.find<Publisher>().where("name = ?").bind("Penguin Random House");

	Wt::Dbo::ptr<Book> book4 = session.add(std::unique_ptr<Book>{new Book()});
	book4.modify()->title = "The Great Gatsby";
	book4.modify()->publisher = second;

	Wt::Dbo::ptr<Book> book5 = session.add(std::unique_ptr<Book>{new Book()});
	book5.modify()->title = "Sword of Honour";
	book5.modify()->publisher = second;

	Wt::Dbo::ptr<Book> book6 = session.add(std::unique_ptr<Book>{new Book()});
	book6.modify()->title = "Botchan";
	book6.modify()->publisher = second;

	//3d publisher
	Wt::Dbo::ptr<Publisher> third = session.find<Publisher>().where("name = ?").bind("Harper Collins");

	Wt::Dbo::ptr<Book> book7 = session.add(std::unique_ptr<Book>{new Book()});
	book7.modify()->title = "The Alchemist";
	book7.modify()->publisher = third;

	Wt::Dbo::ptr<Book> book8 = session.add(std::unique_ptr<Book>{new Book()});
	book8.modify()->title = "Little Blue Truck Board Book";
	book8.modify()->publisher = third;

	Wt::Dbo::ptr<Book> book9 = session.add(std::unique_ptr<Book>{new Book()});
	book9.modify()->title = "Shatter Me";
	book9.modify()->publisher = third;

	//Shops
	std::unique_ptr<Shop> shop{ new Shop() };
	shop->name = "Bookmans";
	Wt::Dbo::ptr<Shop> shopPtr = session.add(std::move(shop));

	std::unique_ptr<Shop> shop2{ new Shop() };
	shop2->name = "Books-A-Million";
	Wt::Dbo::ptr<Shop> shopPtr2 = session.add(std::move(shop2));

	std::unique_ptr<Shop> shop3{ new Shop() };
	shop3->name = "Deseret Book";
	Wt::Dbo::ptr<Shop> shopPtr3 = session.add(std::move(shop3));

	std::unique_ptr<Shop> shop4{ new Shop() };
	shop4->name = "Half Price Books";
	Wt::Dbo::ptr<Shop> shopPtr4 = session.add(std::move(shop4));

	std::unique_ptr<Shop> shop5{ new Shop() };
	shop5->name = "Tattered Cover";
	Wt::Dbo::ptr<Shop> shopPtr5 = session.add(std::move(shop5));

	//Stocks
	//find books
	Wt::Dbo::ptr<Book> look_again = session.find<Book>().where("title = ?").bind("Look again");
	Wt::Dbo::ptr<Book> nature_works = session.find<Book>().where("title = ?").bind("The Way Nature Works");
	Wt::Dbo::ptr<Book> dictionary = session.find<Book>().where("title = ?").bind("School Dictionary");
	Wt::Dbo::ptr<Book> gatsby = session.find<Book>().where("title = ?").bind("The Great Gatsby");
	Wt::Dbo::ptr<Book> honour = session.find<Book>().where("title = ?").bind("Sword of Honour");
	Wt::Dbo::ptr<Book> botchan = session.find<Book>().where("title = ?").bind("Botchan");
	Wt::Dbo::ptr<Book> alchemist = session.find<Book>().where("title = ?").bind("The Alchemist");
	Wt::Dbo::ptr<Book> blue_truck = session.find<Book>().where("title = ?").bind("Little Blue Truck Board Book");
	Wt::Dbo::ptr<Book> shatter_me = session.find<Book>().where("title = ?").bind("Shatter Me");
	//find shops
	Wt::Dbo::ptr<Shop> bookmans = session.find<Shop>().where("name = ?").bind("Bookmans");
	Wt::Dbo::ptr<Shop> books_million = session.find<Shop>().where("name = ?").bind("Books-A-Million");
	Wt::Dbo::ptr<Shop> deseret = session.find<Shop>().where("name = ?").bind("Deseret Book");
	Wt::Dbo::ptr<Shop> half_price = session.find<Shop>().where("name = ?").bind("Half Price Books");
	Wt::Dbo::ptr<Shop> tattered = session.find<Shop>().where("name = ?").bind("Tattered Cover");
	//fill stocks
	Wt::Dbo::ptr<Stock> stock1 = session.add(std::unique_ptr<Stock>{new Stock()});
	stock1.modify()->book = look_again;
	stock1.modify()->shop = deseret;
	stock1.modify()->count = 10;

	Wt::Dbo::ptr<Stock> stock2 = session.add(std::unique_ptr<Stock>{new Stock()});
	stock2.modify()->book = nature_works;
	stock2.modify()->shop = bookmans;
	stock2.modify()->count = 5;

	Wt::Dbo::ptr<Stock> stock3 = session.add(std::unique_ptr<Stock>{new Stock()});
	stock3.modify()->book = dictionary;
	stock3.modify()->shop = books_million;
	stock3.modify()->count = 7;

	Wt::Dbo::ptr<Stock> stock4 = session.add(std::unique_ptr<Stock>{new Stock()});
	stock4.modify()->book = gatsby;
	stock4.modify()->shop = deseret;
	stock4.modify()->count = 3;

	Wt::Dbo::ptr<Stock> stock5 = session.add(std::unique_ptr<Stock>{new Stock()});
	stock5.modify()->book = honour;
	stock5.modify()->shop = bookmans;
	stock5.modify()->count = 9;

	Wt::Dbo::ptr<Stock> stock6 = session.add(std::unique_ptr<Stock>{new Stock()});
	stock6.modify()->book = botchan;
	stock6.modify()->shop = half_price;
	stock6.modify()->count = 3;

	Wt::Dbo::ptr<Stock> stock7 = session.add(std::unique_ptr<Stock>{new Stock()});
	stock7.modify()->book = alchemist;
	stock7.modify()->shop = books_million;
	stock7.modify()->count = 8;

	Wt::Dbo::ptr<Stock> stock8 = session.add(std::unique_ptr<Stock>{new Stock()});
	stock8.modify()->book = blue_truck;
	stock8.modify()->shop = bookmans;
	stock8.modify()->count = 13;

	Wt::Dbo::ptr<Stock> stock9 = session.add(std::unique_ptr<Stock>{new Stock()});
	stock9.modify()->book = shatter_me;
	stock9.modify()->shop = half_price;
	stock9.modify()->count = 4;

	Wt::Dbo::ptr<Stock> stock10 = session.add(std::unique_ptr<Stock>{new Stock()});
	stock10.modify()->book = gatsby;
	stock10.modify()->shop = tattered;
	stock10.modify()->count = 11;

	//Sales
	//find stocks
	Wt::Dbo::ptr<Stock> one = session.find<Stock>().where("id = 1");
	Wt::Dbo::ptr<Stock> two = session.find<Stock>().where("id = 2");
	Wt::Dbo::ptr<Stock> three = session.find<Stock>().where("id = 3");
	Wt::Dbo::ptr<Stock> four = session.find<Stock>().where("id = 4");
	Wt::Dbo::ptr<Stock> five = session.find<Stock>().where("id = 5");
	Wt::Dbo::ptr<Stock> six = session.find<Stock>().where("id = 6");
	/*Wt::Dbo::ptr<Stock> seven = session.find<Stock>().where("id = 7");
	Wt::Dbo::ptr<Stock> eight = session.find<Stock>().where("id = 8");
	Wt::Dbo::ptr<Stock> nine = session.find<Stock>().where("id = 9");
	Wt::Dbo::ptr<Stock> ten = session.find<Stock>().where("id = 10");*/
	//fill sales
	Wt::Dbo::ptr<Sale> sale1 = session.add(std::unique_ptr<Sale>{new Sale()});
	sale1.modify()->price = 10;
	sale1.modify()->date_sale = "01/01/15";
	sale1.modify()->stock = two;
	sale1.modify()->count = 2;

	Wt::Dbo::ptr<Sale> sale2 = session.add(std::unique_ptr<Sale>{new Sale()});
	sale2.modify()->price = 7;
	sale2.modify()->date_sale = "21/10/10";
	sale2.modify()->stock = four;
	sale2.modify()->count = 4;

	Wt::Dbo::ptr<Sale> sale3 = session.add(std::unique_ptr<Sale>{new Sale()});
	sale3.modify()->price = 15;
	sale3.modify()->date_sale = "25/07/20";
	sale3.modify()->stock = one;
	sale3.modify()->count = 5;

	Wt::Dbo::ptr<Sale> sale4 = session.add(std::unique_ptr<Sale>{new Sale()});
	sale4.modify()->price = 6;
	sale4.modify()->date_sale = "04/02/12";
	sale4.modify()->stock = five;
	sale4.modify()->count = 1;

	Wt::Dbo::ptr<Sale> sale5 = session.add(std::unique_ptr<Sale>{new Sale()});
	sale5.modify()->price = 9;
	sale5.modify()->date_sale = "15/03/09";
	sale5.modify()->stock = three;
	sale5.modify()->count = 3;

	Wt::Dbo::ptr<Sale> sale6 = session.add(std::unique_ptr<Sale>{new Sale()});
	sale6.modify()->price = 12;
	sale6.modify()->date_sale = "18/05/18";
	sale6.modify()->stock = six;
	sale6.modify()->count = 6;

	transaction.commit();
}

void publisher_info(Wt::Dbo::Session& session) {
	Wt::Dbo::Transaction transaction{ session };

	std::string publisher_search = "";
	std::cout << "Enter the ID of the publisher:\n";
	std::cin >> publisher_search;
	Wt::Dbo::ptr<Publisher> publisher = session.find<Publisher>().where("id=?").bind(publisher_search);
	std::cout << "Publisher: " << publisher->name << "\nBooks:\n";
	int c{ 1 };
	for (const auto book : publisher->books) {
		std::cout << c << ". " << book->title << '\n';
		c++;
	}
	std::cout << "Can be bought in stores:\n";
	for (const auto book : publisher->books) {
		for (const auto stock : book->stocks) {
			std::cout << "->" << stock->shop->name << std::endl;
		}
	}

	transaction.commit();
}