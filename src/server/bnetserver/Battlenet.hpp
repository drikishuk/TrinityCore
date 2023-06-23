#ifndef Battlenet_hpp__
#define Battlenet_hpp__

namespace Battlenet {
    struct Header final {
        uint8 Command = 0;
        BSN::Optional<uint8> Channel;
    };
}

#endif // Battlenet_hpp__
