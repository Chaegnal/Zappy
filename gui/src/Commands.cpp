/*
** EPITECH PROJECT, 2024
** Commands file
** File description:
** zap Proj
*/

#include "Commands.hpp"
#include <iostream>

CommandManager::CommandManager()
{

}

void CommandManager::sendCommand(const std::string &command)
{
    std::lock_guard<std::mutex> lock(_mutex);
    _sentCommands.push_back(command);
}

void CommandManager::receiveResponse(const std::string &response)
{
    std::lock_guard<std::mutex> lock(_mutex);

    int token = 3;
    std::string cmd = response.substr(0, token);
    std::vector<std::string> params = strToVec(response.substr(token), ' ');

    if (cmd.compare("msz") == 0) {
        _mszCmd.push_back(params);
    } else if (cmd.compare("bct") == 0) {
        _bctCmd.push_back(params);
    } else if (cmd.compare("tna") == 0) {
        _tnaCmd.push_back(params);
    } else if (cmd.compare("pnw") == 0) {
        _pnwCmd.push_back(params);
    } else if (cmd.compare("pdi") == 0) {
        _pdiCmd.push_back(params);
    } else if (cmd.compare("plv") == 0) {
        _plvCmd.push_back(params);
    } else if (cmd.compare("pin") == 0) {
        _pinCmd.push_back(params);
    } else if (cmd.compare("ppo") == 0) {
        _ppoCmd.push_back(params);
    }
    std::cout << response << std::endl;
}

std::vector<std::string> CommandManager::getSentCommands() const
{
    std::lock_guard<std::mutex> lock(_mutex);
    return _sentCommands;
}

std::vector<std::string> CommandManager::getReceivedResponses() const
{
    std::lock_guard<std::mutex> lock(_mutex);
    return _receivedResponses;
}

std::vector<std::vector<std::string>> CommandManager::getMszCmd() const
{
    std::lock_guard<std::mutex> lock(_mutex);
    return _mszCmd;
}

std::vector<std::string> CommandManager::strToVec(const std::string &input, char token)
{
    std::vector<std::string> res;
    std::string tmp;

    for (size_t t = 0; t < input.size(); t++) {
        if (input.at(t) == token) {
            if (!tmp.empty()) {
                res.push_back(tmp);
                tmp.clear();
            }

        } else {
            tmp.push_back(input[t]);
        }
    }

    if (!tmp.empty()) {
        res.push_back(tmp);
    }

    return res;
}