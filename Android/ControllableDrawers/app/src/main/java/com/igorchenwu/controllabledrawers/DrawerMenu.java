package com.igorchenwu.controllabledrawers;

import android.bluetooth.BluetoothAdapter;
import android.content.Intent;
import android.graphics.Typeface;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.TextView;

//activity where users can see a list of drawers of the paired Arduino
public class DrawerMenu extends AppCompatActivity {

    public void hidePopUp(View view) {
        LinearLayout popUp = (LinearLayout) findViewById(R.id.drawerPopUp);
        popUp.setVisibility(View.GONE);
    }

    public void toggleDrawer(View view) {

    }

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