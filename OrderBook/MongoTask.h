#pragma once

#include "utils/Stoppable.h"
#include "orderbook/common.h"
#include <iostream>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <deque>
#include <thread>
#include <mutex>

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

class MongoTask : public Stoppable
{
public:
	std::deque <BidAsk> queue;
	uint16_t port;

public:
	std::mutex mu;
	std::condition_variable cond;


public:
	void safe_insert(BidAsk &bidask)
	{
		{
			std::lock_guard<std::mutex> guard(mu);
			queue.push_front(bidask);
		}
		cond.notify_one();
	}

	bool safe_pop_all(BidAsk &bidask)
	{
		bool exist = false;
		{
			std::lock_guard<std::mutex> guard(mu);
			if (!queue.empty()) {
				bidask = queue.front();
				queue.clear();
				exist = true;
			}
		}
		return exist;
	}

	bool make_json(BidAsk &bidask, bsoncxx::document::view &view) {
		//auto builder = bsoncxx::builder::stream::document{};

		PriceQuantityVec &bids = bidask.first;
		//PriceQuantityVec &ask = bidask.second;

		//builder << "bids" << bsoncxx::builder::stream::open_array;
		auto builder_bids = bsoncxx::builder::basic::array{};

		for (auto order : bids) {


			builder_bids = builder_bids << builder::stream::open_document << "key" << e
				<< builder::stream::close_document;
			
		}
		builder << close_array;

		bsoncxx::document::value doc_value = builder
			<< "name" << "MongoDB"
			<< "type" << "database"
			<< "count" << 1
			<< "versions" << bsoncxx::builder::stream::open_array
			<< "v3.2" << "v3.0" << "v2.6"
			<< close_array
			<< "info" << bsoncxx::builder::stream::open_document
			<< "x" << 203
			<< "y" << 102
			<< bsoncxx::builder::stream::close_document
			<< bsoncxx::builder::stream::finalize;

		view = doc_value.view();
		return true;
	}

	bool safe_pop_all(bsoncxx::document::view &view)
	{
		bool exist = false;
		{
			std::lock_guard<std::mutex> guard(mu);
			if (!queue.empty()) {
				auto bidask = queue.front();
				queue.clear();
				exist = true;
			}
		}
		return exist;
	}
public:
	void run() {
		mongocxx::instance instance{}; // This should be done only once.
		mongocxx::uri uri("mongodb://localhost:27017");
		mongocxx::client client(uri);

		mongocxx::database db = client["bitexchange"];
		mongocxx::collection coll = db["bitexchange"];


		//while (stopRequested() == false)
		while(1)
		{
			//m_server.send(it, msg);
			BidAsk bidask;
			bool bexist = safe_pop_all(bidask);
			if (bexist) {
				//std::string sendmessage = message.substr(0, 10);
				//bidask;
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}



		/*
		

		auto builder = bsoncxx::builder::stream::document{};
		bsoncxx::document::value doc_value = builder
			<< "name" << "MongoDB"
			<< "type" << "database"
			<< "count" << 1
			<< "versions" << bsoncxx::builder::stream::open_array
			<< "v3.2" << "v3.0" << "v2.6"
			<< close_array
			<< "info" << bsoncxx::builder::stream::open_document
			<< "x" << 203
			<< "y" << 102
			<< bsoncxx::builder::stream::close_document
			<< bsoncxx::builder::stream::finalize;


		bsoncxx::document::view view = doc_value.view();

		coll.insert_one(view);
		*/
	}
};
