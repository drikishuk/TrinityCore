#ifndef Protocol_BaseTypes_h__
#define Protocol_BaseTypes_h__

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring> // std::memcpy
#include <functional>
#include <optional>
#include <utility>

#if __cpp_lib_span >= 20202L
# include <span>
# define BSN_SPAN_AVAILABLE
#endif

#if __has_include(<fmt/format.h>)
# include <fmt/format.h>
# define BSN_FORMAT(...) fmt::format(__VA_ARGS__)
#elif defined(__cpp_lib_format)
# include <format>
# define BSN_FORMAT(...) std::format(__VA_ARGS__)
#else
# define BSN_FORMAT(...)
#endif

namespace BSN {
    template <std::size_t N, std::size_t Bits>
    struct Blob final {
        constexpr std::size_t capacity() const noexcept { return N; }
        std::size_t size() const noexcept { return _size; }

#ifdef BSN_SPAN_AVAILABLE
        std::span<const std::byte> data() const noexcept { return std::span { _data, _data + _size }; }
#endif // BSN_SPAN_AVAILABLE

        std::string ToString() const noexcept {
            return BSN_FORMAT("Blob[Size: {}, Bits: {}, Capacity: {}]", size(), Bits, capacity());
        }

    private:
        std::size_t _size = 0;
        std::byte _data[N] = { };
    };

    template <typename T, std::size_t N, std::size_t Bits>
    struct DynArray final {
        DynArray() : _size(0), _storage(new T[N]) { }
        ~DynArray() {
            delete[] _storage;
            _storage = nullptr;

            _size = 0;
        }

        constexpr std::size_t capacity() const noexcept { return N; }
        std::size_t size() const noexcept { return _size; }

        T const& operator [] (std::size_t index) const {
            ASSERT(index < N);

            const_cast<DynArray*>(this)->_size = std::max(_size, index);
            return _storage[index];
        }

        T& operator [] (std::size_t index) {
            ASSERT(index < N);

            _size = std::max(_size, index);
            return _storage[index];
        }

    private:
        std::size_t _size = 0;
        T* _storage = nullptr;
    };

    template <typename T, std::size_t N, std::size_t Bits>
    struct ArrayLength final {
        constexpr std::size_t capacity() const noexcept { return N; }
        std::size_t size() const noexcept { return _size; }

        T const& operator [] (std::size_t index) const {
            ASSERT(index < N);

            const_cast<ArrayLength*>(this)>_size = std::max(_size, index);
            return _storage[index];
        }

        T& operator [] (std::size_t index) {
            ASSERT(index < N);

            _size = std::max(_size, index);
            return _storage[index];
        }

    private:
        std::size_t _size = 0;
        T _storage[N] = { };
    }

    template <typename T, std::size_t N, std::size_t Bits>
    using Array = std::conditional_t<
        (sizeof(T) * N > 0x4000uL),
        DynArray<T, N, Bits>,
        ArrayLength<T, N, Bits>
    >;

    // The actual definition of BSN::Choice is similary to a tagged union where the tag is an enumeration and each value is named. However,
    // this isn't possible with C++'s type system, so we choose to make BSN::Choice a namespace in which types are associated with enumeration
    // values through BSN::Choice::Of, and the overarching tagged union type becomes BSN::Choice::Choice<E, BSN::Choice::Of<E, T>...>.
    //
    // Furthermore, we can't use the enums underlying integer values when tagging the union, because gaps in the enum are possible. This
    // immediately rules out std::variant<...> as a suitable implementation (which has plenty other drawbacks anyways), so we are forced
    // to roll out our own implementation that reindexes. In that implementation, every tagged union can be set to an empty state, akin
    // to std::monostate, where the contents of the union are unspecified, and every accessor asserts that a value is actually stored in the union.
    namespace Choice {
        namespace dtl {
            using std::construct_at;
            // TODO: Pre-cpp20 destroy_at considers a program illformed (no diagnostic required, sic) if T is an array type.
            using std::destroy_at;

            template <auto E, std::size_t I, typename T>
            struct indexed_leaf { // Must be an empty type for EBO
                static_assert(std::is_default_constructible_v<T>, "Type must be default constructible");

                using enum_type = decltype(E);
                using value_type = T;

                static T& launder(std::byte* storage) { return *std::launder(reinterpret_cast<T*>(storage)); }
                static const T& launder(const std::byte* storage) { return *std::launder(reinterpret_cast<const T*>(storage)); }

