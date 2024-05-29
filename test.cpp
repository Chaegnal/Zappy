/*
** EPITECH PROJECT, 2024
** Client GUI
** File description:
** Zap proj
*/

#include <iostream>
#include <asio.hpp>

using asio::ip::tcp;

int main() {
    try {
        asio::io_context io_context;
        tcp::resolver resolver(io_context);
        tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", "4242");

        tcp::socket socket(io_context);
        asio::connect(socket, endpoints);

        asio::streambuf buffer;
        std::istream is(&buffer);

        std::cout << "Connected to the server." << std::endl;

        // Separate thread for reading from the server
        std::thread reader([&]() {
            try {
                while (true) {
                    asio::error_code error;
                    size_t len = asio::read_until(socket, buffer, '\n', error);

                    if (error == asio::error::eof) {
                        std::cout << "Connection closed by server." << std::endl;
                        exit(42);
                    } else if (error) {
                        throw asio::system_error(error);
                    }

                    std::string line;
                    std::getline(is, line);

                    // Remove the carriage return if present (for CRLF line endings)
                    if (!line.empty() && line.back() == '\r') {
                        line.pop_back();
                    }

                    std::cout << "Received: " << line << std::endl;
                }
            } catch (std::exception& e) {
                std::cerr << "Reader failed: " << e.what() << "\n";
            }
        });

        // Main thread for writing to the server
        while (true) {
            std::string command;
            std::getline(std::cin, command);
            if (command.empty()) continue;

            command += "\n";  // Add newline character to command
            asio::write(socket, asio::buffer(command));
        }

        reader.join();
    } catch (std::exception& e) {
        std::cerr << "Failed on: " << e.what() << "\n";
    }

    return 0;
}





