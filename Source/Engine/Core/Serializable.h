#pragma once
#include <core/Json.h>
namespace claw {
    class Serializable {
    public:
        virtual ~Serializable() = default;

        virtual void Read(const json::value_t& value) = 0;
    };
}