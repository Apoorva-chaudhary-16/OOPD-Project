#pragma once
#include "technologies/NetworkTower.h"

/**
 * Tower2G
 * -------
 * 2G uses:
 *   - 1 MHz = 1000 kHz total spectrum
 *   - Channel width = 200 kHz
 *   - 16 users per channel (TDMA)
 *   - 1 antenna (no MIMO)
 *   - Messages per user: 20 (5 data + 15 voice)
 */

class Tower2G : public NetworkTower {
public:
    Tower2G(basicIO& io)
        : NetworkTower(io, "2G", 1000, 200, 16, 20, 1) {}
};
