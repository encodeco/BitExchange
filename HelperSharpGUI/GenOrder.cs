using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Be;
using Grpc;
using Grpc.Core;
using Google.Protobuf;

namespace HelperSharpGUI
{
    class GenOrder
    {
        int order_id = 1;
        public Quote generate( String order_side, String order_type, bool cross = false )
        {
            Random rand = new Random();

            UInt32 quantity = (UInt32)rand.Next(1, 1000);
            UInt32 price = 0;

            if (order_side == "B" && cross == false)
            {
                price = (UInt32)rand.Next(900, 1050);
            }
            if (order_side == "A" && cross == false)
            {
                price = (UInt32)rand.Next(1055, 1200);
            }

            if (order_side == "B" && cross == true)
            {
                price = (UInt32)rand.Next(1055, 1200);
            }
            if (order_side == "A" && cross == true)
            {
                price = (UInt32)rand.Next(900, 1050);
            }

            // generate quotes
            Quote request = new Quote();
            request.OrderSide = ByteString.CopyFrom(order_side, Encoding.Unicode);
            request.OrderType = ByteString.CopyFrom(order_type, Encoding.Unicode);

            Order request_order = new Order();
            request_order.OrderId = (ulong)order_id;
            request_order.Price = price;
            request_order.Quantity = quantity;

            request.Order = request_order;

            order_id++;

            return request;
        }
    }
}
