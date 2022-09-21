// Copyright (C) 2015-2017 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING
#include <csignal>
#endif
#include <vsomeip/vsomeip.hpp>
#include "hello_world_service.hpp"
#include "sample-ids.hpp"
/*
#ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING
hello_world_service *hw_srv_ptr(nullptr);
    void handle_signal(int _signal) {
        if (hw_srv_ptr != nullptr &&
                (_signal == SIGINT || _signal == SIGTERM))
            hw_srv_ptr->terminate();
    }
#endif
*/
#ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING
    service_sample *its_sample_ptr(nullptr);
    void handle_signal(int _signal) {
        if (its_sample_ptr != nullptr &&
                (_signal == SIGINT || _signal == SIGTERM))
            its_sample_ptr->stop();
    }
#endif

int main(int argc, char **argv)
{
/*
    (void)argc;
    (void)argv;
*/
    bool use_tcp = false;
    uint32_t cycle = 1000; // default 1s
/*
    hello_world_service hw_srv;
#ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING
    hw_srv_ptr = &hw_srv;
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);
#endif
    if (hw_srv.init()) {
        hw_srv.start();
        return 0;
    } else {
        return 1;
    }
 */  
 
     std::string tcp_enable("--tcp");
    std::string udp_enable("--udp");
    std::string cycle_arg("--cycle");

    for (int i = 1; i < argc; i++) {
        if (tcp_enable == argv[i]) {
            use_tcp = true;
            break;
        }
        if (udp_enable == argv[i]) {
            use_tcp = false;
            break;
        }

        if (cycle_arg == argv[i] && i + 1 < argc) {
            i++;
            std::stringstream converter;
            converter << argv[i];
            converter >> cycle;
        }
    } 
    service_sample its_sample(use_tcp, cycle);
#ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING
    its_sample_ptr = &its_sample;
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);
#endif
    if (its_sample.init()) {
        its_sample.start();
        return 0;
    } else {
        return 1;
    }
}
