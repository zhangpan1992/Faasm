#include "ZygoteRegistry.h"

#include <util/locks.h>
#include <util/func.h>
#include <util/config.h>
#include <sys/mman.h>

namespace zygote {
    ZygoteRegistry &getZygoteRegistry() {
        static ZygoteRegistry r;
        return r;
    }

    size_t ZygoteRegistry::getTotalZygoteCount() {
        return zygoteMap.size();
    }

    int ZygoteRegistry::getZygoteCount(const std::string &key) {
        util::SharedLock lock(mx);
        int count = zygoteMap.count(key);
        return count;
    }

    std::string ZygoteRegistry::getZygoteKey(const message::Message &msg) {
        std::string key = msg.user() + "/" + msg.function();
        return key;
    }

    wasm::WasmModule &ZygoteRegistry::getZygote(const message::Message &msg) {
        const std::shared_ptr<spdlog::logger> &logger = util::getLogger();
        const std::string key = getZygoteKey(msg);

        if (getZygoteCount(key) == 0) {
            util::FullLock lock(mx);
            if (zygoteMap.count(key) == 0) {
                logger->debug("Creating new zygote for {}", key);
                // Instantiate the module
                wasm::WasmModule &module = zygoteMap[key];

                // Bind to the function
                module.bindToFunction(msg);

                // Write memory to fd
                int fd = memfd_create(key.c_str(), 0);
                module.writeMemoryToFd(fd);
            } else {
                logger->debug("Using cached zygote for {}", key);
            }
        } else {
            logger->debug("Using cached zygote for {}", key);
        }

        return zygoteMap[key];
    }

    void ZygoteRegistry::clear() {
        zygoteMap.clear();
    }
}