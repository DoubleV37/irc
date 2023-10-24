#pragma once

#include <string>
#include <vector>
#include "../Channel.hpp"
#include "../Server.hpp"

class CmdUtils {
    public:
        static std::vector<Channel *> *getChannelsOf(std::string cmd, Server *server);
        static std::vector<std::string> *getKeysOf(std::string const & cmd);

};
