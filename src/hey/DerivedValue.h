//
// Created by gaeqs on 21/10/2024.
//

#ifndef DERIVEDVALUE_H
#define DERIVEDVALUE_H

namespace hey {
    /**
    * Represents a value that is derived from other values.
    *
    * The value of this object will change when any of its
    * observable values changes.
    */
    template<typename T, typename... D>
    class DerivedValue : public Value<T>, public Observable<T> {
        std::tuple<Listener<D>...> _listeners;
        std::tuple<const Value<D>*...> _values;
        std::function<T(D...)> _mapper;
        T _result;

        void refreshValue() {
            std::apply([this](const Value<D>*... args) {
                _result = _mapper(args->getValue()...);
                this->invoke(_result);
            }, _values);
        }

        template<typename V>
        Listener<V> asListener(const Value<V>& value) {
            auto* obs = dynamic_cast<const Observable<V>*>(&value);
            if (obs != nullptr) {
                return obs->createListener([this](const auto&) {
                    refreshValue();
                });
            }
            return Listener<V>();
        }

    public:
        /**
        * Creates a new derived value using the given sources and
        * the given map function.
        *
        * Every time any of the given sources changes, the map function
        * will be invoked using the data inside all sources.
        *
        * @param fun the map function.
        * @param sources the sources.
        */
        template<typename Fun>
        explicit DerivedValue(Fun fun, const Value<D>&... sources)
            : _listeners(std::make_tuple(asListener<D>(sources)...)),
              _values(&sources...),
              _mapper(fun) {
            refreshValue();
        }

        ~DerivedValue() override = default;

        /**
        * @returns the hold value.
        */
        T getValue() const override {
            return _result;
        }

        /**
        * @returns the hold value.
        */
        T getValue() override {
            return _result;
        }
    };
}

#endif //DERIVEDVALUE_H
