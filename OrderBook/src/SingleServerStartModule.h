#pragma once


#include "./utils/BETime.h"

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

class SingleServerStartModule {
public:
	static int run(int argc, char* argv[]) {

		std::unique_ptr <OrderBook> orderbook = std::make_unique<OrderBook>();

		std::pair< std::mutex, be::QuoteList > safe_quotes;
		std::pair< std::mutex, be::OrderBookList > safe_orderbooks;
		

		std::string server_address("0.0.0.0:50051");
		GRPCTask grpc_task(safe_quotes, safe_orderbooks, orderbook);

		grpc::ServerBuilder builder;
		builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
		builder.RegisterService(&grpc_task);
		std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
		std::cout << "Server listening on " << server_address << std::endl;




		std::cout << "Asking Task to Stop" << std::endl;
		
		std::cout << "Thread Joined" << std::endl;
		std::cout << "Exiting Main Function" << std::endl;

		return 0;
	}
};