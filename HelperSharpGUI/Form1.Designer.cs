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
            this.ListBoxAsk.Location = new System.Drawing.Point(603, 46);
            this.ListBoxAsk.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.ListBoxAsk.Name = "ListBoxAsk";
            this.ListBoxAsk.Size = new System.Drawing.Size(511, 264);
            this.ListBoxAsk.TabIndex = 4;
            // 
            // ListBoxBid
            // 
            this.ListBoxBid.FormattingEnabled = true;
            this.ListBoxBid.ItemHeight = 20;
            this.ListBoxBid.Location = new System.Drawing.Point(603, 389);
            this.ListBoxBid.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.ListBoxBid.Name = "ListBoxBid";
            this.ListBoxBid.Size = new System.Drawing.Size(511, 264);
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
            this.label1.Location = new System.Drawing.Point(603, 13);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(36, 20);
            this.label1.TabIndex = 6;
            this.label1.Text = "Ask";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(603, 353);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(32, 20);
            this.label2.TabIndex = 7;
            this.label2.Text = "Bid";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1200, 692);
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
    }
}

