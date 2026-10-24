#include <gtest/gtest.h>   
#include "resp.h"          

TEST(RespTest, SerializeOk) {
    EXPECT_EQ(serialize(Response::ok()), "+OK\r\n");
}

TEST(RespTest, SerializeBulk) {
    EXPECT_EQ(serialize(Response::bulk("Huseyn")), "$6\r\nHuseyn\r\n");
}

TEST(RespTest, SerializeNil) {
    EXPECT_EQ(serialize(Response::nil()), "$-1\r\n");
}

TEST(RespTest, SerializeInteger) {
    EXPECT_EQ(serialize(Response::integer(1)), ":1\r\n");
}

TEST(RespTest, SerializeError) {
    EXPECT_EQ(serialize(Response::error("Invalid")), "-Invalid\r\n");
}

TEST(RespTest, ParseFullCommand) {
    std::string buf = "*2\r\n$3\r\nGET\r\n$4\r\nname\r\n";
    std::vector<std::string> args;
    size_t consumed = 0;

    EXPECT_TRUE(parseRESP(buf, args, consumed));
    EXPECT_EQ(args.size(), 2);
    EXPECT_EQ(args[0], "GET");
    EXPECT_EQ(args[1], "name");
    EXPECT_EQ(consumed, buf.size());
}

TEST(RespTest, ParseIncompleteCommand) {
    std::string buf = "*2\r\n$3\r\nGET\r\n$4\r\nna";
    std::vector<std::string> args;
    size_t consumed = 0;

    EXPECT_FALSE(parseRESP(buf, args, consumed));
}

TEST(RespTest, ParseEmptyBuffer) {
    std::string buf = "";
    std::vector<std::string> args;
    size_t consumed = 0;

    EXPECT_FALSE(parseRESP(buf, args, consumed));
}

TEST(RespTest, ParseWrongStart) {
    std::string buf = "\r\n$3\r\nGET\r\n$4\r\nname\r\n";
    std::vector<std::string> args;
    size_t consumed = 0;

    EXPECT_FALSE(parseRESP(buf, args, consumed));
}

TEST(RespTest, ParseValueWithSpace) {
    std::string buf = "*3\r\n$3\r\nSET\r\n$8\r\ngreeting\r\n$11\r\nHello world\r\n";
    std::vector<std::string> args;
    size_t consumed = 0;

    EXPECT_TRUE(parseRESP(buf, args, consumed));
    EXPECT_EQ(args.size(), 3);
    EXPECT_EQ(args[0], "SET");
    EXPECT_EQ(args[1], "greeting");
    EXPECT_EQ(args[2], "Hello world");
}