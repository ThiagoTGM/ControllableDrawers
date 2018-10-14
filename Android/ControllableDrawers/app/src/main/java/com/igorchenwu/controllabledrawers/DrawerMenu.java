package com.igorchenwu.controllabledrawers;

import android.bluetooth.BluetoothAdapter;
import android.content.Intent;
import android.graphics.Typeface;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

public class DrawerMenu extends AppCompatActivity {

    //switch to main menu activity
    public void mainMenu(View view) {
        Intent i = new Intent(this, MainMenu.class);
        startActivity(i);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_drawer_menu);
    }
}