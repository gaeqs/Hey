//
// Created by gaeqs on 21/10/24.
//

#ifndef OBSERVABLEVALUE_H
#define OBSERVABLEVALUE_H

#include <hey/Observable.h>
#include <hey/Value.h>

namespace hey {

    /**
    * Represents a value that can be observed by listeners.
    */
    template<typename T>
    class ObservableValue : public Observable<T>, public Value<T> {
        T _value;

    public:
        ObservableValue() = default;

        /**
        * Creates an observable value using the given initial value.
        * @param value the initial value.
        */
        ObservableValue(const T& value) : _value(value) {}

        /**
        * Creates an observable value using the given initial value.
        * @param value the initial value.
        */
        ObservableValue(T&& value) : _value(std::move(value)) {}

        ~ObservableValue() override = default;

        /**
        * @returns the hold value.
        */
        T getValue() override {
            return _value;
        }

        /**
        * @returns the hold value.
        */
        T getValue() const override {
            return _value;
        }

        /**
        * Updates the value hold in this object.
        *
        * This function will invoke all the registered listeners.
        *
        * @param value the new value.
        */
        void setValue(const T& value) {
            _value = value;
            this->invoke(_value);
        }

        /**
        * Updates the value hold in this object.
        *
        * This function will invoke all the registered listeners.
        *
        * @param value the new value.
        */
        void setValue(T&& value) {
            _value = std::move(value);
            this->invoke(_value);
        }

        /**
        * Same as setValue().
        */
        ObservableValue& operator=(const T& other) {
            _value = std::move(other);
            this->invoke(_value);
            return *this;
        }

        /**
        * Same as setValue().
        */
        ObservableValue& operator=(T&& other) {
            _value = std::move(other);
            this->invoke(_value);
            return *this;
        }
    };
}
#endif //OBSERVABLEVALUE_H
