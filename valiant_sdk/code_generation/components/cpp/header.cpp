#if !defined(VALIANT_STDLIB)
#define VALIANT_STDLIB

#include <cstdint>
#include <cstdlib>
#include <iostream>

namespace valiant
{
    class Value;

    enum ValueType
    {
        VALUE_TYPE_VOID         = 0b000,
        VALUE_TYPE_BOOLEAN      = 0b001,
        VALUE_TYPE_BYTE         = 0b010,
        VALUE_TYPE_POINTER      = 0b011,
        VALUE_TYPE_INTEGER      = 0b100,
        VALUE_TYPE_NUMBER       = 0b101,
        VALUE_TYPE_STRING       = 0b110,
        VALUE_TYPE_UNIT         = 0b111
    };

    typedef uint64_t RawValue;
    typedef bool RawBoolean;
    typedef uint8_t RawByte;
    typedef uint32_t RawInteger;
    typedef double RawNumber;
    typedef void * RawPointer;
    typedef std::string RawString;
    typedef size_t RawUnit;

    RawInteger cpu_get_bit_count();
    Value print();
    Value print(Value message);

    class Value
    {
    public:
        Value();
        Value(RawValue data, ValueType type);
        Value(RawBoolean data);
        Value(RawByte data);
        Value(RawInteger data);
        Value(RawNumber data);
        Value(RawPointer data);
        Value(RawString data);
        Value(RawUnit data);
        Value(const char *data);
        ~Value();
        operator RawBoolean();
        explicit operator RawByte();
        explicit operator RawInteger();
        operator RawNumber();
        operator RawPointer();
        operator RawString();
        explicit operator RawUnit();
        static Value get_unit();
        static Value get_void();
        RawValue get_data();
        RawString to_string();
        ValueType get_type();
    private:
        RawValue _data;
        ValueType _type;
    };
}

#endif
