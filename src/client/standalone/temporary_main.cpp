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
#include "systems/draw.hpp"
#include "systems/event.hpp"
#include "systems/physics.hpp"
#include "components/sprite.hpp"
#include "components/player_controlled.hpp"
#include "utility.hpp"
#include "world.hpp"
#include "assert.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <thread>
#include <functional>
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
        sf::RenderWindow window(sf::VideoMode(800, 600), "Still haven't come up with a name");
        world.add_system<EventSystem>(&window);
        world.add_system<DrawSystem>(&window);
        world.add_system<PhysicsSystem>();
        // Some test code to make sure we can draw things.
        sf::Image img;
        img.create(20, 20, sf::Color(0xFF, 0xFF, 0xFF));
        sf::Texture txtr;
        txtr.loadFromImage(img);
        auto e = world.new_entity();
        world.add_component_to<SpriteComponent>(e, std::cref(txtr));
        world.add_component_to<PlayerControlledComponent>(e);
        while (window.isOpen())
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
