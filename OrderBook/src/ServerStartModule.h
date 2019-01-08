#pragma once

#include "./RedisTask.h"

#include "OrderBook/OrderBook.h"

#include "./utils/BETime.h"

#include "RedisTask.h"
#include "MongoTask.h"
#include <mutex>

#include "./protobuf/Trading.pb.h"

#include "./GRPCTask.h"


struct SafeQuotes {
	std::mutex mu;
	be::QuoteList quotes;
};

struct SafeOrderbooks {
	std::mutex mu;
	be::OrderBookList orderbooks;
};

class ServerStartModule {
public:
	static int run(int argc, char* argv[]) {

		std::pair< std::mutex, be::QuoteList > safe_quotes;
		std::pair< std::mutex, be::OrderBookList > safe_orderbooks;
		

		std::string server_address("0.0.0.0:50051");
		GRPCTask grpc_task(safe_quotes, safe_orderbooks);

		grpc::ServerBuilder builder;
		builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
		builder.RegisterService(&grpc_task);
		std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
		std::cout << "Server listening on " << server_address << std::endl;



		BETime timestamp;
		timestamp.start();

		// main thread
		std::unique_ptr <OrderBook> orderbook = std::make_unique<OrderBook>();

		int count_of_processed = 0;
		while (true)
		{
			//Quote quote;
			std::unique_lock < std::mutex > locker(safe_quotes.first);

			auto qu = safe_quotes.second.mutable_quotes();

			bool b_exist = false;
			be::Quote searched_quote;

			if (!qu->empty()) {
				b_exist = true;
				auto last_item = qu->rbegin();
				searched_quote.CopyFrom((*last_item));

				 
				auto temp = searched_quote.order_type();

				qu->RemoveLast();
			}

			locker.unlock();

			if(b_exist)
			{
				// end lock
				std::pair<std::vector<TransactionRecord>, be::Quote> ret = orderbook->process_order(searched_quote, false, false);

				std::string ostr = orderbook->text();
				std::cout << ostr;
				std::cout << count_of_processed << "th " << std::endl;
				++count_of_processed;

				// update tree!

				be::OrderBook ob;
				orderbook->get_orderbook(ob);

				//// debug
				//auto ask_tree = ob.ask_tree();
				//for (auto ask : ask_tree.price_map()) {
				//	std::cout << ask.second.volumn();
				//}
				///////////////////////////////////////////

				std::unique_lock < std::mutex > locker(safe_orderbooks.first);

				auto new_ob = safe_orderbooks.second.add_orderbooks();
				new_ob->CopyFrom(ob);

				//// debug
				//auto new_ask_tree = new_ob->mutable_ask_tree();
				//for (auto ask : ask_tree.price_map()) {
				//	std::cout << ask.second.volumn();
				//}
				/////////////////////////////////////////////

				locker.unlock();
			}
		}


		std::cout << "Asking Task to Stop" << std::endl;

		// Stop the Task
		//redis_task.stop();
		//Waiting for thread to join
		//redis_th.join();

		std::cout << "Thread Joined" << std::endl;
		std::cout << "Exiting Main Function" << std::endl;

		return 0;
	}
};