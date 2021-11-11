$('select#location').change(function() {
	var loc = $(this).val();
	var settings = {
		"url": "bid.php",
		"method": "POST",
		"mimeType": "multipart/form-data",
		"data": {'loc':loc, 'op':'update-location'}
	}
	$.ajax(settings).done(function (response) {
		location.reload();
	}).fail(function (jqXHR, textStatus, error) {
		location.reload();
	});	
});

$('.place-bid').click(function() {
	var bid = $(this).attr('auction');
	var settings = {
        "url": "bid.php",
        "method": "POST",
        "mimeType": "multipart/form-data",
        "data": {'bid':bid, 'op':'bid'}
    }

    $.ajax(settings).done(function (response) {
        $('.bid-output').html(response);
    }).fail(function (jqXHR, textStatus, error) {
        $('.bid-output').html('<div class="text-center mb-5 text-danger"><i class="fa fa-info-circle"></i> Cannot bid at the moment, please retry.</div>');
		return false;
    });	
});

$('.numberonly').keypress(function (e) {    
	var charCode = (e.which) ? e.which : event.keyCode    
	if (String.fromCharCode(charCode).match(/[^0-9]/g))    
	return false;                        
});

$('.do-reset').click(function() {
	var user = $('#phone_recover').val();
	var settings = {
        "url": "activate.php",
        "method": "POST",
        "mimeType": "multipart/form-data",
        "data": {'user':user, 'op':'reset'}
    }

    $.ajax(settings).done(function (response) {
        $('.reset-res').html(response);
    }).fail(function (jqXHR, textStatus, error) {
        $('.reset-res').html('<div class="text-center mb-5 text-danger"><i class="fa fa-info-circle"></i> Cannot bid at the moment, please retry.</div>');
		return false;
    });	
});

$('.reset-password').click(function() {
	var pass = $('#newpass').val();
	var otp = $('#otp-code').val();
	var settings = {
        "url": "activate.php",
        "method": "POST",
        "mimeType": "multipart/form-data",
        "data": {'pass':pass, 'otp': otp,'op':'do-reset'}
    }
    $.ajax(settings).done(function (response) {
        $('.reset-res').html(response);
    }).fail(function (jqXHR, textStatus, error) {
        $('.reset-res').html('<div class="text-center mb-5 text-danger"><i class="fa fa-info-circle"></i> Cannot reset password at the moment, please retry.</div>');
		return false;
    });	
});

$('input#bid').keyup(function() {
	var count = $('input#bid').val();
	if(count.length > 0) {
		var price = parseInt(count) * 100;
		$('.total-price').html("&#8358;"+price);
	} else {
		$('.total-price').html("&#8358;100");
	}
});

$('.dashboard-purchase').click(function() {
	$('.purchase-res').html("");
	var bid = $('input#bid').val();
	if(parseInt(bid)
	< 1) {
		$('.purchase-res').html('<div class="alert alert-danger mt-3 mb-0"><i class="fa fa-info-circle"></i> Minimum is One bid @ &#8358;100 per bid</div>');
		return false;
	} else if(parseInt(bid)
	> 1000) {
		$('.purchase-res').html('<div class="alert alert-danger mt-3 mb-0"><i class="fa fa-info-circle"></i> Maximum bid you can buy is 1,000</div>');
		return false;
	} else {
		$(this).attr({'disabled':'disabled'});
		var settings = {
			"url": "bid.php",
			"method": "POST",
			"mimeType": "multipart/form-data",
			"data": {'bid':bid, 'op':'purchase-bid'}
		}
		$.ajax(settings).done(function (response) {
			$('.purchase-res').html(response);
			setTimeout(function(){ location.reload(); }, 3000);
		}).fail(function (jqXHR, textStatus, error) {
			$('.purchase-res').html('<div class="alert alert-danger mt-3 mb-0"><i class="fa fa-info-circle"></i> Cannot purchase bid pack at the moment, please retry.</div>');
			return false;
		});	
	}
});

$('.profile-activation').click(function() {
	$('.activation-res').html('');
	var code = $('#activation-code').val();
	if(code.length < 1) {
		$('.activation-res').html('<div class="alert alert-danger mt-3 mb-0"><i class="fa fa-info-circle"></i> Please enter the activation code</div>');
	} else {
		$(this).attr({'disabled':'disabled'});
		var settings = {
			"url": "activate.php",
			"method": "POST",
			"mimeType": "multipart/form-data",
			"data": {'code':code}
		}
		$.ajax(settings).done(function (response) {
			$('.profile-activation').removeAttr('disabled');
			$('.activation-res').html(response);
		}).fail(function (jqXHR, textStatus, error) {
			$('.activation-res').html('<div class="alert alert-danger mt-3 mb-0"><i class="fa fa-info-circle"></i> Cannot activate account at the moment, please retry.</div>');
			$('.profile-activation').removeAttr('disabled');
			return false;
		});	
	}
});

$('.resend-code').click(function() {
	$('.activation-res').html('');
	var confirm_resend = confirm("Are you sure?");
	if(!confirm_resend) {
		return false;
	} else {
		$(this).attr({'disabled':'disabled'});
		var settings = {
			"url": "resend-code.php",
			"method": "POST",
			"mimeType": "multipart/form-data",
		}
		$.ajax(settings).done(function (response) {
			$('.resend-code').removeAttr('disabled');
			$('.activation-res').html(response);
		}).fail(function (jqXHR, textStatus, error) {
			$('.activation-res').html('<div class="alert alert-danger mt-3 mb-0"><i class="fa fa-info-circle"></i> Cannot resend activation code at the moment, please retry.</div>');
			$('.resend-code').removeAttr('disabled');
			return false;
		});	
	}
});

$('.auction-res').click(function() {
    var auction = $(this).attr('aval');
    $('.result-container').html('<div class="text-center mt-3 mb-3"><i class="fas fa-spin fa-spinner fa-3x"></i></center>');
    var settings = {
		"url": "result-checkup.php",
		"method": "POST",
		"data": {auction:auction},
	}
	$.ajax(settings).done(function (response) {
		$('.result-container').html(response);
	}).fail(function (jqXHR, textStatus, error) {
		$('.result-container').html('<div class="alert alert-danger mt-3 mb-0"><i class="fa fa-info-circle"></i> Cannot display result at the moment, please retry.</div>');
		return false;
	});
});