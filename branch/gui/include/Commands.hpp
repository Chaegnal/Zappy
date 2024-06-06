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
        std::vector<std::vector<std::string>> getMszCmd() const;

        std::vector<std::string> strToVec(const std::string &input, char token);

    private:

        std::vector<std::vector<std::string>> _bctCmd;
        std::vector<std::vector<std::string>> _mszCmd; // CORE
        std::vector<std::vector<std::string>> _tnaCmd;


        std::vector<std::vector<std::string>> _ppoCmd;
        std::vector<std::vector<std::string>> _plvCmd;
        std::vector<std::vector<std::string>> _pinCmd; // Player info
        std::vector<std::vector<std::string>> _pnwCmd;
        std::vector<std::vector<std::string>> _pdiCmd;


        std::vector<std::string> _sgtCmd;
        std::vector<std::string> _eboCmd; // useless atm
        std::vector<std::string> _smgCmd;

        std::vector<std::string> _sentCommands;
        std::vector<std::string> _receivedResponses;
        mutable std::mutex _mutex;
};

#endif