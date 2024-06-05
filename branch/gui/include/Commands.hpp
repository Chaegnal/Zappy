/*
** EPITECH PROJECT, 2024
** Commands management
** File description:
** Zap Proj
*/

#ifndef COMMANDMANAGER_H
    #define COMMANDMANAGER_H

    #include <string>
    #include <vector>
    #include <mutex>
    #include <asio.hpp>

class CommandManager {

    public:

        CommandManager();
        void sendCommand(const std::string &command);
        void receiveResponse(const std::string &response);
        std::vector<std::string> getSentCommands() const;
        std::vector<std::string> getReceivedResponses() const;

    private:

        std::vector<std::string> _sentCommands;
        std::vector<std::string> _receivedResponses;
        mutable std::mutex _mutex;
};

#endif