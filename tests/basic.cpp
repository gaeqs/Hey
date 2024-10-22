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
