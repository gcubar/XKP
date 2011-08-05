package com.xkp.android.Contacts;

import java.util.ArrayList;
import java.util.Arrays;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
    import android.widget.TextView;
    import android.widget.EditText;
    import android.widget.RadioButton;
    import android.widget.Button;
    import android.widget.CheckBox;
    import android.widget.CompoundButton;
    import android.widget.CompoundButton.OnCheckedChangeListener;

public class ActContacts 
                extends Activity
        	implements OnCheckedChangeListener    , OnClickListener				
{
        private XKPSwitcher priv_swtStates;
        private XKPLayout priv_divAbout;
        private TextView priv___label1;
        private XKPLayout priv_divFind;
        private EditText priv_edtCriterion;
        private TextView priv_lblCriterion;
        private RadioButton priv_rdbByPhone;
        private RadioButton priv_rdbByName;
        private TextView priv_lblFindType;
        private XKPLayout priv_divAdd;
        private Button priv_btnAddContact;
        private CheckBox priv_chkVerifier;
        private EditText priv_edtPhoneNumber;
        private EditText priv_edtFullName;
        private TextView priv_lblPhone;
        private TextView priv_lblFullName;
        private XKPLayout priv___div1;
        private Button priv_btnRight;
        private Button priv_btnLeft;

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        bindViews();
    }
	
    private void bindViews() {
            this.priv_swtStates = (XKPSwitcher) findViewById(R.id.swtStates);
            this.priv_divAbout = (XKPLayout) findViewById(R.id.divAbout);
            this.priv___label1 = (TextView) findViewById(R.id.__label1);
            this.priv_divFind = (XKPLayout) findViewById(R.id.divFind);
            this.priv_edtCriterion = (EditText) findViewById(R.id.edtCriterion);
            this.priv_lblCriterion = (TextView) findViewById(R.id.lblCriterion);
            this.priv_rdbByPhone = (RadioButton) findViewById(R.id.rdbByPhone);
            this.priv_rdbByName = (RadioButton) findViewById(R.id.rdbByName);
            this.priv_lblFindType = (TextView) findViewById(R.id.lblFindType);
            this.priv_divAdd = (XKPLayout) findViewById(R.id.divAdd);
            this.priv_btnAddContact = (Button) findViewById(R.id.btnAddContact);
            this.priv_chkVerifier = (CheckBox) findViewById(R.id.chkVerifier);
            this.priv_chkVerifier.setOnCheckedChangeListener(this);
            this.priv_edtPhoneNumber = (EditText) findViewById(R.id.edtPhoneNumber);
            this.priv_edtFullName = (EditText) findViewById(R.id.edtFullName);
            this.priv_lblPhone = (TextView) findViewById(R.id.lblPhone);
            this.priv_lblFullName = (TextView) findViewById(R.id.lblFullName);
            this.priv___div1 = (XKPLayout) findViewById(R.id.__div1);
            this.priv_btnRight = (Button) findViewById(R.id.btnRight);
            this.priv_btnRight.setOnClickListener(this);
            this.priv_btnLeft = (Button) findViewById(R.id.btnLeft);
            this.priv_btnLeft.setOnClickListener(this);
    }
	
        @Override
        public void onCheckedChanged(CompoundButton v, boolean isChecked) {
            switch (v.getId()) {
            case R.id.chkVerifier:
                onCheckedChangedchkVerifier();
                break;
        		
            } //switch
        }
    	
        @Override
        public void onClick(View v) {
            switch (v.getId()) {
            case R.id.btnRight:
                onClickbtnRight();
                break;
        		
            case R.id.btnLeft:
                onClickbtnLeft();
                break;
        		
            } //switch
        }
    	
    	private ArrayList<String> swtTabsTexts	= new ArrayList<String>(Arrays.asList("Add contact", "Find contact", "About"));
    	
    	public String getSwitchText(int idx) {
        	if (idx < 0)
        	{
        	    idx = swtTabsTexts.size;
        	}
        	else
        	{
        	    if (idx >= swtTabsTexts.size)
        	    {
        	        idx = idx % swtTabsTexts.size;
        	    }
        	}
        	return swtTabsTexts.get(idx);
    	}
    	
    	private void onCheckedChangedchkVerifier() {
    	}
    	
    	private void onClickbtnRight() {
        	priv_swtStates.setDisplayedChild(priv_swtStates.getDisplayedChild() + 1);
        	priv_btnLeft.setText(getSwitchText(priv_swtStates.getDisplayedChild() + 1));
    	}
    	
    	private void onClickbtnLeft() {
        	priv_swtStates.setDisplayedChild(priv_swtStates.getDisplayedChild() - 1);
        	priv_btnLeft.setText(getSwitchText(priv_swtStates.getDisplayedChild() - 1));
        	Object x = ((XKPLayout.LayoutParams) priv_btnLeft.getLayoutParams()).getPlacement();
        	priv_btnLeft.setPlacement(left);
    	}
    	
}

