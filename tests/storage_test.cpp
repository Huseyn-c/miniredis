#include <gtest/gtest.h>
#include "storage.h"

TEST(StorageTest, SetThenGetReturnsValue) {
    Storage s;
    s.set("name", "Huseyn");
    EXPECT_EQ(s.get("name"), "Huseyn");
}

TEST(StorageTest , NonExistingKey){
    Storage s;
    EXPECT_FALSE(s.get("x").has_value());
}

TEST(StorageTest , RewritingKey){
    Storage s;
    s.set("name", "Huseyn");
    s.set("name", "David") ;
    EXPECT_EQ(s.get("name"), "David");
}

TEST(StorageTest, DeletingExistingKey){
    Storage s ; 
    s.set("name", "");
    EXPECT_TRUE(s.remove("name"));
    EXPECT_FALSE(s.exists("name"));
}

TEST(StorageTest, DeletingNonExistingKey){
    Storage s ; 
    EXPECT_FALSE(s.remove("x"));
}