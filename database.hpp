#pragma once

#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;
using std::string;

//std::string SERVERNAME = "pink"; //change this to d

class database_obj {
	mongocxx::instance inst{};
	mongocxx::client conn{ mongocxx::uri{"MONGODB URI"} };
	public: int send_to_db(const std::vector<string> names, int state, std::string servername) {
		mongocxx::database db = conn["rates"];
		mongocxx::collection coll = db[servername];
		bsoncxx::builder::stream::document document{};
		std::string final_names;
		for (std::string name : names) {
			final_names = final_names + " " + name ;
		}
		int amount = names.size();
		if (state == 1) {
			try {
				document
					<< "_id" << "p_names"
					<< "names" << final_names
					<< "amount" << amount;
				coll.insert_one(document.view());
			} catch (...) {
				bsoncxx::builder::stream::document filter{};
				filter << "_id" << "p_names";
				document
					<< "_id" << "p_names"
					<< "names" << final_names
					<< "amount" << amount;
				coll.replace_one(filter.view(), document.view());
				}
		}
		else if (state == 2) {
			try {
				document
					<< "_id" << "n_names"
					<< "names" << final_names
					<< "amount" << amount;
				coll.insert_one(document.view());
			}
			catch (...) {
				bsoncxx::builder::stream::document filter{};
				filter << "_id" << "n_names";
				document
					<< "_id" << "n_names"
					<< "names" << final_names
					<< "amount" << amount;
				coll.replace_one(filter.view(), document.view());
			}
		}
		else {
			std::cout << "THE STATE CAN'T BE " << state << " CLOSING..." << std::endl;
			return -1;
		}
		//coll.insert_one(document.view());
		return 0;
	}
};
