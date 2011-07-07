function get_latest_tweets(number)
{
	var div = $("#twitter > #tweets"); 

	div.parent().fadeIn();
	div.html("<p>Loading tweets...</p>");
    
    $.getJSON("http://twitter.com/statuses/user_timeline.json?screen_name=albertcervin&count="+number+"&include_rts=1&callback=?", function(tweets) { 

		div.hide();

		var out = "<ul>";

		$.each(tweets, 
			   function(i,tweet) 
			   {
				   out += '<li><p>' + tweet.text + '</p></li>';
			   });

		out += "</ul>";
		
		div.html(out);

		div.slideDown('fast');
		
    });
}