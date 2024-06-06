/*
** EPITECH PROJECT, 2024
** Client cpp
** File description:
** zap Proj
*/

#include "Client.hpp"

#include <iostream>

Client::Client(const std::string &port, const std::string &host,
    CommandManager &cmd) : _socket(_ioContext), _cmd(cmd)
{
    asio::ip::tcp::resolver resolver(_ioContext);
    _endpoints = resolver.resolve(host, port);
    asio::connect(_socket, _endpoints);
    std::cout << "Connected to the server !" << std::endl;
}

void Client::run()
{
    std::thread reader(&Client::readServ, this);
    writeToServ();
    reader.join();
}

void Client::readServ()
{
    try {

        std::istream is(&_buff);

        while (true) {

            asio::error_code error;
            asio::read_until(_socket, _buff, '\n', error); // A LAISSER !

            if (error == asio::error::eof) {
                std::cout << "Connection closed by server." << std::endl;
                exit(42);
            }

            else if (error) {
                throw asio::system_error(error);
            }

            std::string line;
            std::getline(is, line);

            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }

            _cmd.receiveResponse(line);
        }

    } catch (std::exception &e) {
        std::cerr << "Reader failed: " << e.what() << "\n";
    }
}

void Client::writeToServ()
{
    while (true) {

        std::string command;
        std::getline(std::cin, command);

        if (command.empty()) {
            continue;
        }

        command += "\n";
        _cmd.sendCommand(command);

        asio::write(_socket, asio::buffer(command));
    }
}
