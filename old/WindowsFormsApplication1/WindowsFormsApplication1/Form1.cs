using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;
using System.Threading;

namespace WindowsFormsApplication1
{

    public partial class Form1 : Form
    {
        
        byte[] remdata = { };
        TcpClient Client = new TcpClient();
        string ip = "127.0.0.1"; // ip адрес
        int port = 3000; // порт
        Socket Sock;
        public Form1()
        {
            InitializeComponent();
        }

        private void connect_btn_Click(object sender, EventArgs e)
        {
            ip = "192.168.1.1";
            try
            {
                Client.Connect(ip, port);
            }
            catch
            {
                console_txt.Text+="\nCannot connect to remote host!";
                return;
            }
            console_txt.Text += "\nConnected'";
            Sock = Client.Client;

            Thread clientThread = new Thread(new ThreadStart(GetMsg));
            clientThread.Start();

        }


        void GetMsg()
        {
            NetworkStream clientStream = Client.GetStream();
            int bytesRead;
            
             while (true)
            {
                bytesRead = 0;

                try
                {
                    //blocks until a client sends a message
                    bytesRead = clientStream.Read(remdata, 0, 4096);
                }
                catch
                {
                    //a socket error has occured
                    break;
                }

                

                //message has successfully been received
                ASCIIEncoding encoder = new ASCIIEncoding();

                // Convert the Bytes received to a string and display it on the Server Screen

                // Now Echo the message back

                //Echo(msg, encoder, clientStream);
            }
        }


        private void send_btn_Click(object sender, EventArgs e)
        {
            
        }

        private void stop_btn_Click(object sender, EventArgs e)
        {
            Sock.Close();
            Client.Close();
        }
        ~Form1()
        {
            Sock.Close();
            Client.Close();
        }

        private void tst1_Click(object sender, EventArgs e)
        {
            Sock.Send(Encoding.ASCII.GetBytes("1tst"));
        }

        private void tst2_Click(object sender, EventArgs e)
        {
            Sock.Send(Encoding.ASCII.GetBytes("2tst"));
        }

        private void tst3_Click(object sender, EventArgs e)
        {
            Sock.Send(Encoding.ASCII.GetBytes("3tst"));
        }

        private void tst4_Click(object sender, EventArgs e)
        {
            Sock.Send(Encoding.ASCII.GetBytes("4tst"));
        }

        private void tst5_Click(object sender, EventArgs e)
        {
            Sock.Send(Encoding.ASCII.GetBytes("5tst"));
        }
    }
}
