#ifndef Protocol_Toon_h__
#define Protocol_Toon_h__

#include "BaseTypes.h"
#include "Common.h"
#include "Profile.h"

namespace Battlenet::Toon {
    using Name = BSN::String<25, 7, 2>;
    using NameTag = BSN::String<6, 5>;
    using DisplayName = BSN::String<12, 6, 2>;
    using NameRestriction = BSN::String<1024, 13>;
    using Keyword = BSN::String<12, 6, 3>;

    using Flags = uint32;
    using Id = uint64;
    using DisplayVersion = uint32;

    struct Handle final {
        Battlenet::Region Region;
        Battlenet::Program::Id ProgramID;
        Battlenet::Realm::Id RealmID;
        Battlenet::Toon::Id ID;
    };

    struct FullName final {
        Battlenet::Region Region;
        Battlenet::Program::Id ProgramID;
        Battlenet::Realm::Id RealmID;
        Battlenet::Toon::Name Name;
    };

    struct Info final {
        Battlenet::Toon::Handle Handle;
        Battlenet::Toon::Name Name;
    };

    struct Display final {
        Battlenet::Toon::Name Name;
        Battlenet::Realm RealmID;
        Battlenet::Profile::RecordAddress Profile;
    };

    enum Flags : uint32 {
        FLAG_SQUELCHED = 1,
        FLAG_DELETED   = 2,
        FLAG_BANNED    = 4,
        FLAG_RENAME    = 8,
    }
}

#endif // Protocol_Toon_h__
