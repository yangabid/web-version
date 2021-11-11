<!--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            Start Page Title Area
        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-->
        <div class="page-title-area bg-white-smoke">
            <div class="container">
                <div class="row">
                    <div class="col-12">
                        <div class="page-header-content text-center">
                            <div class="page-header-caption">
                                <h2 class="page-title">My Account</h2>
                            </div><!--~~./ page-header-caption ~~-->
                            <div class="breadcrumb-area">
                                <ol class="breadcrumb">
                                    <li class="breadcrumb-item"><a href="./">Home</a></li>  
                                    <li class="breadcrumb-item active">Sign Up</li>
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
                                <div class="form-header">
                                    <h4 class="form-subheading">Sign Up here</h4>
                                    <h2 class="heading">Welcome to Yangabid</h2>
                                </div>
                                <?php
									if(isset($_SESSION['msg'])) {
										print $_SESSION['msg'];
										unset($_SESSION['msg']);
									}
								?>
                                <form class="default-form signup-form" action="register.php" method="POST">
                                    <div class="row">
                                        <div class="col-lg-6">
                                            <div class="form-group">
                                                <label for="f_name">First Name</label>
                                                <input id="f_name" name="f_name" class="form-controller" type="text" required>
                                            </div><!--/.form-group-->
                                        </div>
                                        <div class="col-lg-6">
                                            <div class="form-group">
                                                <label for="l_name">Last Name</label>
                                                <input id="l_name" name="l_name" class="form-controller" type="text" required>
                                            </div><!--/.form-group-->
                                        </div>
                                        <div class="col-lg-6">
                                            <div class="form-group">
                                                <label for="phone">Phone</label>
                                                <input id="phone" name="phone" class="form-controller" type="text" required>
                                            </div><!--/.form-group-->
                                        </div>
                                        <div class="col-lg-6">
                                            <div class="form-group">
                                                <label for="email">Email Address</label>
                                                <input id="email" name="email" class="form-controller" type="email" required>
                                            </div><!--/.form-group-->
                                        </div>
                                        <div class="col-lg-6">
                                            <div class="form-group">
                                                <label for="pass">Password</label>
                                                <input id="pass" name="password" class="form-controller" type="password" required>
                                            </div><!--/.form-group-->
                                        </div>
                                        <div class="col-lg-6">
                                            <div class="form-group">
                                                <label for="con_pass"> Confirm Password</label>
                                                <input id="con_pass" name="password2" class="form-controller" type="password" required>
                                            </div><!--/.form-group-->
                                        </div>
                                        <div class="col-lg-6">
                                            <div class="form-group">
                                                <label for="pass">State of Residence</label>
                                                <select name="state" class="form-controller" required>
                                                    <option value="" disabled selected="selected">Select</option>
                                                    <option value="Abuja FCT">Abuja FCT</option>
                                                    <option value="Abia">Abia</option>
                                                    <option value="Adamawa">Adamawa</option>
                                                    <option value="Akwa Ibom">Akwa Ibom</option>
                                                    <option value="Anambra">Anambra</option>
                                                    <option value="Bauchi">Bauchi</option>
                                                    <option value="Bayelsa">Bayelsa</option>
                                                    <option value="Benue">Benue</option>
                                                    <option value="Borno">Borno</option>
                                                    <option value="Cross River">Cross River</option>
                                                    <option value="Delta">Delta</option>
                                                    <option value="Ebonyi">Ebonyi</option>
                                                    <option value="Edo">Edo</option>
                                                    <option value="Ekiti">Ekiti</option>
                                                    <option value="Enugu">Enugu</option>
                                                    <option value="Gombe">Gombe</option>
                                                    <option value="Imo">Imo</option>
                                                    <option value="Jigawa">Jigawa</option>
                                                    <option value="Kaduna">Kaduna</option>
                                                    <option value="Kano">Kano</option>
                                                    <option value="Katsina">Katsina</option>
                                                    <option value="Kebbi">Kebbi</option>
                                                    <option value="Kogi">Kogi</option>
                                                    <option value="Kwara">Kwara</option>
                                                    <option value="Lagos">Lagos</option>
                                                    <option value="Nassarawa">Nassarawa</option>
                                                    <option value="Niger">Niger</option>
                                                    <option value="Ogun">Ogun</option>
                                                    <option value="Ondo">Ondo</option>
                                                    <option value="Osun">Osun</option>
                                                    <option value="Oyo">Oyo</option>
                                                    <option value="Plateau">Plateau</option>
                                                    <option value="Rivers">Rivers</option>
                                                    <option value="Sokoto">Sokoto</option>
                                                    <option value="Taraba">Taraba</option>
                                                    <option value="Yobe">Yobe</option>
                                                    <option value="Zamfara">Zamfara</option>
                                                </select>
                                            </div><!--/.form-group-->
                                        </div>
                                        <div class="col-lg-6">
                                            <div class="form-group">
                                                <label for="con_pass">Country</label>
                                                <select disabled class="form-controller">
                                                    <option>Nigeria</option>
                                                </select>
                                            </div><!--/.form-group-->
                                        </div>
                                    </div>
                                    <div class="login-form-remember"> 
                                        <label><input id="18above" value="" type="checkbox" required><span> I certify that i am 18 years and above</span></label>
                                    </div>

                                    <div class="login-form-remember"> 
                                        <label><input id="termssignin" value="" type="checkbox" required><span>I agree to the <a >Terms, Privacy policy and fees</a></span></label>
                                    </div>
                                    <div class="login-form-remember"> 
                                        <label><input id="remembermesignin" value="" type="checkbox"><span>Yes, I want to receive Email </span></label>
                                    </div>

                                    <div class="form-btn-group">
                                        <div class="form-login-area">
                                            <button type="submit" class="btn btn-default btn-primary">
                                                Sign Up
                                            </button>
                                        </div>
                                        <div class="login-form-register-now">
                                            You have an account ? <a class="btn-register-now" href=".?page=signin">Sign In</a>
                                        </div>
                                    </div>
									<!--
                                    <div class="reg-others-media">
                                        <div class="text">Or, User social media to sign in</div>
                                        <div class="social-media-icons">
                                            <a href="signup.html#"><i class="fab fa-facebook-f"></i></a>
                                            <a href="signup.html#"><i class="fab fa-twitter"></i></a><a href="signup.html#"><i class="fab fa-linkedin-in"></i></a>
                                        </div>
                                    </div>
									-->
                                </form>  
                            </div>
                        </div><!--~./ end user register area ~--> 
                    </div><!-- /.col-lg-10 -->
                </div><!-- /.row -->
            </div><!-- /.container -->
        </div><!--~~./ end user signup block ~~-->