package com.igorchenwu.controllabledrawers;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.TypedValue;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.TextView;

import java.util.Set;

public class DeviceMenu extends AppCompatActivity {

    BluetoothAdapter BA = BluetoothAdapter.getDefaultAdapter();

    //switch to main menu activity
    public void mainMenu(View view) {
        Intent i = new Intent(this, MainMenu.class);
        startActivity(i);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_device_menu);

        Set<BluetoothDevice> pairedDevices = BA.getBondedDevices();
        LinearLayout devices = (LinearLayout) findViewById(R.id.deviceList);
        TextView noDeviceText = (TextView) findViewById(R.id.noDeviceText);

        if (pairedDevices.size() > 0) {
            noDeviceText.setVisibility(View.GONE);

            // There are paired devices. Get the name and address of each paired device.
            for (BluetoothDevice device : pairedDevices) {
                TextView t = new TextView(this);
                t.setText(device.getName() + "\n" + device.getAddress() + "\n\n" );
                devices.addView(t);
            }
        }
    }
}
