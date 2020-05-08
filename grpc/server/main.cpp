#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <chrono>
#include <map>

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <api/greet.grpc.pb.h>

using grpc::Server;
using grpc::Status;

// Logic and data behind the server's behavior.
class GreeterServiceImpl final : public greet::Greeter::Service {
  grpc::Status SayHello(grpc::ServerContext* context, const greet::HelloRequest* request,
                        greet::HelloReply* reply) override {

    std::string request_id{"none"};

    const auto client_meta = context->client_metadata();

    auto it = client_meta.find("request-id");

    if (it != std::end(client_meta)) {
      request_id = std::string(it->second.begin(), it->second.end());
    }

    logger_->info("Request received [{}] [id: {}]", request->name(), request_id);
    std::string prefix("Hello ");
    reply->set_message(prefix + request->name());
    std::this_thread::sleep_for(std::chrono::seconds(5));
    logger_->info("Request ended [id: {}]", request_id);
    return Status::OK;
  }

 private:
  std::shared_ptr<spdlog::logger> logger_ = spdlog::stdout_color_mt("console");
};

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  GreeterServiceImpl service;

  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  grpc::ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}

int main(int argc, char** argv) {
  RunServer();

  return 0;
}
