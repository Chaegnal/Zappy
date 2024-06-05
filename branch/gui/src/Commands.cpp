/*
** EPITECH PROJECT, 2024
** Commands file
** File description:
** zap Proj
*/

#include "Commands.hpp"

CommandManager::CommandManager()
{

}

void CommandManager::sendCommand(const std::string &command)
{
    std::lock_guard<std::mutex> lock(_mutex);
    _sentCommands.push_back(command);
}

void CommandManager::receiveResponse(const std::string& response)
{
    std::lock_guard<std::mutex> lock(_mutex);
    _receivedResponses.push_back(response);
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

