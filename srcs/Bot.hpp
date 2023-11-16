#ifndef BOT_HPP
# define BOT_HPP

#include <bits/types/siginfo_t.h>
#include <string>
#include <vector>

class Bot {

	private:
		int _port;
		int _socket;
		std::string _password;
		std::string _name;
		bool exit;

		void on();
		void send(const std::string & channel, const std::string & msg);
		void exec(const std::string & cmd, const std::string & channel, const std::string & arg);
		std::string compact(std::vector<char> & vector) const;

	public:
		Bot();
		Bot(int port, std::string password, std::string name);
		~Bot();

		Bot& operator=(const Bot & copy);

		void run();
		void close();

};

#endif
