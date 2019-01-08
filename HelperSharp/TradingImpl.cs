using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Be;
using Grpc;
using Grpc.Core;
using Google.Protobuf;

namespace HelperSharp
{
    class TradingImpl : Trading.TradingBase
    {
        // Server side handler of the SayHello RPC
        public override Task<Empty> QuoteUpdate(Quote request, ServerCallContext context)
        {
            return Task.FromResult( new Empty() );
        }

        //// Server side handler for the SayHelloAgain RPC
        //public override Task<HelloReply> SayHelloAgain(HelloRequest request, ServerCallContext context)
        //{
        //    return Task.FromResult(new HelloReply { Message = "Hello again " + request.Name });
        //}
    }
}
