//
// Created by gaeqs on 21/10/24.
//

#include <catch2/catch_all.hpp>

#include <hey_listen/HeyListen.h>

TEST_CASE("Basics") {
    bool called = false;
    hey_listen::Observable<int> observable;
    hey_listen::Listener<int> listener{
        [&called](int i) {
            REQUIRE(i == 42);
            called = true;
        }
    };

    observable.addListener(listener);

    observable.invoke(42);

    REQUIRE(called);
}
