#pragma once

#include<iostream>
#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Postgres.h>

class Book;
class Shop;
class Stock;
class Sale;
class Publisher {
public:
	std::string name = "";
	Wt::Dbo::collection< Wt::Dbo::ptr<Book> > books;

	template<class Action>
	void persist(Action& a)
	{
		Wt::Dbo::field(a, name, "name");
		Wt::Dbo::hasMany(a, books, Wt::Dbo::ManyToOne, "publisher");
	}
};

class Book {
public:
	std::string title = "";
	Wt::Dbo::ptr<Publisher> publisher;
	Wt::Dbo::collection< Wt::Dbo::ptr<Stock> > stocks;

	template<class Action>
	void persist(Action& a)
	{
		Wt::Dbo::field(a, title, "title");
		Wt::Dbo::belongsTo(a, publisher, "publisher");
		Wt::Dbo::hasMany(a, stocks, Wt::Dbo::ManyToOne, "book");
	}
};

class Shop {
public:
	std::string name = "";
	Wt::Dbo::collection< Wt::Dbo::ptr<Stock> > stocks;

	template<class Action>
	void persist(Action& a)
	{
		Wt::Dbo::field(a, name, "name");
		Wt::Dbo::hasMany(a, stocks, Wt::Dbo::ManyToOne, "shop");
	}
};

class Stock {
public:
	Wt::Dbo::ptr<Book> book;
	Wt::Dbo::ptr<Shop> shop;
	int count{ 0 };
	Wt::Dbo::collection< Wt::Dbo::ptr<Sale> > sales;

	template<class Action>
	void persist(Action& a)
	{
		Wt::Dbo::belongsTo(a, book, "book");
		Wt::Dbo::belongsTo(a, shop, "shop");
		Wt::Dbo::field(a, count, "count");
		Wt::Dbo::hasMany(a, sales, Wt::Dbo::ManyToOne, "stock");
	}
};

class Sale {
public:
	int price{ 0 };
	std::string date_sale = "";
	Wt::Dbo::ptr<Stock> stock;
	int count{ 0 };

	template<class Action>
	void persist(Action& a)
	{
		Wt::Dbo::field(a, price, "price");
		Wt::Dbo::field(a, date_sale, "date_sale");
		Wt::Dbo::belongsTo(a, stock, "stock");
		Wt::Dbo::field(a, count, "count");
	}
};

void fill_tables(Wt::Dbo::Session& session);

void publisher_info(Wt::Dbo::Session& session);