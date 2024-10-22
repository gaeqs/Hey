//
// Created by gaeqs on 21/10/24.
//

#include <catch2/catch_all.hpp>
#include <hey/Hey.h>

TEST_CASE("Basics") {
    bool called = false;
    hey::Observable<int> observable;
    hey::Listener<int> listener = [&called](int i) {
        REQUIRE(i == 42);
        called = true;
    };

    observable += listener;

    observable.invoke(42);

    REQUIRE(called);
}

TEST_CASE("Value") {
    bool called = false;
    hey::ObservableValue<std::string> observable;
    hey::Listener<std::string> listener = [&called](const std::string& i) {
        REQUIRE(i == "patata");
        called = true;
    };

    observable.addListener(listener);

    observable = "patata";

    REQUIRE(observable.getValue() == "patata");
    REQUIRE(called);
}


TEST_CASE("Derived Value") {
    bool called = false;
    hey::ObservableValue a = 2;
    hey::ObservableValue b = 3;
    hey::DerivedValue<int, int, int> c([](int a, int b) {
        return a + b;
    }, a, b);

    hey::Listener<int> listener = [&called](int result) {
        REQUIRE(result == 13);
        called = true;
    };

    REQUIRE(a.getValue() == 2);
    REQUIRE(b.getValue() == 3);
    REQUIRE(c.getValue() == 5);

    c += listener;
    a = 10;

    REQUIRE(c.getValue() == 13);
    REQUIRE(called);
}
