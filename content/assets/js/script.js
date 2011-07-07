/* Author: 

*/


$(function(){


	// External links open in a new window
	$("a[rel='external']").click(
		function()
		{
			window.open(this.href);
			return false;
		});


	get_latest_tweets(10);

});





















