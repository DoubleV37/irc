#ifndef BOT_HPP
# define BOT_HPP

#include <string>
#include <vector>

class Bot {

	private:
		const int _port;
		int _socket;

		void on();
		void send(const std::string & channel, const std::string & msg);
		void exec(const std::string & cmd, const std::string & channel, const std::string & arg);
		std::string compact(const std::vector<char> & vector) const;

	public:
		Bot(int port);
		~Bot();
		void run();
		void close();

};

#endif
