#include <memory>

#include "pipeline/RedisPipelineBootstrap.h"
#include "ratelimit/RateLimitHandler.h"

namespace ratelimit {

static pipeline::RedisPipelineBootstrap::Config config{
  redisHandlerFactory: [](const pipeline::RedisPipelineBootstrap::OptionalComponents& optionalComponents) {
    std::shared_ptr<pipeline::RedisHandler> handler = std::make_shared<RateLimitHandler>(
        optionalComponents.databaseManager);
    return handler;
  },

  kafkaTailerFactory: nullptr,

  databaseManagerFactory: nullptr,

  scheduledTaskQueueFactory: nullptr,

  rocksDbConfiguratorMap: {
    {
      pipeline::RedisPipelineBootstrap::defaultColumnFamilyName(),
      RateLimitHandler::optimizeColumnFamily,
    },
  },
};

static auto redisPipelineBootstrap = pipeline::RedisPipelineBootstrap::create(config);

}  // namespace ratelimit
