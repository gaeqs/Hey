//
// Created by gaeqs on 21/10/24.
//

#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <hey/Listener.h>

namespace hey {
    template<typename Event>
    class Observable {
        std::vector<ListenCounter<Event>*> _counters;

    public:
        Observable(const Observable& other) = delete;

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

        void addListener(const Listener<Event>& listener) {
            auto* counter = listener.getCounter();
            _counters.push_back(counter);
            ++counter->registered;
        }

        void invoke(Event event) const {
            for (auto counter: _counters) {
                auto callee = counter->callee;
                if (callee != nullptr) {
                    callee(event);
                }
            }
        }

        template<class Fun>
        Listener<Event> createListener(Fun fun) {
            Listener<Event> listener(std::move(fun));
            addListener(listener);
            return listener;
        }

        Observable& operator+=(const Listener<Event>& listener) {
            addListener(listener);
            return *this;
        }
    };
}

#endif //OBSERVABLE_H
