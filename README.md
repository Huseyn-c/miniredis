# MiniRedis

A Redis-like in-memory key-value store written from scratch in C++17.

I'm building this to learn how a real server works under the hood: storage, command handling, the RESP protocol, networking and later concurrency and persistence. No external frameworks except GoogleTest for testing.

**Status:** in progress (phase 2 of 5).

## Features

- In-memory storage on `std::unordered_map`
- Commands: `SET`, `GET`, `DEL`
- Extensible command system: an abstract `Command` interface and a `CommandRegistry` that owns commands via `std::unique_ptr`. A new command is a new class; the dispatch logic doesn't change.
- Typed responses (simple string, bulk string, nil, integer, error)
- RESP serializer and parser (the protocol used by the real Redis); the parser handles incomplete input, which matters because TCP is a byte stream
- Interactive console (REPL)
- 25 unit tests with GoogleTest

## Project structure

```
src/
  storage.*            key-value storage
  response.*           typed reply object
  command.h            abstract Command interface
  commands.*           SET, GET, DEL
  command_registry.*   maps command names to handlers
  parser.*             tokenizer for the console
  resp.*               RESP serialize / parse
  main.cpp             REPL
tests/                 GoogleTest unit tests
```

## Build and run

Requirements: a C++17 compiler, CMake, GoogleTest.

```bash
cmake -S . -B build
cmake --build build
./build/miniredis   # start the console
./build/tests       # run the tests
```

Example:

```
> SET name Huseyn
OK
> GET name
"Huseyn"
> DEL name
(integer) 1
> GET name
(nil)
```

## Roadmap

- [x] Phase 1: storage, command system, console, unit tests
- [ ] Phase 2: RESP protocol + TCP server (POSIX sockets), compatible with `redis-cli`
- [ ] Phase 3: multiple clients with threads and mutexes
- [ ] Phase 4: event loop with `kqueue` / `epoll`
- [ ] Phase 5: persistence (append-only file) and key expiration (TTL)