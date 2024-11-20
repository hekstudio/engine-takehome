//
// Created by JIANG on 17/11/24.
//

#ifndef ENGINE_TAKEHOME_TIME_IN_FORCE_H
#define ENGINE_TAKEHOME_TIME_IN_FORCE_H

#include <string>

enum class TimeInForce {
    GTC,  // Good 'Til Canceled
    IOC,  // Immediate or Cancel
    FOK,  // Fill or Kill
    DAY,  // Day
    GTD,  // Good 'Til Date
    AON,  // All or None
    OPG,  // At the Opening
    CLS   // At the Close
};

#endif //ENGINE_TAKEHOME_TIME_IN_FORCE_H
