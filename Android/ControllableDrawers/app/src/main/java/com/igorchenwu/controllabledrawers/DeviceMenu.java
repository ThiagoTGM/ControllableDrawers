package com.igorchenwu.controllabledrawers;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;

public class DeviceMenu extends AppCompatActivity {

    //switch to main menu activity
    public void mainMenu(View view) {
        Intent i = new Intent(this, MainMenu.class);
        startActivity(i);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_device_menu);
    }
}
