#ifndef Battlenet_IP4_hpp__
#define Battlenet_IP4_hpp__

namespace Battlenet::IP4 {
    using Address = BSN::Blob<4>;
    using Port = BSN::Blob<2>;

    struct AddressPort final {
        Address Address;
        Port Port;
    };
}

#endif // Battlenet_IP4_hpp__
