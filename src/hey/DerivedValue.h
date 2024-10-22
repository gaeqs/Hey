//
// Created by gaeqs on 21/10/2024.
//

#ifndef DERIVEDVALUE_H
#define DERIVEDVALUE_H

namespace hey {
    template <typename T>
    class DerivedValue : public Value<T&>, public Observable<T> {



    };
}

#endif //DERIVEDVALUE_H
