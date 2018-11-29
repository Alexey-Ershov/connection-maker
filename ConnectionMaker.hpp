#pragma once

#include "Application.hpp"
#include "Loader.hpp"
#include "Controller.hpp"
#include "SwitchManager.hpp"
#include <fluid/OFClient.hh>

#include <string>
#include <memory>

namespace runos {

class ConnectionMaker : public Application
{
    Q_OBJECT
    SIMPLE_APPLICATION(ConnectionMaker, "connection-maker")
public:
    void init(Loader* loader, const Config& config) override;
    void startUp(Loader* loader);
    void addConnections();

private:
    std::unique_ptr<fluid_base::OFClient> client_;
    Config config_;
    SwitchManager* switch_manager_;
};

} // namespace runos
