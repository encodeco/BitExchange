import grpc

import Service_pb2
import Service_pb2_grpc

def run():
    with grpc.insecure_channel('localhost:50051') as channel:
        stub = Service_pb2_grpc.TradingStub(channel)
        newQuote = Service_pb2.Quote()
        
        stub.QuoteUpdate( newQuote )
        #stub.Update( Service_pb2.NumSteps(n=5) )
        #res = stub.GetPosition(Service_pb2.Empty())
        #print(res.x)

if __name__ == '__main__':
    run()
