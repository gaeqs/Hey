//
// Created by gaeqs on 22/10/2024.
//

#include <iostream>
#include <catch2/catch_all.hpp>
#include <hey/Hey.h>

TEST_CASE("Basic usage", "[example]") {
    hey::Observable<int> observable;

    hey::Listener<int> listener = [](int i) {
        std::cout << "I received the value " << i << "!" << std::endl;
    };

    observable += listener; // Or observable.addListener(listener)
    observable.invoke(42); // Listener will be invoked.

    observable -= listener; // Or observable.removeListener(listener)

    observable.invoke(42); // Listener won't be invoked.

    observable += listener;
    observable += listener;
    observable.invoke(42); // Listener will be invoked twice.
}

TEST_CASE("Observable values", "[example]") {
    hey::ObservableValue<int> observable = 30;

    hey::Listener<int> listener = [](int i) {
        std::cout << "I received the value " << i << "!" << std::endl;
    };

    observable += listener; // Or observable.addListener(listener)
    observable = 42; // Listener will be invoked.

    std::cout << "Now the object holds the value " << observable.getValue() << "." << std::endl;

    observable -= listener; // Or observable.removeListener(listener)

    observable = 10; // Listener won't be invoked.

    std::cout << "Now the object holds the value " << observable.getValue() << "." << std::endl;

    observable += listener;
    observable += listener;
    observable = 60; // Listener will be invoked twice.
    std::cout << "Now the object holds the value " << observable.getValue() << "." << std::endl;
}

TEST_CASE("Derived values", "[example]") {
    hey::ObservableValue<int> a = 30;
    hey::ObservableValue<int> b = 5;

    hey::DerivedValue<int, int, int> c([](int a, int b) {
        return a + b;
    }, a, b);


    hey::Listener<int> aListener = a.createListener([](int i) {
        std::cout << "A = " << i << "." << std::endl;
    });

    hey::Listener<int> bListener = b.createListener([](int i) {
        std::cout << "B = " << i << "." << std::endl;
    });

    hey::Listener<int> cListener = c.createListener([](int i) {
        std::cout << "C = " << i << "." << std::endl;
    });

    std::cout << "--- Initial values ---" << std::endl;
    std::cout << "A = " << a.getValue() << "." << std::endl;
    std::cout << "B = " << b.getValue() << "." << std::endl;
    std::cout << "C = " << c.getValue() << "." << std::endl;
    std::cout << "----------------------" << std::endl;

    a = 10; // Calls aListener and cListener.
    b = 40; // Calls bListener and cListener.
}
