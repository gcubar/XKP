package com.xkp.android.SimpleTest;

import java.util.ArrayList;

import android.content.Context;
import android.content.res.TypedArray;
import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.view.View;

public class XKPReplicator extends XKPLayout {
	
	static private final int ID_START = 0x7f0A0000;
	
	static private int mChildCount = ID_START;
	
	protected OnItemAssigner mOnItemAssigner;
	
	private int mTemplateResource = 0;
	private int mTemplateIndex;
	private ArrayList<Template> mTemplates;

	public XKPReplicator(Context context) {
		super(context);
		
		mTemplates = new ArrayList<Template>();
	}

	public XKPReplicator(Context context, AttributeSet attrs) {
		super(context, attrs);
		
        TypedArray a = context.obtainStyledAttributes(attrs, R.styleable.XKPReplicator);
        mTemplateResource = a.getResourceId(R.styleable.XKPReplicator_template, 0);
        
        a.recycle();
        
		mTemplates = new ArrayList<Template>();
		
		//for now
		mTemplateIndex = R.layout.template;
	}
	
	public void setTemplateIndex(int index) {
		mTemplateIndex = index;
	}
	
	public int getTemplateIndex() {
		return mTemplateIndex;
	}
	
	public void replicateTemplate(int index, int count) {
		LayoutInflater linflater = (LayoutInflater) this.getContext().
			getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		
		for(int i = 0; i < count; i++) {
			View template = linflater.inflate(mTemplateIndex, this);
			mChildCount++;
			template.setId(mChildCount);
		}
	}
	
	public boolean assignItem(Object i) {
		
		if (mOnItemAssigner != null) {
			mOnItemAssigner.OnAssign(i);
			return true;
		}
		
		return false;
	}
	
    /**
     * Register a callback to be invoked when one item is assigning.
     *
     * @param i The callback that will run
     */
    public void setOnItemAssigner(OnItemAssigner i) {
        mOnItemAssigner = i;
    }

	public interface OnItemAssigner {
        /**
         * Called when a item was assigned to a replicator.
         *
         * @param item The item that was assigned.
         */
		void OnAssign(Object item);
	}
	
	public class Template {
		public View view;
		public int index;
		public XKPLayout.LayoutParams params;
	}
	
}

