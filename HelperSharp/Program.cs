using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

using Be;
using Grpc;
using Grpc.Core;
using Google.Protobuf;

namespace HelperSharp
{
    class Program
    {
        static void Main(string[] args)
        {
            Channel channel = new Channel("127.0.0.1:50051", ChannelCredentials.Insecure);

            var client = new Trading.TradingClient(channel);

            Random rand = new Random();

            UInt64 order_id = 0;

            for( int i = 0; i < 9999; i++ )
            {
                order_id++;
                UInt32 quantity = (UInt32)rand.Next(1, 1000);
                UInt32 price = rand.Next(0, 2) == 0 ? (UInt32)rand.Next(900, 1050) : (UInt32)rand.Next(1055, 1200);
                String OrderSide = rand.Next(0, 2) == 0 ? "B" : "A";
                String OrderType = "L";

                Console.WriteLine(OrderSide + OrderType);

                // generate quotes
                Quote request = new Quote();
                request.OrderSide = ByteString.CopyFrom(OrderSide, Encoding.Unicode);
                request.OrderType = ByteString.CopyFrom(OrderType, Encoding.Unicode);

                Order request_order = new Order();
                request_order.OrderId = order_id++;
                request_order.Price = price;
                request_order.Quantity = quantity;

                request.Order = request_order;

                var reply = client.QuoteUpdate(request);

                Thread.Sleep(100);
            }



            channel.ShutdownAsync().Wait();
            Console.WriteLine("Press any key to exit...");
            Console.ReadKey();
        }
    }
}
