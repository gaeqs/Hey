//
// Created by gaeqs on 21/10/24.
//

#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <hey/Listener.h>

namespace hey {
    /**
    * Represents an object that can be observed using listeners.
    *
    * To listen values transmitted by this observable object,
    * create a Listener object and use the function "addListener" or
    * the operator "+=". You can also use the method "createListener"
    * to create an already bound listener.
    *
    * You cannot copy Observable objects, but you can move them.
    * All bounds will be moved to the new Observable.
    */
    template<typename Event>
    class Observable {
        mutable std::vector<ListenCounter<Event>*> _counters;

    public:
        Observable(const Observable& other) = delete;

        /**
        * Moves the Observable object. All bounds will be moved alongside the object.
        */
        Observable(Observable&& other) noexcept : _counters(std::move(other._counters)) {}

        /**
        * Creates an empty observable object.
        */
        Observable() = default;

        virtual ~Observable() {
            for (auto counter: _counters) {
                if (!counter->active && counter->registered == 1) {
                    delete counter;
                } else {
                    --counter->registered;
                }
            }
        }

        /**
        * Registers a listener.
        * Registered listeners will be invoked when the method
        * "invoke" of this observable object is called.
        *
        * Listeners can be registered several times.
        *
        * @param listener the listener to register.
        */
        void addListener(const Listener<Event>& listener) const {
            auto* counter = listener.getCounter();
            _counters.push_back(counter);
            ++counter->registered;
        }

        /**
        * Removes a listeners from the register list.
        *
        * This function erases all registrations.
        *
        * @param listener the listener to remove.
        */
        void removeListener(const Listener<Event>& listener) const {
            auto* counter = listener.getCounter();
            std::erase(_counters, counter);
        }

        /**
        * Calls all listeners registered on this observable object.
        *
        * The invocation orders will follow the registration order.
        *
        * @param event the data passed to the listeners.
        */
        void invoke(Event event) const {
            for (auto counter: _counters) {
                auto callee = counter->callee;
                if (callee != nullptr) {
                    callee(event);
                }
            }
        }

        /**
        * Creates an already bound listener.
        *
        * @param fun the function that will be called when the listener is invoked.
        */
        template<class Fun>
        Listener<Event> createListener(Fun fun) const {
            Listener<Event> listener(std::move(fun));
            addListener(listener);
            return listener;
        }

        /**
        * Same as addListener.
        */
        const Observable& operator+=(const Listener<Event>& listener) const {
            addListener(listener);
            return *this;
        }

        /**
        * Same as removeListener.
        */
        const Observable& operator-=(const Listener<Event>& listener) const {
            removeListener(listener);
            return *this;
        }
    };
}

#endif //OBSERVABLE_H
