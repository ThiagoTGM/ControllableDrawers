package com.igorchenwu.controllabledrawers;

import android.bluetooth.BluetoothAdapter;
import android.content.Intent;
import android.graphics.Typeface;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

public class MainMenu extends AppCompatActivity {

    private BluetoothAdapter BA = BluetoothAdapter.getDefaultAdapter();

    //self-explanatory
    public void toggleBluetooth (View view) {
        TextView status = (TextView) findViewById(R.id.bluetoothStatusField);

        if(BA.isEnabled()) {
            BA.disable();
            status.setText("OFF");
            status.setTextColor(getResources().getColor(R.color.colorMainTitleText));
        } else {
            Intent bOn = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivity(bOn);
            status.setText("ON");
            status.setTextColor(getResources().getColor(R.color.colorMainButtonBgActive));
        }
    }

    public void findDiscoverableDevices (View view) {
        Intent i = new Intent(this, NDeviceMenu.class);
        startActivity(i);
    }

    public void viewPairedDevices (View view) {
        Intent i = new Intent(this, DeviceMenu.class);
        startActivity(i);
    }

    //switch to drawer menu activity
    public void displayDrawers(View view) {
        Intent i = new Intent(this, DrawerMenu.class);
        startActivity(i);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main_menu);

        TextView status = (TextView) findViewById(R.id.bluetoothStatusField);

        if(BA.isEnabled()) {
            status.setText("ON");
            status.setTextColor(getResources().getColor(R.color.colorMainButtonBgActive));
        } else {
            status.setText("OFF");
            status.setTextColor(getResources().getColor(R.color.colorMainTitleText));
        }
    }
}
