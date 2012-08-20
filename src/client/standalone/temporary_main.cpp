/*
 * This is a temporary file for running the game locally.
 *
 * I honestly spent a while wondering how best to organise things so that
 * the system would be extensible, decoupled, possible to easily adapt to
 * when we want real networking, configurable at runtime, pleasant to his
 * tentacleness Cthulhu, free of redundancy, and a bunch of other things
 * I'd rather not get into now.
 *
 * Eventually, I decided I may as well write something now, and as soon as
 * it does anything useful, we'll refactor it.
 *
 * Won't we?
 */

#include "network/sender.hpp"
#include "network/receiver.hpp"
#include "network/byte_sender.hpp"
#include "network/byte_receiver.hpp"
#include "network/local_byte_sender.hpp"
#include "network/local_byte_receiver.hpp"
#include "network/local_message_queue.hpp"
#include "systems/window.hpp"
#include "utility.hpp"
#include "world.hpp"
#include "assert.hpp"
#include <thread>
#include <iostream>

void server_do(std::unique_ptr<IByteSender>&& b_sender, std::unique_ptr<IByteReceiver>&& b_receiver) {
    try {
        World world;
        Sender sender(std::move(b_sender));
        Receiver<World> receiver(world, std::move(b_receiver));
    }
    catch (BaseError& e) {
        // Strictly speaking, this cleanup is not safe due to the possibility of
        // client and server dying at the same time and seeing as std::cerr does
        // not make thread safety guarantees we may mess up the output with
        // this.  However, I'm not particularly eager to write a thread safe
        // wrapper around std::iostream so I'll leave this as a TODO.
        print_diagnostic_info(std::cerr, e);
        if (std::string const* err_msg_p = boost::get_error_info<err_msg>(e))
            std::cerr << "Error: " << *err_msg_p << std::endl;
    }
}

void client_do(std::unique_ptr<IByteSender>&& b_sender, std::unique_ptr<IByteReceiver>&& b_receiver) {
    try {
        World world;
        Sender sender(std::move(b_sender));
        Receiver<World> receiver(world, std::move(b_receiver));
        world.add_system<WindowSystem>();
        for (;;)
            world.update(1);
    }
    catch (BaseError& e) {
        print_diagnostic_info(std::cerr, e);
        if (std::string const* err_msg_p = boost::get_error_info<err_msg>(e))
            std::cerr << "Error: " << *err_msg_p << std::endl;
    }
}

int main() {
    LocalMessageQueue server_to_client, client_to_server;
    std::thread server(server_do, make_unique<LocalByteSender>(server_to_client), make_unique<LocalByteReceiver>(client_to_server));
    std::thread client(client_do, make_unique<LocalByteSender>(client_to_server), make_unique<LocalByteReceiver>(server_to_client));
    client.join();
    server.join();
}
