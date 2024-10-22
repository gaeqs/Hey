//
// Created by gaeqs on 21/10/2024.
//

#include <iostream>
#include <catch2/catch_all.hpp>
#include <hey/Hey.h>

void* operator new(size_t n) {
    return malloc(n);
}

void* checkDeletion = nullptr;
bool deleted = false;

void operator delete(void* p) {
    if (p == checkDeletion) {
        deleted = true;
    }
    free(p);
}


TEST_CASE("Counter", "[pointer]") {
    auto observable = new hey::Observable<int>;
    auto listener = new hey::Listener<int>{[](int i) {}};
    hey::ListenCounter<int>* counter = listener->getCounter();

    REQUIRE(counter->active);
    REQUIRE(counter->callee != nullptr);
    REQUIRE(counter->registered == 0);

    *observable += *listener;

    REQUIRE(counter->active);
    REQUIRE(counter->callee != nullptr);
    REQUIRE(counter->registered == 1);

    delete observable;

    REQUIRE(counter->active);
    REQUIRE(counter->callee != nullptr);
    REQUIRE(counter->registered == 0);

    observable = new hey::Observable<int>;
    REQUIRE(counter->active);
    REQUIRE(counter->callee != nullptr);
    REQUIRE(counter->registered == 0);

    *observable += *listener;
    REQUIRE(counter->active);
    REQUIRE(counter->callee != nullptr);
    REQUIRE(counter->registered == 1);

    delete listener;

    REQUIRE_FALSE(counter->active);
    REQUIRE(counter->callee == nullptr);
    REQUIRE(counter->registered == 1);

    checkDeletion = counter;
    deleted = false;
    delete observable;
    REQUIRE(deleted);
}