                static void call(std::byte* storage, void* closure) {
                    auto pfn = reinterpret_cast<std::function<void(T&)>*>(closure);
                    return (*pfn)(launder(storage));
                }

                static void call(std::byte const* storage, void* closure) {
                    auto pfn = reinterpret_cast<std::function<void(T const&)>*>(closure);
                    return (*pfn)(launder(storage));
                }

                constexpr static const auto enum_value = E;
                constexpr static const std::size_t index = I; // Internal index, used to track monostate. Not sent to the client.
            };

            template <typename...> struct indexed_leaf_pack;

            template <auto... Es, std::size_t... Is, typename... Ts>
            struct indexed_leaf_pack<std::integer_sequence<std::common_type_t<decltype(Es)...>, Es...>, std::index_sequence<Is...>, Ts...>
                // +1 so that 0 is automatically monostate; private inheritance to abuse slicing for overload resolution
                : private indexed_leaf<Es, Is + 1, Ts>...
            {
                explicit indexed_leaf_pack() noexcept = default;
                virtual ~indexed_leaf_pack() noexcept { clear(); }

                using enum_type = std::common_type_t<decltype(Es)...>;

            private:
                template <std::size_t I, auto E, typename T> constexpr static auto select_base_for_index(indexed_leaf<E, I, T>* pack) { return pack; }
                template <std::size_t I>
                using base_for_index_t = std::remove_pointer_t<decltype(select_base_for_index<I + 1>(std::declval<indexed_leaf_pack*>()))>;

                constexpr static auto select_base_for_enum(...) = delete;
                template <auto E, std::size_t I, typename T> constexpr static auto select_base_for_enum(indexed_leaf<E, I, T>* pack) { return pack; }
                template <auto E> using base_for_enum_t = std::remove_pointer_t<decltype(select_base_for_enum<E>(std::declval<indexed_leaf_pack*>()))>;

                constexpr static auto select_base_for_type(...) = delete;
                template <auto E, std::size_t I, typename T> constexpr static auto select_base_for_type(indexed_leaf<E, I, T>* pack) { return pack; }
                template <typename T> using base_for_type_t = std::remove_pointer_t<decltype(select_base_for_type<T>(std::declval<indexed_leaf_pack*>()))>;

            public:
                /**
                 * Returns a cv-qualified ref to the value held for a given enumeration value.
                 *
                 * If the object currently held does not match the expected type, this function asserts.
                 */
                template <auto E>
                auto get() const -> typename base_for_enum_t<E>::value_type const& {
                    using base_for_enum = base_for_enum_t<E>;
                    ASSERT(base_for_enum::index == _index && "runtime type does not match for this BSN::Choice");

                    return *as_pointer<typename base_for_enum::value_type>(_storage);
                }

                /**
                 * Returns a mutable reference to the value held for a given enumeration value.
                 *
                 * If the object currently held does not match the expected type, this function asserts.                
                 */
                template <auto E>
                auto get() -> typename base_for_enum_t<E>::value_type& {
                    using base_for_enum = base_for_enum_t<E>;
                    ASSERT(base_for_enum::index == _index);

                    return *as_pointer<typename base_for_enum::value_type>(_storage);
                }

                /**
                 * Constructs a value in-place using the given arguments.
                 *
                 * @param[in] ...args A pack of arguments to be forwarded to the correct type's constructor.
                 */
                template <auto E, typename... Us, typename = std::enable_if_t<
                    std::is_constructible_v<typename base_for_enum_t<E>::value_type, Us...>
                >>
                void emplace(Us&&... args) {
                    // Destruct the previous value if it exists
                    clear();

                    using base_for_enum = base_for_enum_t<E>;

                    _index = base_for_enum::index;
                    dtl::construct_at(as_pointer<typename base_for_enum::value_type>(), std::forward<Us>(args)...);
                }

                /**
                 * Default-constructs the alternative value associated with the given tag into this union.
                 * 
                 * @param[in] tag The tag identifying the type to start holding.
                 */
                void set(enum_type tag) {
                    std::size_t index = ((tag == Es ? Is + 1 : 0) + ... + 0);
                    if (index != 0) {
                        clear();

                        _index = index;

                        using erased_ctor_t = void(*)(void*);
                        erased_ctor_t erased_ctors[] = {
                            [](void* storage) {
                                // Default-construct
                                dtl::construct_at(std::launder(reinterpret_cast<Ts*>(storage)));
                            }...
                        };
                        erased_ctors[_index - 1](_storage);
                    }
                }

                /**
                 * Returns true if a value is currently held.
                 */
                bool has_value() const noexcept { return _index != 0; }

                /**
                 * Sets this object to an empty alternative state.
                 */
                void clear() noexcept {
                    if (!has_value())
                        return;

                    auto _ = ((_index == Is + 1 ? (dtl::destroy_at(as_pointer<Ts>()), true) : false) || ...);
                    _index = 0;
                }

                /**
                 * Returns the enumeration associated with the value currently held.
                 *
                 * If no value is held, this function asserts.
                 */
                auto index() const noexcept -> enum_type {
                    ASSERT(has_value() && "Empty BSN::Choice");

                    constexpr static const enum_type values[] = { Es... };
                    return values[_index - 1];
                }

                /**
                 * Implements the visitor pattern on this type.
                 *
                 * @param[in] ...visitors A variadic pack of visitors, one for each of the possibly stored type, in the order they are declared
                 *                        on this type.
                 */
                void visit(std::function<void(Ts&)>... visitors) {
                    // TODO: Is there any way to drop std::function in favor of more lightweight function_ref-like types somehow?

                    ASSERT(has_value() && "empty BSN::Choice");

                    void* vs[] = { std::addressof(visitors)... };
                    using dispatch_type = void(*)(std::byte*, void*);
                    dispatch_type dispatches[] = { static_cast<dispatch_type>(&indexed_leaf<Es, Is + 1, Ts>::call)... };

                    dispatches[_index - 1](_storage, vs[_index - 1]);
                }

                /**
                 * Implements the visitor pattern on this type.
                 *
                 * @param[in] ...visitors A variadic pack of visitors, one for each of the possibly stored type, in the order they are declared
                 *                        on this type.
                 */
                void visit(std::function<void(const Ts&)>... visitors) const {
                    // TODO: Is there any way to drop std::function in favor of more lightweight function_ref-like types somehow?

                    ASSERT(has_value() && "empty BSN::Choice");

                    void* vs[] = { std::addressof(visitors)... };
                    using dispatch_type = void(*)(std::byte const*, void*);
                    dispatch_type dispatches[] = { static_cast<dispatch_type>(&indexed_leaf<Es, Is + 1, Ts>::call)... };

                    dispatches[_index - 1](_storage, vs[_index - 1]);
                }
                
            private:
                // Utility that launders the storage to a pointer.
                template <typename U>
                U* as_pointer() noexcept {
                    return std::launder(reinterpret_cast<U*>(_storage));
                }

                std::size_t _index = 0;
                alignas(std::max({ alignof(Ts)... })) std::byte _storage[std::max({ sizeof(Ts)... })] = { };
            };

