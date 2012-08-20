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
#include <thread>
#include <iostream>

void server_do(std::unique_ptr<IByteSender>&& b_sender, std::unique_ptr<IByteReceiver>&& b_receiver) {
    World world;
    Sender sender(std::move(b_sender));
    Receiver<World> receiver(world, std::move(b_receiver));
}

void client_do(std::unique_ptr<IByteSender>&& b_sender, std::unique_ptr<IByteReceiver>&& b_receiver) {
    World world;
    Sender sender(std::move(b_sender));
    Receiver<World> receiver(world, std::move(b_receiver));
    world.add_system<WindowSystem>();
    for (;;)
        world.update(1);
}

int main() {
    LocalMessageQueue server_to_client, client_to_server;
    std::thread(server_do, make_unique<LocalByteSender>(server_to_client), make_unique<LocalByteReceiver>(client_to_server)).detach();
    std::thread(client_do, make_unique<LocalByteSender>(client_to_server), make_unique<LocalByteReceiver>(server_to_client)).join();
}
