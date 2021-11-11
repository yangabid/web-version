<div class="logo">
        <h4><a href=".?page=dashboard">Yanga <strong>Bid</strong></a></h4>
    </div>
<nav id="sidebar" class="sidebar nav-collapse collapse">
    <ul id="side-nav" class="side-nav">
        <li>
            <a href=".?page=dashboard"><i class="fa fa-home"></i> <span class="name">Dashboard</span></a>
        </li>
		<li class="panel ">
            <a class="accordion-toggle collapsed" data-toggle="collapse"
               data-parent="#side-nav" href="#items"><i class="fa fa-shopping-cart"></i> <span class="name">Items</span></a>
            <ul id="items" class="panel-collapse collapse ">
                <li class=""><a href=".?page=create-item">New Item</a></li>
                <li class=""><a href=".?page=list-item">View All</a></li>
            </ul>
        </li>
		<li class="panel ">
            <a class="accordion-toggle collapsed" data-toggle="collapse"
               data-parent="#side-nav" href="#auction"><i class="fa fa-clock-o"></i> <span class="name">Auction System</span></a>
            <ul id="auction" class="panel-collapse collapse ">
                <li class=""><a href=".?page=create-auction">New Auction</a></li>
                <li class=""><a href=".?page=closed-auction">Closed Auction</a></li>
                <li class=""><a href=".?page=list-auction">Current Auction</a></li>
            </ul>
        </li>
		<li class="panel ">
            <a class="accordion-toggle collapsed" data-toggle="collapse"
               data-parent="#side-nav" href="#bid-pack"><i class="fa fa-dollar"></i> <span class="name">Bid System</span></a>
            <ul id="bid-pack" class="panel-collapse collapse ">
                <!-- <li class=""><a href=".?page=create-bid">Create Pack</a></li>
                <li class=""><a href=".?page=list-bid">View All Pack</a></li> -->
				<li class=""><a href=".?page=topup">Fund Wallet</a></li>
            </ul>
        </li>
		<li>
            <a href=".?page=customers-list"><i class="fa fa-users"></i> <span class="name">Customers</span></a>
        </li>
		<li>
            <a href=".?page=transaction-list"><i class="fa fa-exchange"></i> <span class="name">Transactions</span></a>
        </li>
        <li>
            <a href=".?page=search"><i class="fa fa-search"></i> <span class="name">Search Engine</span></a>
        </li>
		<li>
            <a href=".?page=logout"><i class="fa fa-power-off"></i> <span class="name">Sign out</span></a>
        </li>
    </ul>
</nav>
    <div class="wrap">
        <header class="page-header">
            <div class="navbar">
                <ul class="nav navbar-nav navbar-right pull-right">
                    <li class="visible-phone-landscape">
                        <a href="#" id="search-toggle">
                            <i class="fa fa-search"></i>
                        </a>
                    </li>
                    <li class="hidden-xs dropdown">
                        <a href="#" title="Account"  style="color:#fff;" id="account" class="dropdown-toggle" data-toggle="dropdown">
                            <i class="glyphicon glyphicon-user"></i>
                        </a>
                        <ul id="account-menu" class="dropdown-menu account" role="menu">
                            <li role="presentation" class="account-picture">
                                <img src="img/avatars/default.png" alt="" class="img-circle">
                                <?php
									echo $_SESSION['user_name'];
								?>
                            </li>
                        </ul>
                    </li>
                    <li class="visible-xs">
                        <a style="color:yellow !important;" href="#" class="btn-navbar" data-toggle="collapse" data-target=".sidebar" title="">
                            <i class="fa fa-bars"></i>
                        </a>
                    </li>
                    <li class="hidden-xs"><a href=".?page=logout" style="color:#fff;"><i class="glyphicon glyphicon-off"></i></a></li>
                </ul>
                <!--
                <form id="search-form" class="navbar-form pull-right" role="search">
                    <input type="search" class="form-control search-query" placeholder="Search...">
                </form> -->
            </div>
        </header>