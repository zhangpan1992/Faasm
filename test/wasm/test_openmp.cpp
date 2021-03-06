#include <catch/catch.hpp>

#include "utils.h"

#include <util/func.h>

namespace tests {
    TEST_CASE("Test static for scheduling", "[wasm]") {
        cleanSystem();
        message::Message msg = util::messageFactory("omp", "for_static_schedule");
        execFunction(msg);
    }

    TEST_CASE("Test OMP header API functions", "[wasm]") {
        cleanSystem();
        message::Message msg = util::messageFactory("omp", "header_api_support");
        execFunction(msg);
    }

    TEST_CASE("Test running OpenMP checks", "[wasm]") {
        cleanSystem();
        message::Message msg = util::messageFactory("omp", "omp_checks");
        execFunction(msg);
    }

    TEST_CASE("Test non-nested barrier pragma", "[wasm]") {
        cleanSystem();
        message::Message msg = util::messageFactory("omp", "simple_barrier");
        execFunction(msg);
    }

    TEST_CASE("Test basic omp parallel for pragma", "[wasm]") {
        cleanSystem();
        message::Message msg = util::messageFactory("omp", "simple_for");
        execFunction(msg);
    }

    TEST_CASE("Test non-nested master pragma", "[wasm]") {
        cleanSystem();
        message::Message msg = util::messageFactory("omp", "simple_master");
        execFunction(msg);
    }

    TEST_CASE("Test thread stack mapping", "[wasm]") {
        cleanSystem();
        message::Message msg = util::messageFactory("omp", "stack_debug");
        execFunction(msg);
    }
}