auto thread_num = 1;
// TODO: if proxy will use handshake then we need to handle different controller and switch versions
auto of_settings = fluid_base::OFServerSettings()
    .supported_version(fluid_msg::of10::OFP_VERSION)
    .supported_version(fluid_msg::of13::OFP_VERSION)
    .liveness_check(false)
    .handshake(false)
    .dispatch_all_messages(true)
    .keep_data_ownership(false);
auto client_settings = of_settings.is_controller(false);
auto server_settings = of_settings.is_controller(true);

client_ = std::make_unique<Client>(
    this, thread_num, client_settings
);

server_ = std::make_unique<Server>(
    this, settings_.proxy_address, settings_.proxy_port,
    thread_num, server_settings
);