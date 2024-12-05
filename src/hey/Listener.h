//
// Created by gaeqs on 21/10/24.
//

#ifndef LISTENER_H
#define LISTENER_H

#include <functional>

namespace hey {
    template<typename Event>
    struct ListenCounter {
        size_t registered;
        std::function<void(Event)> callee;
        bool active;
    };

    /**
    * Represents an object that can listen observable objects.
    *
    * Listeners calls a given function when an observable object invokes them.
    */
    template<typename Event>
    class Listener {
        ListenCounter<Event>* _counter;

    public:
        Listener(const Listener& other) = delete;

        /**
        * Moves the Observable object, with all its registrations.
        */
        Listener(Listener&& other) noexcept : _counter(other._counter) {
            other._counter = new ListenCounter<Event>(0, nullptr, true);
        }

        /**
        * Creates a listener that doesn't react to invocations.
        *
        * You can use the assign operator to add a reaction.
        */
        Listener() : _counter(new ListenCounter<Event>(0, nullptr, true)) {};

        /**
        * Creates a listener that will call the given function when it is invoked.
        *
        * @param callee the function that will be called.
        */
        template<class Fun>
            requires std::is_invocable_v<Fun, Event>
        Listener(Fun callee): _counter(new ListenCounter<Event>(0, callee, true)) {}

        ~Listener() {
            _counter->callee = nullptr;
            _counter->active = false;
            if (_counter->registered == 0) {
                delete _counter;
            }
        }

        /**
        * @returns the object used to count the registrations of this listener.
        */
        ListenCounter<Event>* getCounter() const {
            return _counter;
        }

        /**
        * Assigns a new reaction to this listener.
        * The old reaction will be overridden.
        */
        template<class Fun>
        requires std::is_invocable_v<Fun, Event>
        Listener& operator=(Fun callee) {
            _counter->callee = callee;
            return *this;
        }

        Listener& operator=(Listener&& other) noexcept {
            if (this == &other) return *this;

            _counter->callee = nullptr;
            _counter->active = false;
            if (_counter->registered == 0) {
                delete _counter;
            }

            _counter = other._counter;
            other._counter = new ListenCounter<Event>(0, nullptr, true);
            return *this;
        }
    };
}

#endif //LISTENER_H
