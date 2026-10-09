#pragma once
#include <string>

struct Response {
    enum class Type { SimpleString, BulkString, Nil, Integer, Error };

    Type type;
    std::string text;
    long long number = 0;

    static Response ok(){
        Response r ; 
        r.type = Type::SimpleString;
        r.text = "OK";
        return r;
    }

    static Response bulk(const std::string& s){
        Response r ; 
        r.type = Type::BulkString;
        r.text = s ;
        return r ;
    }

    static Response nil(){
        Response r ; 
        r.type = Type::Nil;
        return r ; 
    }

    static Response integer(long long n){
        Response r ;
        r.type = Type::Integer;
        r.number = n ; 
        return r ; 
    }

    static Response error(const std::string& msg){
        Response r ; 
        r.type = Type::Error;
        r.text = msg ;
        return r ; 
    }
};