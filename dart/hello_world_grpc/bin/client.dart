// Copyright (c) 2018, the gRPC project authors. Please see the AUTHORS file
// for details. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/// Dart implementation of the gRPC helloworld.Greeter client.
import 'package:grpc/grpc.dart';

import 'package:helloworld/src/generated/helloworld.pb.dart';
import 'package:helloworld/src/generated/helloworld.pbgrpc.dart';

import 'package:helloworld/src/generated/helloworld2.pb.dart' as greet2;
import 'package:helloworld/src/generated/helloworld2.pbgrpc.dart' as greet2;

enum SrvType {
  GreeterOne,
  GreeterTwo
}

SrvType getSrvType(String arg) {
  final converter = { 'one': SrvType.GreeterOne, 'two': SrvType.GreeterTwo};
  return converter[arg];
}

Future<void> main(List<String> args) async {
  final channel = ClientChannel(
    'localhost',
    port: 50051,
    options: const ChannelOptions(credentials: ChannelCredentials.insecure()),
  );
  
  var name = 'World';
  var srv_type = SrvType.GreeterOne;

  if (args.isNotEmpty) { 
    name = args[0];
    if (args.length > 1) {
      srv_type = getSrvType(args[1]);
    }
  }

  
  try {

    if (srv_type == SrvType.GreeterOne) {
      final stub = GreeterClient(channel);
      final response = await stub.sayHello(HelloRequest()..name = name);
      print('Greeter client received: ${response.message}');
    } else {
      final stub = greet2.GreeterClient(channel);
      final response = await stub.sayHello(greet2.HelloRequest()..name = name);
      print('Greeter 2 client received: ${response.message}');
    }

  } catch (e) {
    print('Caught error: $e');
  }
  await channel.shutdown();
}