            template <typename E, typename... Ts> struct make_indexed_leaf_pack final {
                using type = indexed_leaf_pack<E, std::make_index_sequence<sizeof...(Ts)>, Ts...>;
            };
        }

        template <auto E, typename T>
        struct Of final{
            constexpr static const auto enum_value = E;
            using enum_type = decltype(E);

            using value_type = T;
        };

        template <typename Enum, std::size_t TagBits, typename... Ts>
        class Choice final : private dtl::make_indexed_leaf_pack<
            std::integer_sequence<Enum, Ts::enum_value...>,
            typename Ts::value_type...
        >::type  {
            using base_t = typename dtl::make_indexed_leaf_pack<
                std::integer_sequence<Enum, Ts::enum_value...>,
                typename Ts::value_type...
            >::type;

            static_assert((std::is_same_v<Enum, typename Ts::enum_type> && ...));

        public:
            
            using base_t::index;
            using base_t::get;
            using base_t::set;
            using base_t::emplace;
            using base_t::clear;
            using base_t::visit;
        };
    }

    template <std::size_t Length, std::size_t Bits, std::size_t BaseLength = 0>
    struct AsciiString {
        // ASCII String.
        std::size_t _size;
        char _storage[Length];
    };

    template <std::size_t Length, std::size_t Bits, std::size_t BaseLength = 0 /* in bytes */>
    struct String {
        // UTF8 String
        std::size_t _size; // Not sure if in characters or bytes; probably characters? Need more decomp
        char _storage[Length * 4 + 1] = { };
    };

    template <typename T>
    using Optional = std::optional<T>;
}

#undef BSN_SPAN_AVAILABLE
#undef BSN_FORMAT

#endif // Protocol_BaseTypes_h__
