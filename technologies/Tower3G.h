#pragma once
#include "technologies/NetworkTower.h"

/**
 * Tower3G
 * -------
 * 3G uses:
 *   - Total spectrum: 1000 kHz (1 MHz)
 *   - Channel width: 200 kHz
 *   - 32 users per channel (CDMA)
 *   - 1 antenna (no MIMO)
 *   - 10 messages per user (packet switching)
 */

class Tower3G : public NetworkTower {
public:
    Tower3G(basicIO& io)
        : NetworkTower(io, "3G", 1000, 200, 32, 10, 1) {}
};
