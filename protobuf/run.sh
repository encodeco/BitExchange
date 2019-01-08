# PROTOBUF C++
protoc -I . --cpp_out=../OrderBook/src/protobuf ./Trading.proto
# PROTOBUF GOLANG
protoc -I . --go_out=%userprofile%/go/src/be/orderbook ./Trading.proto

# PROTOBUF C++
protoc -I . --grpc_out=../OrderBook/src/protobuf --plugin=protoc-gen-grpc=`which grpc_cpp_plugin.exe` ./Trading.proto
# PROTOBUF GOLANG




python -m grpc_tools.protoc -I . --python_out=. --grpc_python_out=../HelperScripts/ ./Service.proto

#protoc -I . --grpc_out=../OrderBook/src/protobuf --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` ./Service.proto

#
#protoc.exe --cpp_out=../OrderBook/src/protobuf ./Service.proto
#protoc -I ../proto --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` ./Service.proto



#protoc -I . --cpp_out=../OrderBook/src/protobuf ./Service.proto
#protoc -I . --grpc_out=../OrderBook/src/protobuf --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` ./Service.proto