/*
** EPITECH PROJECT, 2024
** Client GUI
** File description:
** Zap proj
*/

#include <iostream>
#include <asio.hpp>

using asio::ip::tcp;

int main()
{

    try {

        asio::io_context io_context;
        tcp::resolver resolver(io_context);
        tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", "4242"); // late fix;

        tcp::socket socket(io_context);
        asio::connect(socket, endpoints);

        while (true) {

            std::array<char, 128> buf;
            asio::error_code error;
            size_t len = socket.read_some(asio::buffer(buf), error);

            if (error == asio::error::eof) {
                break;
            }

            else if (error) {
                throw asio::system_error(error);
            }

            std::cout.write(buf.data(), len);
        }

    } catch (std::exception& e) {

        std::cerr << "Failed on: " << e.what() << "\n";

    }

    return 0;
}
