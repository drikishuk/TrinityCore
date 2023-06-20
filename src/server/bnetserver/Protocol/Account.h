#ifndef Protocol_Account_h__
#define Protocol_Account_h__

#include "BaseTypes.h"

namespace Battlenet::Account {
    using Id = uint32;
    using PasswordScheme = uint8; // 8 bits

    enum PasswordSchemeEnum : uint8 { // 7 bits
        PASSWORD_OLYMPUS       = 0, // 0x0
        MIN_WEB_RESERVED_1     = 1, // 0x1
        MAX_WEB_RESERVED_1     = 10, // 0xa
        PASSWORD_WOW           = 11, // 0xb
        PASSWORD_RESET         = 12, // 0xc
        MOBILE_TOKEN           = 13, // 0xd
        THE9_VASCO_DIGIPASS    = 14, // 0xe
        VIRTUAL_KEYPAD         = 15, // 0xf
        MATRIX_CARD            = 16, // 0x10
        PASSWORD_OLYMPUS_DEVELOPMENT = 17, // 0x11
        BLIZZARD_AUTHENTICATOR = 18, // 0x12
        COOKIE                 = 19, // 0x13
        NETEASE_TOKEN          = 20, // 0x14
        MATRIX_CARD_NETEASE    = 21, // 0x15
        NETEASE_E_TOKEN        = 22, // 0x16
        PHONE_SECURE           = 23, // 0x17
        PHONE_LOCK             = 24, // 0x18
        AUTHENTICATOR_BYPASS   = 25, // 0x19
        AUTHENTICATOR_BYPASS_CONTROL = 26, // 0x1a
        MIN_WEB_RESERVED_2     = 30, // 0x1e
        MAX_WEB_RESERVED_2     = 49, // 0x31
        MIN_AGREEMENT_HANDLER  = 50, // 0x32
        TOS_ACCEPTANCE_BNET    = 50, // 0x32
        TOS_ACCEPTANCE_WOW     = 51, // 0x33
        TOS_ACCEPTANCE_S2      = 52, // 0x34
        TOS_ACCEPTANCE_D3      = 53, // 0x35
        TOS_ACCEPTANCE_AURORA  = 54, // 0x36
        EULA_ACCEPTANCE_BNET   = 70, // 0x46
        EULA_ACCEPTANCE_WOW    = 71, // 0x47
        EULA_ACCEPTANCE_S2     = 72, // 0x48
        EULA_ACCEPTANCE_D3     = 73, // 0x49
        EULA_ACCEPTANCE_AURORA = 74, // 0x4a
        RMAH_ACCEPTANCE_D3     = 80, // 0x50
        MAX_AGREEMENT_HANDLER  = 89, // 0x59
    }

    enum class Flags : uint64 {
        FLAG_INCOMPLETE                                = 0x00000001,
        FLAG_MAIL_VERIFIED                             = 0x00000002,
        FLAG_EMPLOYEE                                  = 0x00000004,
        FLAG_ADMIN                                     = 0x00000008,
        FLAG_SUPPORT_EMPLOYEE                          = 0x00000010,
        FLAG_NEWSLETTER                                = 0x00000020,
        FLAG_PARENT_AGREEMENT_KR                       = 0x00000040,
        FLAG_INSIDER_SMS_KR                            = 0x00000080,
        FLAG_CANCELLED_KR                              = 0x00000100,
        FLAG_BETA_SIGN_UP                              = 0x00000200,
        FLAG_PURCHASE_BAN                              = 0x00000400,
        FLAG_LEGAL_ACCEPT                              = 0x00000800,
        FLAG_PRESS                                     = 0x00001000,
        FLAG_ONE_TIME_EVENT                            = 0x00002000,
        FLAG_TRIAL_INCOMPLETE                          = 0x00004000,
        FLAG_MARKETING_EMAIL                           = 0x00008000,
        FLAG_KR_AGE_NOT_VERIFIED                       = 0x00010000,
        FLAG_SEC_LOCK_MUST_RELEASE                     = 0x00020000,
        FLAG_SEC_LOCKED                                = 0x00040000,
        FLAG_RID_DISABLED                              = 0x00080000,
        FLAG_DONT_SHOW_TO_DIRECT_FRIEND                = 0x00100000,
        FLAG_PARENTAL_CONTROL                          = 0x00200000,
        FLAG_PARENT_AGREE_14_KR                        = 0x00400000,
        FLAG_PLAY_SUMMARY_EMAIL                        = 0x00800000,
        FLAG_PRIV_NETWORK_RQD                          = 0x01000000,
        FLAG_PRIMARY_RID_INVITE_REQUIRES_EMPLOYEE_FLAG = 0x02000000,
        FLAG_VOICE_CHAT_DISABLED                       = 0x04000000,
        FLAG_VOICE_SPEAK_DISABLED                      = 0x08000000,
        FLAG_HIDE_FROM_FACEBOOK_FRIEND_FINDER          = 0x10000000,
        FLAG_EU_FORBID_ELV                             = 0x20000000,
        FLAG_PHONE_SECURE_ENHANCED                     = 0x40000000,
    }

    enum LocalFlags { // 0bits ?!
        BATTLESECURE_NO_FRAUD_HANDLING = 0x00000001
    }

    enum MarketingFlags : uint64 {
        SOR2_ELIGIBLE = 0x00000001
    }

    using NamePart = BSN::String<32, 8>;
    using Nickname = BSN::String<27, 7>;

    using Mail = BSN::AsciiString<320, 9, 3>;
    using Password = BSN::AsciiString<16, 4, 3>;
    using CAISIdentity = BSN::AsciiString<18, 5, 0>;

    using PasswordData = BSN::Blob<512, 10>;

    using AuthenticatorBypassKey = BSN::Blob<16, 0>;
    using CookieClientId = BSN::Blob<8, 4>;
    using CookieData = BSN::Blob<32, 6>;

    struct FullName final {
        NamePart GivenName;
        NamePart SurName;
    };

    struct Credential final {
        uint8 Scheme; // 0-255, 8 bits
        PasswordData Data;
    };
}

#endif // Protocol_Account_h__