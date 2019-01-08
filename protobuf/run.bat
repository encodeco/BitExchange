protoc.exe -I . --cpp_out=..\OrderBook/src/protobuf .\Service.proto
protoc.exe -I . --grpc_out=..\OrderBook/src/protobuf --plugin=protoc-gen-grpc="C:\Dev\vcpkg\packages\grpc_x86-windows\tools\grpc\grpc_cpp_plugin.exe" .\Service.proto

