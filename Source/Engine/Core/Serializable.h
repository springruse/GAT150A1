#pragma once
#include <core/Json.h>
namespace claw {
    class ISerializable {
    public:
        virtual ~ISerializable() = default;

        virtual void Read(const json::value_t& value) = 0;
    };
}