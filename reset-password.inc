<?php @session_start(); ?>
<!--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            Start Page Title Area
        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-->
        <div class="page-title-area bg-white-smoke">
            <div class="container">
                <div class="row">
                    <div class="col-12">
                        <div class="page-header-content text-center">
                            <div class="page-header-caption">
                                <h2 class="page-title">Password Reset</h2>
                            </div><!--~~./ page-header-caption ~~-->
                            <div class="breadcrumb-area">
                                <ol class="breadcrumb">
                                    <li class="breadcrumb-item"><a href="./">Home</a></li>  
                                    <li class="breadcrumb-item active">Password Reset</li>
                                </ol>
                            </div><!--~~./ breadcrumb-area ~~-->
                        </div><!--~~./ page-header-content ~~-->
                    </div>
                </div>
            </div><!--~~./ end container ~~-->
        </div><!--~~./ end page title area ~~--> 

        <!--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            User Signin Block
        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-->
        <div class="user-signup-block ptb-120">
            <div class="bg-left bg-image" style="background-image: url('assets/images/shape/signup-shape.png')"></div>
            <div class="container">
                <div class="row">
                    <div class="col-lg-6">
                        <div class="sing-in-mockup md-mrb-60">
                            <img src="assets/images/others/signin-mockup.png" alt="Mockup">
                        </div>
                    </div><!--/.col-lg-2-->
                    <div class="col-lg-6">
                        <div class="user-register-area">
                            <div class="form-content">
                                <div class="card bg-primary">
									<div class="card-body">
										<h3 style="color:#fff;"><?php @session_start(); print $_SESSION['user']['first_name'].' '.$_SESSION['user']['last_name']; ?> </h3> 
										<p style="color:#fff;">Enter the code sent to your registered phone number and choose a new password below to reset your password.</p>
                                        <div class="">
                                            <div class="form-group">
                                                <div class="d-flex justify-content-between">
                                                    <label for="newpass" style="color:#fff">New Password</label>
                                                    <div class="custom-control custom-switch">
                                                        <input type="checkbox" onclick="showPass()" class="custom-control-input" id="customSwitch">
                                                        <label class="custom-control-label" for="customSwitch">Show Password</label>
                                                    </div>
                                                </div>
                                                <input type="password" id="newpass" name="new-pass" class="form-control" placeholder="Enter a new password" />
                                            </div>
                                            <script>
    function showPass() {
    var x = document.getElementById("newpass");
    if (x.type === "password") {
        x.type = "text";
    } else {
        x.type = "password";
    }
    }
    </script>
                                            
                                            <label for="otp-code" style="color:#fff">OTP Code</label>
                                            <div class="form-group">
                                                <input type="text" id="otp-code" class="form-control" placeholder="OTP code">
                                            </div>
                                            <button class="btn btn-white btn-default reset-password">Reset</button>
                                        </div>
                                        <div class="reset-res mt-3"></div>
									</div>
								</div>
                            </div>
                        </div><!--~./ end user register area ~--> 
                    </div><!-- /.col-lg-10 -->
                </div><!-- /.row -->
            </div><!-- /.container -->
        </div><!--~~./ end user signup block ~~-->