# run on linux bash shell even windows

# PROTOBUF C++
protoc -I . --cpp_out=../OrderBook/src/protobuf ./Trading.proto

# GRPC C++
protoc -I . --grpc_out=../OrderBook/src/protobuf --plugin=protoc-gen-grpc=`which grpc_cpp_plugin.exe` ./Trading.proto

# PROTOBUF AND GRPC FOR CSHARP
protoc -I . --csharp_out=../HelperSharpGUI/protobuf --grpc_out ../HelperSharpGUI/protobuf Trading.proto --plugin=protoc-gen-grpc=`which grpc_csharp_plugin.exe`

# PROTOBUF AND GRPC FOR PYTHON
python -m grpc_tools.protoc -I . --python_out=. --grpc_python_out=../HelperScripts/ ./Service.proto

# PROTOBUF GOLANG
# protoc -I . --go_out=%userprofile%/go/src/be/orderbook ./Trading.proto
#protoc -I . --grpc_out=../OrderBook/src/protobuf --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` ./Service.proto

#
#protoc.exe --cpp_out=../OrderBook/src/protobuf ./Service.proto
#protoc -I ../proto --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` ./Service.proto



#protoc -I . --cpp_out=../OrderBook/src/protobuf ./Service.proto
#protoc -I . --grpc_out=../OrderBook/src/protobuf --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` ./Service.proto