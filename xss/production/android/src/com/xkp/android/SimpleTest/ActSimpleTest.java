package com.xkp.android.SimpleTest;

import android.app.Activity;
import android.os.Bundle;
    import android.widget.TextView;
    import android.widget.Button;
    import android.widget.CheckBox;
    import android.widget.EditText;

public class ActSimpleTest 
                extends Activity
				
{
        private XKPReplicator priv_rep;
        private XKPLayout priv_template1;
        private TextView priv_value;
        private TextView priv_name;
        private XKPSwitcher priv_swtExchange;
        private Button priv_btn3;
        private CheckBox priv_chk1;
        private XKPLayout priv_div1;
        private TextView priv_lbl1;
        private Button priv_btn2;
        private Button priv_btn1;
        private TextView priv_lblFullName;
        private Button priv_btnFullName;
        private EditText priv_edtLastName;
        private TextView priv_lblLastName;
        private EditText priv_edtFirstName;
        private TextView priv_lblFirstName;

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
		bindViews();
	}
	
	private void bindViews() {
        	priv_rep = (XKPReplicator) findViewById(R.id.rep);
        	priv_template1 = (XKPLayout) findViewById(R.id.template1);
        	priv_value = (TextView) findViewById(R.id.value);
        	priv_name = (TextView) findViewById(R.id.name);
        	priv_swtExchange = (XKPSwitcher) findViewById(R.id.swtExchange);
        	priv_btn3 = (Button) findViewById(R.id.btn3);
        	priv_chk1 = (CheckBox) findViewById(R.id.chk1);
        	priv_div1 = (XKPLayout) findViewById(R.id.div1);
        	priv_lbl1 = (TextView) findViewById(R.id.lbl1);
        	priv_btn2 = (Button) findViewById(R.id.btn2);
        	priv_btn1 = (Button) findViewById(R.id.btn1);
        	priv_lblFullName = (TextView) findViewById(R.id.lblFullName);
        	priv_btnFullName = (Button) findViewById(R.id.btnFullName);
        	priv_edtLastName = (EditText) findViewById(R.id.edtLastName);
        	priv_lblLastName = (TextView) findViewById(R.id.lblLastName);
        	priv_edtFirstName = (EditText) findViewById(R.id.edtFirstName);
        	priv_lblFirstName = (TextView) findViewById(R.id.lblFirstName);

    }
	
}

