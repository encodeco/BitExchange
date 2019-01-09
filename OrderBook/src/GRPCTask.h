#include <iostream>
#include <cstdlib>
#include <string>

#include <grpc/grpc.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/security/server_credentials.h>

#include "./protobuf/Trading.pb.h"
#include "./protobuf/Trading.grpc.pb.h"

//#include <deque>
#include <thread>
#include <mutex>
#include "./orderbook/common.h"

#include "OrderBook/OrderBook.h"

#pragma comment(lib,"WS2_32")
#pragma comment(lib, "grpc++.lib")

class GRPCTask : public be::Trading::Service {
public:
	std::pair< std::mutex, be::QuoteList >		&safe_quotes;
	std::pair< std::mutex, be::OrderBookList >	&safe_orderbooks;
	std::unique_ptr <OrderBook>					&orderbook;

public:
	GRPCTask(std::pair< std::mutex, be::QuoteList > &safe_quotes, std::pair< std::mutex, be::OrderBookList > &safe_orderbooks, std::unique_ptr <OrderBook> &orderbook) : be::Trading::Service(), safe_quotes(safe_quotes), safe_orderbooks(safe_orderbooks), orderbook(orderbook){
		//pos = 0; 
	}

	::grpc::Status QuoteUpdateAsync(::grpc::ServerContext* context, const be::Quote* request, be::Empty* response) {
		{
			std::unique_lock < std::mutex > locker(safe_quotes.first);

			// 
			auto new_quotes = safe_quotes.second.add_quotes();
			new_quotes->CopyFrom(*request);

			locker.unlock();
		}

		return grpc::Status::OK;
	}

	::grpc::Status QuoteUpdateSync(::grpc::ServerContext* context, const be::Quote* request, be::MatchingResult* response) {
		{
			be::Quote new_quotes;
			new_quotes.CopyFrom(*request);

			{
				if (const char order_type = new_quotes.order_type().c_str()[0] == 0)
					return grpc::Status::OK;

				std::pair<std::vector<TransactionRecord>, be::Quote> ret = orderbook->process_order(new_quotes, false, false);

				std::string ostr = orderbook->text();
				std::cout << ostr;

				be::OrderBook ob;
				orderbook->get_orderbook(ob);

				auto res_ob = response->mutable_orderbook();
				res_ob->CopyFrom(ob);
			}
		}

		return grpc::Status::OK;
	}

	::grpc::Status OrderBookUpdate(::grpc::ServerContext* context, const be::Empty* request, be::OrderBook* response) {
		{
			std::unique_lock < std::mutex > locker(safe_orderbooks.first);

			auto new_quotes = safe_orderbooks.second.mutable_orderbooks();

			if (!new_quotes->empty()) {

				auto last = new_quotes->rbegin();
				//auto last_one = (*last);
				//auto bids_map = last_one.bids_map();
				//auto asks_map = last_one.asks_map();

				//// debug	////////////////////////
				//auto ask_tree = last->mutable_ask_tree();
				//auto p_map = ask_tree->mutable_price_map();
				//for (auto item : *p_map) {
				//	std::cout << item.second.volumn();
				//	std::cout << std::endl;
				//}
				/////////////////////////////////////

				response->CopyFrom(*last);
			}

			// debug	////////////////////////
			//auto ask_tree = response->mutable_ask_tree();
			//auto p_map = ask_tree->mutable_price_map();
			//for (auto item : *p_map) {
			//	std::cout << item.second.volumn();
			//	std::cout << std::endl;
			//}
			/////////////////////////////////////

			locker.unlock();
		}

		return grpc::Status::OK;
	}
};



//::grpc::Status Update(::grpc::ServerContext* context, const NumSteps* request, Empty* response) {
//	int32_t n = request->n();
//	for (int32_t i = 0; i < n; i++) {
//		if (rand() % 2 == 0) { pos += 1; }
//		else { pos -= 1; }
//	}
//	return grpc::Status::OK;
//}
//::grpc::Status GetPosition(::grpc::ServerContext* context, const Empty* request, Position* response) {
//	response->set_x(pos);
//	return grpc::Status::OK;
//}
//private:
//	int pos;
//int main_temp(int argc, char** argv) {
//
//	std::string server_address("0.0.0.0:50051");
//	RandomWalkerImpl service;
//
//	grpc::ServerBuilder builder;
//	builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
//	builder.RegisterService(&service);
//	std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
//	std::cout << "Server listening on " << server_address << std::endl;
//	server->Wait();
//
//	return 0;
//}