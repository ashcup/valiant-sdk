#include <string>

#if !defined(VALIANT_STDLIB)

#include "header.cpp"

#endif

namespace valiant
{
    RawInteger cpu_get_bit_count()
    {
        if (sizeof(size_t) == sizeof(uint64_t))
        {
            return 64;
        }
        else if (sizeof(size_t) == sizeof(uint32_t))
        {
            return 32;
        }
        else if (sizeof(size_t) == sizeof(uint16_t))
        {
            return 16;
        }
        else if (sizeof(size_t) == sizeof(uint8_t))
        {
            return 8;
        }
    }

    Value print()
    {
        return Value::get_unit();
    }

    Value print(Value message)
    {
        std::cout << message.to_string() << std::endl;

        return Value::get_unit();
    }

    Value::Value(RawValue data, ValueType type)
    {
        this->_data = data;
        this->_type = type;
    }

    Value::Value() : Value(0, VALUE_TYPE_UNIT) {}

    Value::Value(RawBoolean data) : Value(data, VALUE_TYPE_BOOLEAN) {}

    Value::Value(RawByte data) : Value(data, VALUE_TYPE_BYTE) {}

    Value::Value(RawInteger data) : Value(data, VALUE_TYPE_INTEGER) {}

    Value::Value(RawNumber data) : Value(data, VALUE_TYPE_NUMBER) {}

    Value::Value(RawPointer data) : Value((RawValue)(data), VALUE_TYPE_POINTER) {}

    Value::Value(RawString data) : Value((RawValue)(new RawString(data)), VALUE_TYPE_STRING) {}

    Value::Value(const char *data) : Value(RawString(data)) {};

    Value Value::get_unit()
    {
        Value value;

        value._data = 0;
        value._type = VALUE_TYPE_UNIT;

        return value;
    }

    Value Value::get_void()
    {
        Value value;

        value._data = 0;
        value._type = VALUE_TYPE_VOID;

        return value;
    }

    Value::~Value()
    {
        if (this->get_type() == VALUE_TYPE_STRING)
        {
            delete (RawString *)(this->_data);
        }
    }

    Value::operator RawBoolean()
    {
        return (RawBoolean)(this->_data);
    }

    Value::operator RawByte()
    {
        return (RawByte)(this->_data);
    }

    Value::operator RawInteger()
    {
        return (RawInteger)(this->_data);
    }

    Value::operator RawNumber()
    {
        return (RawNumber)(this->_data);
    }

    Value::operator RawPointer()
    {
        return (RawPointer)(this->_data);
    }

    Value::operator RawString()
    {
        return *(RawString *)(this->_data);
    }

    Value::operator RawUnit()
    {
        return (RawUnit)(this->_data);
    }

    RawValue Value::get_data()
    {
        return this->_data;
    }

    RawString Value::to_string()
    {
        RawString error_string = RawString("<error>");

        ValueType type = this->get_type();

        if (type == VALUE_TYPE_STRING)
        {
            return *(RawString *)(this->_data);
        }
        else if (type == VALUE_TYPE_BOOLEAN)
        {
            return std::to_string((RawBoolean) this->_data);
        }
        else if (type == VALUE_TYPE_BYTE)
        {
            return std::to_string((RawByte) this->_data);
        }
        else if (type == VALUE_TYPE_INTEGER)
        {
            return std::to_string((RawInteger) this->_data);
        }
        else if (type == VALUE_TYPE_NUMBER)
        {
            return std::to_string((RawNumber) this->_data);
        }
        else if (type == VALUE_TYPE_UNIT)
        {
            return std::string("<Unit>");
        }
        else
        {
            RawInteger cpu_bit_count = cpu_get_bit_count();

            if (cpu_bit_count == 64)
            {
                return std::to_string((uint64_t) this->_data);
            }
            else if (cpu_bit_count == 32)
            {
                return std::to_string((uint32_t) this->_data);
            }
            else if (cpu_bit_count == 16)
            {
                return std::to_string((uint16_t) this->_data);
            }
            else if (cpu_bit_count == 8)
            {
                return std::to_string((uint8_t) this->_data);
            }
            else
            {
                return error_string;
            }
        }

        return error_string;
    }

    ValueType Value::get_type()
    {
        return this->_type;
    }
}
