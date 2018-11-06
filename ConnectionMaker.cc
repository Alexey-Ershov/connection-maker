#include "ConnectionMaker.hpp"

namespace runos {

REGISTER_APPLICATION(ConnectionMaker, {""})

void ConnectionMaker::init(Loader* loader, const Config& config)
{
    auto thread_num = 4;
    
    // TODO: if proxy will use handshake then we need to handle different
    // controller and switch versions.
    
    auto of_settings = fluid_base::OFServerSettings()
            .supported_version(fluid_msg::of13::OFP_VERSION)
            .liveness_check(false)
            .handshake(false)
            .dispatch_all_messages(true)
            .keep_data_ownership(false)
            .is_controller(false);

    client_ = std::make_unique<fluid_base::OFClient>(
            thread_num, of_settings);
    client_->start();

    Config of_server_conf = config_cd(config, "main-runos");
    std::string controller_ip = config_get(
            of_server_conf, "address", "0.0.0.0");
    int controller_port = config_get(
            of_server_conf, "port", 6653);

    // For checking testing controller use testing-controller-config.json
    addConnection(1, controller_ip, controller_port);
}

void ConnectionMaker::addConnection(int id,
                                    const std::string& address,
                                    int port)
{
    client_->add_connection(id, address, port);
}

} // namespace runos
