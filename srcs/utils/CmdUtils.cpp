#include "CmdUtils.hpp"

std::vector<Channel *> *CmdUtils::getChannelsOf(std::string cmd, Server *server)
{
    std::vector<Channel *> *channels = new std::vector<Channel *>;

    size_t pos = 0;
    std::string token;
    while ((pos = cmd.find(",")) != std::string::npos) {
        token = cmd.substr(0, pos);
        channels->push_back(server->getChannelByName(token));
        cmd.erase(0, pos + 1);
    }
    channels->push_back(server->getChannelByName(cmd));
    return channels;
}

std::vector<std::string> *CmdUtils::getKeysOf(const std::string &cmd)
{
    // TODO: to implement
    (void) cmd;
    return NULL;
}