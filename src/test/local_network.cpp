#include "network/local_byte_receiver.hpp"
#include "network/local_byte_sender.hpp"
#include "network/local_message_queue.hpp"
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include <chrono>
#include <future>

BOOST_AUTO_TEST_CASE(send_message) {
    LocalMessageQueue lmq;
    LocalByteSender sender(lmq);
    LocalByteReceiver receiver(lmq);
    Message msg{0,1,2,3,4,5,6,7};
    sender.send(msg);
    auto reply = receiver.block_until_message();
    BOOST_CHECK_EQUAL_COLLECTIONS(msg.begin(), msg.end(), reply.begin(), reply.end());
}

BOOST_AUTO_TEST_CASE(send_message_async) {
    LocalMessageQueue lmq;
    LocalByteSender sender(lmq);
    LocalByteReceiver receiver(lmq);
    Message msg{0,1,2,3,4,5,6,7};
    auto future = std::async([&](){ return receiver.block_until_message(); });
    auto result = future.wait_for(std::chrono::microseconds(20));
    BOOST_CHECK(result == std::future_status::timeout);
    sender.send(msg);
    auto reply = future.get();
    BOOST_CHECK_EQUAL_COLLECTIONS(msg.begin(), msg.end(), reply.begin(), reply.end());
}
