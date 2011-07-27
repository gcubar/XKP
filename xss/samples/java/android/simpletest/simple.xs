on btnFullName.click()
{
	string fullname = edtFirstName.text + " " + edtLastName.text;
	
	if(fullname != " ")
		lblFullName.caption = "Your fullname is " + fullname;
	else
		lblFullName.caption = "Your fullname is EMPTY!";
}

on creation()
{
	array sources = [
		object( name = "cuba", value = "father"), 
		object( name = "daniela", value = "daughter"), 
		object( name = "maite", value = "wife")
	];
	//rep.items = sources;
}

instance rep.template1
{
	property data_source
	{
		name.caption = data_source.name;
		value.caption = data_source.value;
	}
}