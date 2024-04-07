package com.maketoff.lights;

import android.app.ProgressDialog;
import android.content.Context;
import android.net.wifi.WifiConfiguration;
import android.net.wifi.WifiManager;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.CheckBox;
import android.widget.TextView;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.List;

import static java.lang.Thread.sleep;


public class MainActivity extends ActionBarActivity {

    String networkSSID = "ESP";
    String networkPass = "pass";

    private Socket socket;
    private static final int SERVERPORT = 3000;
    private static final String SERVER_IP = "192.168.1.1";

    ClientThread client;
    TextView tvText, tvMessage;

    ProgressDialog ProgresDlg;
    int loadProgrs=0;
    int progrsMax=3;


   /* public void ShowManager()
    {
        TextView mainText = (TextView) findViewById(R.id.wifiText);
        mainText.setText("editted");
    }*/



    private Handler hPrgrs;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


            WifiConfiguration conf = new WifiConfiguration();
            conf.SSID = "\"" + networkSSID + "\"";
/* -----------------------------------------------------------------------------WEP
        conf.wepKeys[0] = "\"" + networkPass + "\"";
        conf.wepTxKeyIndex = 0;
        conf.allowedKeyManagement.set(WifiConfiguration.KeyMgmt.NONE);
        conf.allowedGroupCiphers.set(WifiConfiguration.GroupCipher.WEP40);
*/
            //For WPA network you need to add passphrase like this:   ----------WPA
/*
        conf.preSharedKey = "\""+ networkPass +"\"";
*/
            //For Open network you need to do this:

            conf.allowedKeyManagement.set(WifiConfiguration.KeyMgmt.NONE);
            //Then, you need to add it to Android wifi manager settings:

            final WifiManager wifiManager = (WifiManager) getSystemService(Context.WIFI_SERVICE);
            //
            //
            wifiManager.addNetwork(conf);









        ProgresDlg = new ProgressDialog(this);
        ProgresDlg.setTitle("Подключение");
        ProgresDlg.setMessage("fds");
        ProgresDlg.setProgressStyle(1);
        ProgresDlg.show();
        ProgresDlg.setMax(3);

        ProgresDlg.setProgressStyle(ProgressDialog.STYLE_SPINNER);
        ProgresDlg.setIndeterminate(true);
        ProgresDlg.setCanceledOnTouchOutside(false);




        hPrgrs =

        new Handler() {
            @Override
            public void handleMessage(android.os.Message msg) {
                switch (msg.what) {
                    case 0:
                        ProgresDlg.setMessage("Подключаюсь к wifi");
                        break;
                    case 1:
                        ProgresDlg.setMessage("Подключаюсь к серверу");
                        break;
                    case 2:
                        ProgresDlg.setMessage("Все готово");
                        ProgresDlg.dismiss();
                        break;
                }
            };
        };
        //hPrgrs.sendEmptyMessage(0);

/*new Handler() {
            @Override
            public void handleMessage(android.os.Message msg) {
                ProgresDlg.setMessage("Включаю wifi");
                ProgresDlg.setProgress(msg.what);
                loadProgrs++;
                /*if(msg.what==0) {
                    ProgresDlg.setMessage("Подключаюсь к wifi");
                }
                if(msg.what==1) {
                    ProgresDlg.setMessage("Подключаюсь к серверу");

                }
                if(msg.what==2) {

                    ProgresDlg.dismiss();
                }
    }
};*/



        if(!wifiManager.isWifiEnabled()) {


           Thread ThrWIFIen=new Thread(new Runnable() {
               @Override
               public void run() {
                   try {
                       Thread.sleep(4000);
                   } catch (InterruptedException e) {
                       e.printStackTrace();
                   }
                   hPrgrs.sendEmptyMessage(1);
                   wifiManager.setWifiEnabled(true);
                  /* while(!wifiManager.isWifiEnabled())

                   {
                       //Wait to connect
                       try {
                           Thread.sleep(1000);
                       } catch (InterruptedException e) {
                           e.printStackTrace();
                       }
                   }*/


               }
           });
            ThrWIFIen.start();

           /*{



               //ProgressDialog.show(Context,"Loading","Please wait...",true);

                wifiManager.setWifiEnabled(true);
                while(!wifiManager.isWifiEnabled())

                {
                    //Wait to connect
                    sleep(1000);
                }


            }*/

        }


            // And finally, you might need to enable it, so Android connects to it:
            if(wifiManager.isWifiEnabled()) {
                List<WifiConfiguration> list = wifiManager.getConfiguredNetworks();
                for (WifiConfiguration i : list) {
                    if (i.SSID != null && i.SSID.equals("\"" + networkSSID + "\"")) {
                        wifiManager.disconnect();
                        wifiManager.enableNetwork(i.networkId, true);
                        wifiManager.reconnect();

                        break;
                    }
                }



                client = new ClientThread();
                Thread thread = new Thread(client);
                thread.start();
            }

    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }


    public void onConnect(View v)  {
        TextView asd = (TextView)findViewById(R.id.txtVw);

        switch(v.getId()) {
           case R.id.chk1:
                client.sendMessage("1tst");
                break;
           case R.id.chk2:
                client.sendMessage("2tst");
                break;
           case R.id.chk3:
                client.sendMessage("3tst");
                break;
           case R.id.chk4:
                client.sendMessage("4tst");
                break;
           case R.id.chk5:
                client.sendMessage("5tst");
                break;
           case R.id.chk6:
                client.sendMessage("6tst");
                break;
           case R.id.chk7:
                client.sendMessage("7tst");
                break;
           case R.id.chk8:
                client.sendMessage("8tst");
                break;
        }



    }





    class ClientThread implements Runnable
    {
        PrintWriter out;
        BufferedReader in;


        @Override
        public void run()
        {
            try
            {
                InetAddress serverAddr = InetAddress.getByName(SERVER_IP);
                socket = new Socket(serverAddr, SERVERPORT);

                out = new PrintWriter(socket.getOutputStream(),true);
                in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            }
            catch (UnknownHostException e1)  {	e1.printStackTrace();  }
            catch (IOException e1) { e1.printStackTrace();  }
        }


        public void sendMessage(String str)
        {

                out.write(str);
                out.flush();

          // String line = in.readLine();

        }

        public void stopClient() {
            if (out != null) {
                out.flush();
                out.close();
            }
        }
    }
}



