#include "ConnectionMaker.hpp"

#include <vector>

#include <unistd.h>

namespace runos {

REGISTER_APPLICATION(ConnectionMaker, {"switch-manager",
                                       ""})

void ConnectionMaker::init(Loader* loader, const Config& config)
{
    // TODO: if proxy will use handshake then we need to handle different
    // controller and switch versions.
    
    config_ = config;
    switch_manager_ = SwitchManager::get(loader);

    auto of_settings = fluid_base::OFServerSettings()
            .supported_version(fluid_msg::of13::OFP_VERSION)
            .liveness_check(false)
            .handshake(true)
            .dispatch_all_messages(true)
            .keep_data_ownership(false)
            .is_controller(false);

    auto thread_num = config_get(config_cd(config, "of-server"),
                                 "nthreads",
                                 4);

    client_ = std::make_unique<fluid_base::OFClient>(
            thread_num, of_settings);
    client_->start();    
}

void ConnectionMaker::startUp(Loader* loader)
{
    // For checking testing controller use testing-controller-config.json.
    addConnections();
}

void ConnectionMaker::addConnections()
{
    const auto& students_controllers = config_.at("students-controllers")
                                              .array_items();
    
    for (const auto& students_controller: students_controllers) {
        std::string controller_ip = students_controller.object_items()
                                                       .find("address")
                                                       ->second
                                                       .string_value();
        
        int controller_port = students_controller.object_items()
                                                 .find("port")
                                                 ->second
                                                 .int_value();

        std::vector<SwitchPtr> switches;
        do {
            int id = 0;
            switches = switch_manager_->switches();
            
            for (auto sw: switches) {
                client_->add_connection(id, controller_ip, controller_port);

                DLOG(INFO) << "Add connection with id = " << id;
                DLOG(INFO) << "controller_ip = " << controller_ip;
                DLOG(INFO) << "controller_port = " << controller_port;

                ++id;
            }

        } while (switches.empty());
    }
}

} // namespace runos
