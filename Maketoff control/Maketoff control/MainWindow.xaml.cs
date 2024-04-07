using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

using System.Net;
using System.Net.Sockets;
using System.Threading;

namespace Maketoff_control
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        byte[] remdata = { };
        TcpClient Client = new TcpClient();
        string ip = "127.0.0.1"; // ip адрес
        int port = 3000; // порт
        Socket Sock;
        public MainWindow()
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
                conStat.Text += "\nCannot connect to remote host!";
                return;
            }
            conStat.Text = "Connected";

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

        private void stop_btn_Click(object sender, EventArgs e)
        {
            Sock.Close();
            Client.Close();
        }
        ~MainWindow()
        {
            Sock.Close();
            Client.Close();
        }

        public void chkEv(object sender, RoutedEventArgs e)
        {

            CheckBox cb = (CheckBox)sender;
            

            if (Client.Connected)
            {
                if (cb.Name == "chk1")
                {
                    Sock.Send(Encoding.ASCII.GetBytes("1tst"));
                }
                if (cb.Name == "chk2")
                {
                    Sock.Send(Encoding.ASCII.GetBytes("2tst"));
                }
                if (cb.Name == "chk3")
                {
                    Sock.Send(Encoding.ASCII.GetBytes("3tst"));
                }
                if (cb.Name == "chk4")
                {
                    Sock.Send(Encoding.ASCII.GetBytes("4tst"));
                }
                if (cb.Name == "chk5")
                {
                    Sock.Send(Encoding.ASCII.GetBytes("5tst"));
                }
            }
            else
            {
                if ((bool)cb.IsChecked)
                {
                    cb.IsChecked = false;
                    if (cb.Name == "chk1")
                    {
                        text2.Text = "1 checked";

                    }
                }
                else
                {

                    cb.IsChecked = true;

                    if (cb.Name == "chk1")
                    {
                        text2.Text = "1 UNchecked";
                    }
                }

            }

        }
    }
}
