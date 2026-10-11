#include <gtest/gtest.h>
#include "commands.h"
#include "command_registry.h"

TEST(CommandsTest, SetReturnsOk) {
    Storage s;
    SetCommand cmd;
    Response r = cmd.execute(s, {"SET", "name", "Huseyn"});
    EXPECT_EQ(r.type, Response::Type::SimpleString);
    EXPECT_EQ(r.text, "OK");
}

TEST(CommandsTest, GetExistingKey){
    Storage s;
    s.set("name", "Huseyn");
    GetCommand cmd;
    Response r = cmd.execute(s, {"GET", "name"});
    EXPECT_EQ(r.type, Response::Type::BulkString);
    EXPECT_EQ(r.text, "Huseyn");   
}

TEST(CommandsTest, GetMissingKey) {
    Storage s;
    GetCommand cmd;
    Response r = cmd.execute(s, {"GET", "name"});
    EXPECT_EQ(r.type, Response::Type::Nil);
}

TEST(CommandsTest, SetWrongArgs) {
    Storage s;
    SetCommand cmd;
    Response r = cmd.execute(s, {"SET", "name", "Huseyn", "David"});
    EXPECT_EQ(r.type, Response::Type::Error);
    EXPECT_EQ(r.text, "ERR wrong number of arguments for 'set' command");
}

TEST(CommandsTest, DelCountsRemovedKeys) {
    Storage s;
    s.set("a" , "");
    DelCommand cmd;
    Response r = cmd.execute(s, {"Del", "a", "x"});
    EXPECT_EQ(r.type, Response::Type::Integer);
    EXPECT_EQ(r.number, 1);   
}

TEST(RegistryTest, RegistryFindsKnownCommand) {
    CommandRegistry registry;
    Command* cmd = registry.find("GET");
    EXPECT_NE(cmd, nullptr);       
}

TEST(RegistryTest, RegistryReturnsNullForUnknown) {
    CommandRegistry registry;
    Command* cmd = registry.find("David");
    EXPECT_EQ(cmd, nullptr);      
}