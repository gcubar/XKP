on pushButton_1.click()
{
	//Aqui estan algunos ejemplos
	var placement = pushButton_1.placement;
	Placement pl = Placement.Left;
	var pl1 = Placement.Right;

	pushButton_2.caption = "Clicked";
	caption = "Other Clicked";

	pushButton_2.width += pushButton_1.width;
	application.reset(600);
}

on pushButton_2.click()
{
	pushButton_1.caption = "Old value: " + application.target;

	xss_breakpoint();
	application.target = 300;
}

property target : string =
//{
//	return value;
//}
//{
//	value = "ok";
//}
 {
	pushButton_2.caption = "target acquired " + value;
	
	 for(int i = 0; i < 20; i++)
	 {
		 pushButton_2.width = pushButton_2.width + 10;
		 if (pushButton_2.width > 200)
			 pushButton_2.width = 100;
	 }
 }

method reset(string s)
{
	//target = s;
	//pushButton_1.caption = "...";
	//pushButton_2.caption = "..." + target;
	return target + "...";
}

method returning_stuff()
{
	var i = 0;
	return i + 23;
}

//method declaring_error() : string
method declaring_error()
{
	var s = "hello";
	return 12;
	return s;
}

//method declaring_ok() : int
method declaring_ok(int value)
{
	return value;
}

//this is a very trick
method declaring_trick(var value)
{
	return value;
}

//method returned_real() : float
method returned_real()
{
	int pi = 3.14;
	return pi;
}

