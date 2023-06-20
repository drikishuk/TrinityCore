#ifndef Protocol_Common_h__
#define Protocol_Common_h__

namespace Battlenet {
    using Region = uint8;

    struct FourCC {
        uint32 Value;
    };

    namespace Program {
        using Id = FourCC;
    }
}

#endif // Protocol_Common_h__
