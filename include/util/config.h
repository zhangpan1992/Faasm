#pragma once

#include <string>

namespace util {
    std::string getHostName();

    const int DEFAULT_TIMEOUT = 60;
    const int RESULT_KEY_EXPIRY = 30;

    class SystemConfig {

    public:
        // System
        std::string hostType;
        std::string globalMessageBus;
        std::string functionStorage;
        std::string serialisation;
        std::string bucketName;
        std::string queueName;
        std::string cgroupMode;
        std::string netNsMode;
        std::string logLevel;
        std::string awsLogLevel;

        // Redis
        std::string redisStateHost;
        std::string redisQueueHost;
        std::string redisPort;

        // Scheduling
        int threadsPerWorker;
        int noScheduler;
        int prewarm;
        int maxQueueRatio;
        int maxWorkersPerFunction;

        // Worker-related timeouts
        int globalMessageTimeout;
        int unboundTimeout;
        int boundTimeout;

        // State
        int stateStaleThreshold;
        int stateClearThreshold;
        int statePushInterval;
        int fullAsync;

        SystemConfig();

        void print();

        void reset();

    private:
        int getSystemConfIntParam(const char *name, const char *defaultValue);

        void initialise();
    };

    SystemConfig &getSystemConfig();
}