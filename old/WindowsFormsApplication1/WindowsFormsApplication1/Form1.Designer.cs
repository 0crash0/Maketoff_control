namespace WindowsFormsApplication1
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
            this.connect_btn = new System.Windows.Forms.Button();
            this.console_txt = new System.Windows.Forms.TextBox();
            this.tst1 = new System.Windows.Forms.Button();
            this.tst2 = new System.Windows.Forms.Button();
            this.tst3 = new System.Windows.Forms.Button();
            this.tst4 = new System.Windows.Forms.Button();
            this.tst5 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // connect_btn
            // 
            this.connect_btn.Location = new System.Drawing.Point(7, 10);
            this.connect_btn.Name = "connect_btn";
            this.connect_btn.Size = new System.Drawing.Size(75, 23);
            this.connect_btn.TabIndex = 5;
            this.connect_btn.Text = "connect";
            this.connect_btn.UseVisualStyleBackColor = true;
            this.connect_btn.Click += new System.EventHandler(this.connect_btn_Click);
            // 
            // console_txt
            // 
            this.console_txt.ForeColor = System.Drawing.Color.YellowGreen;
            this.console_txt.Location = new System.Drawing.Point(42, 39);
            this.console_txt.Multiline = true;
            this.console_txt.Name = "console_txt";
            this.console_txt.Size = new System.Drawing.Size(247, 36);
            this.console_txt.TabIndex = 6;
            this.console_txt.Text = "Console:";
            // 
            // tst1
            // 
            this.tst1.Location = new System.Drawing.Point(7, 88);
            this.tst1.Name = "tst1";
            this.tst1.Size = new System.Drawing.Size(75, 23);
            this.tst1.TabIndex = 7;
            this.tst1.Text = "1tst";
            this.tst1.UseVisualStyleBackColor = true;
            this.tst1.Click += new System.EventHandler(this.tst1_Click);
            // 
            // tst2
            // 
            this.tst2.Location = new System.Drawing.Point(89, 87);
            this.tst2.Name = "tst2";
            this.tst2.Size = new System.Drawing.Size(75, 23);
            this.tst2.TabIndex = 8;
            this.tst2.Text = "2tst";
            this.tst2.UseVisualStyleBackColor = true;
            this.tst2.Click += new System.EventHandler(this.tst2_Click);
            // 
            // tst3
            // 
            this.tst3.Location = new System.Drawing.Point(171, 87);
            this.tst3.Name = "tst3";
            this.tst3.Size = new System.Drawing.Size(75, 23);
            this.tst3.TabIndex = 9;
            this.tst3.Text = "3tst";
            this.tst3.UseVisualStyleBackColor = true;
            this.tst3.Click += new System.EventHandler(this.tst3_Click);
            // 
            // tst4
            // 
            this.tst4.Location = new System.Drawing.Point(7, 117);
            this.tst4.Name = "tst4";
            this.tst4.Size = new System.Drawing.Size(75, 23);
            this.tst4.TabIndex = 10;
            this.tst4.Text = "4tst";
            this.tst4.UseVisualStyleBackColor = true;
            this.tst4.Click += new System.EventHandler(this.tst4_Click);
            // 
            // tst5
            // 
            this.tst5.Location = new System.Drawing.Point(88, 117);
            this.tst5.Name = "tst5";
            this.tst5.Size = new System.Drawing.Size(75, 23);
            this.tst5.TabIndex = 11;
            this.tst5.Text = "5tst";
            this.tst5.UseVisualStyleBackColor = true;
            this.tst5.Click += new System.EventHandler(this.tst5_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(296, 149);
            this.Controls.Add(this.tst5);
            this.Controls.Add(this.tst4);
            this.Controls.Add(this.tst3);
            this.Controls.Add(this.tst2);
            this.Controls.Add(this.tst1);
            this.Controls.Add(this.console_txt);
            this.Controls.Add(this.connect_btn);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Button connect_btn;
        private System.Windows.Forms.TextBox console_txt;
        private System.Windows.Forms.Button tst1;
        private System.Windows.Forms.Button tst2;
        private System.Windows.Forms.Button tst3;
        private System.Windows.Forms.Button tst4;
        private System.Windows.Forms.Button tst5;
    }
}

