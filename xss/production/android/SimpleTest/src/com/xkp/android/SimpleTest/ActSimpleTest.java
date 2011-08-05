package com.xkp.android.SimpleTest;

import android.app.Activity;
import android.os.Bundle;
    import android.widget.TextView;
    import android.widget.Button;
    import android.widget.CheckBox;
    import android.widget.EditText;

public class ActSimpleTest 
                extends Activity
        	implements OnClickListener
				
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
            this.priv_rep = (XKPReplicator) findViewById(R.id.rep);
            this.priv_template1 = (XKPLayout) findViewById(R.id.template1);
            this.priv_value = (TextView) findViewById(R.id.value);
            this.priv_name = (TextView) findViewById(R.id.name);
            this.priv_swtExchange = (XKPSwitcher) findViewById(R.id.swtExchange);
            this.priv_btn3 = (Button) findViewById(R.id.btn3);
            this.priv_chk1 = (CheckBox) findViewById(R.id.chk1);
            this.priv_div1 = (XKPLayout) findViewById(R.id.div1);
            this.priv_lbl1 = (TextView) findViewById(R.id.lbl1);
            this.priv_btn2 = (Button) findViewById(R.id.btn2);
            this.priv_btn1 = (Button) findViewById(R.id.btn1);
            this.priv_lblFullName = (TextView) findViewById(R.id.lblFullName);
            this.priv_btnFullName = (Button) findViewById(R.id.btnFullName);
            this.priv_btnFullName.setOnClickListener(this);
            this.priv_edtLastName = (EditText) findViewById(R.id.edtLastName);
            this.priv_lblLastName = (TextView) findViewById(R.id.lblLastName);
            this.priv_edtFirstName = (EditText) findViewById(R.id.edtFirstName);
            this.priv_lblFirstName = (TextView) findViewById(R.id.lblFirstName);
    }
	
        @Override
        public void onClick(View v) {
            switch (v.getId()) {
            case R.id.btnFullName:
                onClickbtnFullName();
                break;
        		
            } //switch
        }

        private void onClickbtnFullName() {
            String fullname = edtFirstName.getText().toString() + " " + edtLastName.getText().toString();
            if (fullname != " ")
            {
                lblFullName.setText("Your fullname is " + fullname);
            }
            else
            {
                lblFullName.setText("Your fullname is EMPTY!");
            }
        }
        
}

