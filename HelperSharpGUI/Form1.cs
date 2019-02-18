using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;


using Be;
using Grpc;
using Grpc.Core;
using Google.Protobuf;

namespace HelperSharpGUI
{
    enum ORDER_TYPE{ BIDS, ASKS } ;

    public partial class Form1 : Form
    {
        Dictionary<ulong, Quote> [] db = new Dictionary<ulong, Quote>[2]; // key : order_id

        List<Execution> executions = new List<Execution>();

        Channel channel;

        int order_id = 0;

        GenOrder gen_order = new GenOrder();

        public Form1()
        {
            InitializeComponent();

            db[(int)ORDER_TYPE.BIDS] = new Dictionary<ulong, Quote>();
            db[(int)ORDER_TYPE.ASKS] = new Dictionary<ulong, Quote>();
        }

        private void BtnGetOrderbook_Click(object sender, EventArgs e)
        {

            channel = new Channel("127.0.0.1:50051", ChannelCredentials.Insecure);
            var client = new Trading.TradingClient(channel);

            Empty empty = new Empty();
            var orderbook = client.OrderBookUpdate(empty);

            // debug
            ListBox lb_ask = (ListBox)this.Controls["ListBoxAsk"];
            ListBox lb_bid = (ListBox)this.Controls["ListBoxBid"];

            var asks_tree = orderbook.AskTree;
            if(asks_tree != null)
            {
                lb_ask.Items.Clear();
                var p_map = asks_tree.PriceMap;
                foreach (var ask in p_map)
                {
                    Console.WriteLine(ask.ToString());

                    lb_ask.Items.Add(ask.ToString());
                }
            }
            var bidss_tree = orderbook.BidTree;
            if (bidss_tree != null)
            {
                lb_bid.Items.Clear();
                var p_map = bidss_tree.PriceMap;
                foreach (var ask in p_map)
                {
                    Console.WriteLine(ask.ToString());

                    lb_bid.Items.Add(ask.ToString());
                }
            }
            /////////////////////////////////////


            channel.ShutdownAsync().Wait();
            Console.WriteLine("Press any key to exit...");
        }



        private void UpdateDB(MatchingResult mr)
        {
            foreach (var quote in mr.Quotes)
            {
                String order_side = quote.OrderSide.ToStringUtf8();

                int orderbook_kind = (order_side[0] == 'B') ? 0 : 1;

                if (quote.Order.Quantity == 0)
                {
                    db[orderbook_kind].Remove(quote.Order.OrderId);
                    continue;
                }

                Quote find_quote;

                if (db[orderbook_kind].TryGetValue((ulong)quote.Order.OrderId, out find_quote))
                {
                    find_quote.Order.Quantity = quote.Order.Quantity;
                }
                else
                {
                    db[orderbook_kind].Add(quote.Order.OrderId, quote);
                }
            }
            blBidDB.Items.Clear();
            foreach ( var quote in db[(int)ORDER_TYPE.BIDS].Values)
            {
                String text = String.Format("{0},{1},{2}", quote.Order.OrderId, quote.Order.Price, quote.Order.Quantity);
                blBidDB.Items.Add(text);
            }

            blAskDB.Items.Clear();
            foreach (var quote in db[(int)ORDER_TYPE.ASKS].Values)
            {
                String text = String.Format("{0},{1},{2}", quote.Order.OrderId, quote.Order.Price, quote.Order.Quantity);
                blAskDB.Items.Add(text);
            }



        }
        private void UpdateOrderBookStream(MatchingResult mr)
        {

            var orderbook = mr.Orderbook;

            // debug
            ListBox lb_ask = (ListBox)this.Controls["ListBoxAsk"];
            ListBox lb_bid = (ListBox)this.Controls["ListBoxBid"];

            lb_ask.Items.Clear();
            lb_bid.Items.Clear();

            var asks_tree = orderbook.AskTree;
            if (asks_tree != null)
            {
                lb_ask.Items.Clear();
                var p_map = asks_tree.PriceMap;
                foreach (var ask in p_map)
                {
                    Console.WriteLine(ask.ToString());

                    lb_ask.Items.Add(ask.ToString());
                }
            }
            var bidss_tree = orderbook.BidTree;
            if (bidss_tree != null)
            {
                lb_bid.Items.Clear();
                var p_map = bidss_tree.PriceMap;
                foreach (var ask in p_map)
                {
                    Console.WriteLine(ask.ToString());

                    lb_bid.Items.Add(ask.ToString());
                }
            }
        }
        private void BtnSetQuote_Click(object sender, EventArgs e)
        {
            channel = new Channel("127.0.0.1:50051", ChannelCredentials.Insecure);
            var client = new Trading.TradingClient(channel);

            for( int i = 0; i < 1; i++)
            {
                {
                    Quote request = gen_order.generate("A", "L", false);
                    var reply = client.QuoteUpdateSync(request);
                    UpdateDB(reply);
                    UpdateOrderBookStream(reply);
                }
                {
                    Quote request = gen_order.generate("B", "L", false);
                    var reply = client.QuoteUpdateSync(request);
                    UpdateDB(reply);
                    UpdateOrderBookStream(reply);
                }

                //{
                //    Quote request = gen_order.generate("A", "L", false);
                //    var reply = client.QuoteUpdateSync(request);
                //    ProcessResponse(reply);
                //}
                //{
                //    Quote request = gen_order.generate("B", "L", true);
                //    var reply = client.QuoteUpdateSync(request);
                //    ProcessResponse(reply);
                //}
                //{
                //    Quote request = gen_order.generate("A", "L", true);
                //    var reply = client.QuoteUpdateSync(request);
                //    ProcessResponse(reply);
                //}
            }




            channel.ShutdownAsync().Wait();
        }

        private void BtnStopQuote_Click(object sender, EventArgs e)
        {
            channel.ShutdownAsync().Wait();
        }

        private void BtnStopOrderbook_Click(object sender, EventArgs e)
        {

        }
        private global::Be.MatchingResult sendOrder(ulong price, uint quantity, int order_id, String order_side, String order_type = "L")
        {

            channel = new Channel("127.0.0.1:50051", ChannelCredentials.Insecure);
            var client = new Trading.TradingClient(channel);

            // generate quotes
            Quote request = new Quote();
            request.OrderSide = ByteString.CopyFrom(order_side, Encoding.Unicode);
            request.OrderType = ByteString.CopyFrom(order_type, Encoding.Unicode);

            Order request_order = new Order();
            request_order.OrderId = (ulong)order_id;
            request_order.Price = price;
            request_order.Quantity = quantity;

            request.Order = request_order;

            var reply = client.QuoteUpdateSync(request);
            UpdateDB(reply);
            UpdateOrderBookStream(reply);

            channel.ShutdownAsync().Wait();

            return reply;
        }
        private void btnSell_Click(object sender, EventArgs e)
        {
            int price = Convert.ToInt32(tbPrice.Text);
            int quantity = Convert.ToInt32(tbQuantity.Text);
            ++order_id;

            var reply = sendOrder((ulong)price, (uint)quantity, order_id, "AS");

            UpdateDB(reply);
            UpdateOrderBookStream(reply);
        }

        private void btnBuy_Click(object sender, EventArgs e)
        {
            int price = Convert.ToInt32(tbPrice.Text);
            int quantity = Convert.ToInt32(tbQuantity.Text);
            ++order_id;
            var reply = sendOrder((ulong)price, (uint)quantity, order_id, "B");

            UpdateDB(reply);
            UpdateOrderBookStream(reply);
        }
    }
}
