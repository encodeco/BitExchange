#include <set>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include "./utils/Stoppable.h"

typedef websocketpp::server<websocketpp::config::asio> server;

using websocketpp::connection_hdl;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

#include <mutex>

class StreamingTask : public Stoppable {
public:
	std::deque <std::string> queue;
	uint16_t port;

public:
	std::mutex mu;
	std::condition_variable cond;

public:
	void safe_insert(std::string msg)
	{
		{
			std::lock_guard<std::mutex> guard(mu);
			queue.push_front(msg);
		}
		cond.notify_one();
	}

	bool safe_pop_all(std::string &msg)
	{
		bool exist = false;
		{
			std::lock_guard<std::mutex> guard(mu);
			if (!queue.empty()) {
				msg = queue.front();
				queue.clear();
				exist = true;
			}
		}
		return exist;
	}

public:
	StreamingTask(uint16_t port) {
		this->port = port;
		m_server.init_asio();

		m_server.set_open_handler(bind(&StreamingTask::on_open, this, ::_1));
		m_server.set_close_handler(bind(&StreamingTask::on_close, this, ::_1));
		m_server.set_message_handler(bind(&StreamingTask::on_message, this, ::_1, ::_2));
	}

	void on_open(connection_hdl hdl) {
		m_connections.insert(hdl);
	}

	void on_close(connection_hdl hdl) {
		m_connections.erase(hdl);
	}

	void on_message(connection_hdl hdl, server::message_ptr msg) {
		for (auto it : m_connections) {
			//m_server.send(it, msg);
			std::string message;
			bool bexist =  safe_pop_all(message);
			if (bexist) {
				std::string sendmessage = message.substr(0, 10);
				m_server.send(it, message, websocketpp::frame::opcode::text);
			}
			//m_server.send(it, msg, websocketpp::frame::opcode::text);
		}
	}

	void run() {
		m_server.listen(port);
		m_server.start_accept();
		m_server.run();
	}
private:
	typedef std::set<connection_hdl, std::owner_less<connection_hdl>> con_list;

	server m_server;
	con_list m_connections;
};

//int main() {
//	broadcast_server server;
//	server.run(9002);
//}
