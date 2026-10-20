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