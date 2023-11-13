#ifndef BOT_HPP
# define BOT_HPP

#include <string>

class Bot {

	private:
		const int _port;
		int _socket;

		void on();
		void send(const std::string & channel, const std::string & msg);

	public:
		Bot(int port);
		~Bot();
		void close();

};

#endif
