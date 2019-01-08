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
    public partial class Form1 : Form
    {
        Channel channel;

        GenOrder gen_order = new GenOrder();

        public Form1()
        {
            InitializeComponent();
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

        private void BtnSetQuote_Click(object sender, EventArgs e)
        {
            channel = new Channel("127.0.0.1:50051", ChannelCredentials.Insecure);
            var client = new Trading.TradingClient(channel);

            for( int i = 0; i < 1; i++)
            {
                {
                    Quote request = gen_order.generate("B", "L", false);
                    var reply = client.QuoteUpdate(request);
                }
                {
                    Quote request = gen_order.generate("A", "L", false);
                    var reply = client.QuoteUpdate(request);
                }
                {
                    Quote request = gen_order.generate("B", "L", true);
                    var reply = client.QuoteUpdate(request);
                }
                {
                    Quote request = gen_order.generate("A", "L", true);
                    var reply = client.QuoteUpdate(request);
                }
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
    }
}
