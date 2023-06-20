#ifndef Protocol_Profile_h__
#define Protocol_Profile_h__

#include "Common.h"

namespace Battlenet::Profile {
    using RecordId = uint64;

    using IntType = int64;
    using StringType = BSN::String<1023, 12>;
    using FloatType = double;
    using BinaryType = BSN::Blob<4096, 13>;
    using FieldPath = BSN::Blob<32, 6>;
    using CacheHandleType = BSN::Blob<40>;

    struct RecordAddress {
        Battlenet::Label Label;
        Battlenet::Profile::RecordId ID;
    };

    enum AccessLevel : uint8 {
        SYSTEM = 0xFF,
        OWNER  = 0x80,
        PUBLIC = 0x00
    }
}

#endif // Protocol_Profile_h__
