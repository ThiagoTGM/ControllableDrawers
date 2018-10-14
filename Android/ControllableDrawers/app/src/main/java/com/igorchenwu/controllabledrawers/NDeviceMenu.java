package com.igorchenwu.controllabledrawers;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;

//ok maybe I dun goofed and we might not need to use this one but w/e
public class NDeviceMenu extends AppCompatActivity {

    //switch to main menu activity
    public void mainMenu(View view) {
        Intent i = new Intent(this, MainMenu.class);
        startActivity(i);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_ndevice_menu);
    }
}
