namespace HelperSharpGUI
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.BtnGetOrderbook = new System.Windows.Forms.Button();
            this.BtnSetQuote = new System.Windows.Forms.Button();
            this.ListBoxAsk = new System.Windows.Forms.ListBox();
            this.ListBoxBid = new System.Windows.Forms.ListBox();
            this.BtnStopOrderbook = new System.Windows.Forms.Button();
            this.BtnStopQuote = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.tbPrice = new System.Windows.Forms.TextBox();
            this.tbQuantity = new System.Windows.Forms.TextBox();
            this.btnSell = new System.Windows.Forms.Button();
            this.btnBuy = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.blBidDB = new System.Windows.Forms.ListBox();
            this.blAskDB = new System.Windows.Forms.ListBox();
            this.SuspendLayout();
            // 
            // BtnGetOrderbook
            // 
            this.BtnGetOrderbook.Location = new System.Drawing.Point(82, 91);
            this.BtnGetOrderbook.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.BtnGetOrderbook.Name = "BtnGetOrderbook";
            this.BtnGetOrderbook.Size = new System.Drawing.Size(168, 35);
            this.BtnGetOrderbook.TabIndex = 0;
            this.BtnGetOrderbook.Text = "GetOrderbook";
            this.BtnGetOrderbook.UseVisualStyleBackColor = true;
            this.BtnGetOrderbook.Click += new System.EventHandler(this.BtnGetOrderbook_Click);
            // 
            // BtnSetQuote
            // 
            this.BtnSetQuote.Location = new System.Drawing.Point(82, 46);
            this.BtnSetQuote.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.BtnSetQuote.Name = "BtnSetQuote";
            this.BtnSetQuote.Size = new System.Drawing.Size(168, 35);
            this.BtnSetQuote.TabIndex = 1;
            this.BtnSetQuote.Text = "SetQuote";
            this.BtnSetQuote.UseVisualStyleBackColor = true;
            this.BtnSetQuote.Click += new System.EventHandler(this.BtnSetQuote_Click);
            // 
            // ListBoxAsk
            // 
            this.ListBoxAsk.FormattingEnabled = true;
            this.ListBoxAsk.ItemHeight = 20;
            this.ListBoxAsk.Location = new System.Drawing.Point(1196, 46);
            this.ListBoxAsk.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.ListBoxAsk.Name = "ListBoxAsk";
            this.ListBoxAsk.Size = new System.Drawing.Size(217, 264);
            this.ListBoxAsk.TabIndex = 4;
            // 
            // ListBoxBid
            // 
            this.ListBoxBid.FormattingEnabled = true;
            this.ListBoxBid.ItemHeight = 20;
            this.ListBoxBid.Location = new System.Drawing.Point(1196, 389);
            this.ListBoxBid.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.ListBoxBid.Name = "ListBoxBid";
            this.ListBoxBid.Size = new System.Drawing.Size(217, 264);
            this.ListBoxBid.TabIndex = 5;
            // 
            // BtnStopOrderbook
            // 
            this.BtnStopOrderbook.Location = new System.Drawing.Point(278, 91);
            this.BtnStopOrderbook.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.BtnStopOrderbook.Name = "BtnStopOrderbook";
            this.BtnStopOrderbook.Size = new System.Drawing.Size(168, 35);
            this.BtnStopOrderbook.TabIndex = 3;
            this.BtnStopOrderbook.Text = "StopOrderbook";
            this.BtnStopOrderbook.UseVisualStyleBackColor = true;
            this.BtnStopOrderbook.Click += new System.EventHandler(this.BtnStopOrderbook_Click);
            // 
            // BtnStopQuote
            // 
            this.BtnStopQuote.Location = new System.Drawing.Point(278, 46);
            this.BtnStopQuote.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.BtnStopQuote.Name = "BtnStopQuote";
            this.BtnStopQuote.Size = new System.Drawing.Size(168, 35);
            this.BtnStopQuote.TabIndex = 2;
            this.BtnStopQuote.Text = "StopQuote";
            this.BtnStopQuote.UseVisualStyleBackColor = true;
            this.BtnStopQuote.Click += new System.EventHandler(this.BtnStopQuote_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(1196, 13);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(36, 20);
            this.label1.TabIndex = 6;
            this.label1.Text = "Ask";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(1196, 353);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(32, 20);
            this.label2.TabIndex = 7;
            this.label2.Text = "Bid";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(82, 260);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(43, 20);
            this.label3.TabIndex = 8;
            this.label3.Text = "price";
            // 
            // tbPrice
            // 
            this.tbPrice.Location = new System.Drawing.Point(86, 283);
            this.tbPrice.Name = "tbPrice";
            this.tbPrice.Size = new System.Drawing.Size(100, 26);
            this.tbPrice.TabIndex = 9;
            // 
            // tbQuantity
            // 
            this.tbQuantity.Location = new System.Drawing.Point(211, 284);
            this.tbQuantity.Name = "tbQuantity";
            this.tbQuantity.Size = new System.Drawing.Size(100, 26);
            this.tbQuantity.TabIndex = 10;
            // 
            // btnSell
            // 
            this.btnSell.Location = new System.Drawing.Point(374, 253);
            this.btnSell.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.btnSell.Name = "btnSell";
            this.btnSell.Size = new System.Drawing.Size(168, 35);
            this.btnSell.TabIndex = 11;
            this.btnSell.Text = "SELL";
            this.btnSell.UseVisualStyleBackColor = true;
            this.btnSell.Click += new System.EventHandler(this.btnSell_Click);
            // 
            // btnBuy
            // 
            this.btnBuy.Location = new System.Drawing.Point(374, 321);
            this.btnBuy.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.btnBuy.Name = "btnBuy";
            this.btnBuy.Size = new System.Drawing.Size(168, 35);
            this.btnBuy.TabIndex = 12;
            this.btnBuy.Text = "BUY";
            this.btnBuy.UseVisualStyleBackColor = true;
            this.btnBuy.Click += new System.EventHandler(this.btnBuy_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(217, 260);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(63, 20);
            this.label4.TabIndex = 13;
            this.label4.Text = "quanitiy";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(632, 366);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(74, 20);
            this.label5.TabIndex = 17;
            this.label5.Text = "Bid - ALL";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(632, 26);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(78, 20);
            this.label6.TabIndex = 16;
            this.label6.Text = "Ask - ALL";
            // 
            // blBidDB
            // 
            this.blBidDB.FormattingEnabled = true;
            this.blBidDB.ItemHeight = 20;
            this.blBidDB.Location = new System.Drawing.Point(632, 402);
            this.blBidDB.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.blBidDB.Name = "blBidDB";
            this.blBidDB.Size = new System.Drawing.Size(217, 264);
            this.blBidDB.TabIndex = 15;
            // 
            // blAskDB
            // 
            this.blAskDB.FormattingEnabled = true;
            this.blAskDB.ItemHeight = 20;
            this.blAskDB.Location = new System.Drawing.Point(632, 59);
            this.blAskDB.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.blAskDB.Name = "blAskDB";
            this.blAskDB.Size = new System.Drawing.Size(217, 264);
            this.blAskDB.TabIndex = 14;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1480, 692);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.blBidDB);
            this.Controls.Add(this.blAskDB);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.btnBuy);
            this.Controls.Add(this.btnSell);
            this.Controls.Add(this.tbQuantity);
            this.Controls.Add(this.tbPrice);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.ListBoxBid);
            this.Controls.Add(this.ListBoxAsk);
            this.Controls.Add(this.BtnStopOrderbook);
            this.Controls.Add(this.BtnStopQuote);
            this.Controls.Add(this.BtnSetQuote);
            this.Controls.Add(this.BtnGetOrderbook);
            this.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button BtnGetOrderbook;
        private System.Windows.Forms.Button BtnSetQuote;
        private System.Windows.Forms.ListBox ListBoxAsk;
        private System.Windows.Forms.ListBox ListBoxBid;
        private System.Windows.Forms.Button BtnStopOrderbook;
        private System.Windows.Forms.Button BtnStopQuote;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox tbPrice;
        private System.Windows.Forms.TextBox tbQuantity;
        private System.Windows.Forms.Button btnSell;
        private System.Windows.Forms.Button btnBuy;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.ListBox blBidDB;
        private System.Windows.Forms.ListBox blAskDB;
    }
}

