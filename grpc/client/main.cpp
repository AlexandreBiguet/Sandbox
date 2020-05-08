#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#include <api/greet.grpc.pb.h>

namespace {

class GreeterClient {
 public:
  GreeterClient(std::shared_ptr<grpc::Channel> channel) : stub_(greet::Greeter::NewStub(channel)) {}

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  std::string SayHello(const std::string &user) {
    // Data we are sending to the server.
    greet::HelloRequest request;
    request.set_name(user);

    // Container for the data we expect from the server.
    greet::HelloReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    grpc::ClientContext context;
    std::size_t request_id{0};
    context.AddMetadata("request-id", std::to_string(request_id));// std::to_string(request_id));

    // The actual RPC.
    grpc::Status status = stub_->SayHello(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      return reply.message();
    } else {
      std::cout << status.error_code() << ": " << status.error_message() << std::endl;
      return "RPC failed";
    }
  }

 private:
  std::unique_ptr<greet::Greeter::Stub> stub_;
};  // namespace

}  // namespace

int main() {
  const std::string target{"localhost:50051"};

  GreeterClient greeter(grpc::CreateChannel(target, grpc::InsecureChannelCredentials()));
  std::string user("world");
  std::string reply = greeter.SayHello(user);
  std::cout << "Greeter received: " << reply << std::endl;

  return EXIT_SUCCESS;
}
