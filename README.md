# _Hey!_ A C++20 Observer-Listener Library

_Hey!_ is a lightweight and flexible observer-listener library built with modern C++20, designed to simplify the process
of reacting to events through listeners. The core feature of Hey! are Observables, which allows objects to emit
events that registered listeners can respond to.

_Hey!_ also can be used to listen value changes using the `Value` class. This class is ideal for situations where you
need to track changes to a value and notify listeners whenever the value is updated.

For more advance uses, _Hey!_ also implements the `DerivedValue` class. The value provided by these types of objects are
derived from other values.

## Examples:

### Basic usage

```c++
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
```

### Values

```c++
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
```

### Derived values

```c++
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
```