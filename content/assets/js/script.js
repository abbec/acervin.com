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

});

$(document).ready(function() {
	
	$("a.gallery").fancybox({
		'overlayColor'  :   '#aaaaaa',
		'transitionIn'	:	'elastic',
		'transitionOut'	:	'elastic',
		'speedIn'		:	300, 
		'speedOut'		:	300, 
		'overlayShow'	:	true
	});
	
});



















