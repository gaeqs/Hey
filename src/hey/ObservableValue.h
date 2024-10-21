//
// Created by gaeqs on 21/10/24.
//

#ifndef OBSERVABLEVALUE_H
#define OBSERVABLEVALUE_H

namespace hey {
    template<typename Value>
    class ObservableValue : public Observable<Value> {
        Value _value;
    };
}
#endif //OBSERVABLEVALUE_H
