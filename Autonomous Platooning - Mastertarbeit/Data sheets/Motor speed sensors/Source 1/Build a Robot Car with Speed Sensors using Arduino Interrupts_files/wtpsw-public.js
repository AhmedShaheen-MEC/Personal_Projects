jQuery( document ).ready(function( $ ) {

	/* Post views count ajax */
	if( Wtpsw.post_view_count != 0 ) {
		var data = {
					action 		: 'wtpsw_post_view_count',
					is_ajax 	: 1,
					post_id 	: Wtpsw.post_view_count
				};
		$.post(Wtpsw.ajaxurl,data,function(response) {
			/* Do Response Process */
		});
	}

	/* For Trending Post Slider */
	$( '.wtpsw-post-slider' ).each(function( index ) {

		var slider_id   	= $(this).attr('id');
		var slider_conf 	= $.parseJSON( $(this).attr('data-conf'));

		if( typeof(slider_id) != 'undefined' && slider_id != '' ) {
			jQuery('#'+slider_id).slick({
				infinite		: true,
				slidesToShow	: 1,
				slidesToScroll	: 1,
				dots			: ( slider_conf.dots == "true" ) ? true : false,
				arrows			: ( slider_conf.arrows == "true" ) ? true : false,
				autoplay		: ( slider_conf.autoplay == "true" ) ? true : false,
				speed			: parseInt(slider_conf.speed),
				autoplaySpeed	: parseInt( slider_conf.autoplayinterval ),
				rtl             : ( Wtpsw.is_rtl == 1 ) ? true : false,
			});
		}
	});

	/* For Trending Post Carousel */
	$( '.wtpsw-post-carousel' ).each(function( index ) {

		var slider_id   	= $(this).attr('id');
		var slider_conf 	= $.parseJSON( $(this).attr('data-conf'));

		if( typeof(slider_id) != 'undefined' && slider_id != '' ) {
			jQuery('#'+slider_id).slick({
				infinite		: true,
				dots			: ( slider_conf.dots == "true" ) ? true : false,
				arrows			: ( slider_conf.arrows == "true" ) ? true : false,
				autoplay		: ( slider_conf.autoplay == "true" ) ? true : false,
				speed			: parseInt( slider_conf.speed ),
				autoplaySpeed	: parseInt( slider_conf.autoplayinterval ),
				slidesToShow	: parseInt( slider_conf.slides_to_show ),
				slidesToScroll	: parseInt( slider_conf.slides_to_scroll ),
				rtl             : ( Wtpsw.is_rtl == 1 ) ? true : false,
				mobileFirst    	: ( Wtpsw.is_mobile == 1 ) ? true : false,
				responsive: [{
					breakpoint: 767,
						settings: {
							slidesToShow: (parseInt(slider_conf.slides_to_show) > 3) ? 3 : parseInt(slider_conf.slides_to_show),
							slidesToScroll: 1,
							dots: true
						}
					},
					{
						breakpoint: 640,
						settings: {
							slidesToShow: (parseInt(slider_conf.slides_to_show) > 2) ? 2 : parseInt(slider_conf.slides_to_show),
							slidesToScroll: 1
						}
					},
					{
						breakpoint: 479,
						settings: {
							slidesToShow: 1,
							slidesToScroll: 1
						}
					},
					{
						breakpoint: 319,
						settings: {
							slidesToShow: 1,
							slidesToScroll: 1
						}
					}
				]
			});
		}
	});
});
