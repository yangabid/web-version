<!--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            Start Page Title Area
        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-->
        <div class="page-title-area bg-white-smoke">
            <div class="container">
                <div class="row">
                    <div class="col-12">
                        <div class="page-header-content text-center">
                            <div class="page-header-caption">
                                <h2 class="page-title">Auction Winners</h2>
                            </div><!--~~./ page-header-caption ~~-->
                            <div class="breadcrumb-area">
                                <ol class="breadcrumb">
                                    <li class="breadcrumb-item"><a href="./">Home</a></li>  
                                    <li class="breadcrumb-item active">Winners</li>
                                </ol>
                            </div><!--~~./ breadcrumb-area ~~-->
                        </div><!--~~./ page-header-content ~~-->
                    </div>
                </div>
            </div><!--~~./ end container ~~-->
        </div><!--~~./ end page title area ~~--> 

        <!--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            Start Winner Page Block
        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-->
		<?php
			$list = mysqli_query(Yanga::db(), "select * from winners order by created_date desc");
			if(mysqli_num_rows($list) > 0) {
			?>
        <div class="winner-page-block ptb-120">
            <div class="container">
                <div class="row justify-content-center winner-list-area">
			<?php
				while($win = mysqli_fetch_array($list)) {
				$user = mysqli_fetch_array(mysqli_query(Yanga::db(), 'select * from profile where profile_id = "'.$win['profile_id'].'"'));
				$item = mysqli_fetch_array(mysqli_query(Yanga::db(), 'select * from bid_items where item_id = "'.$win['item_id'].'"'));
				?>
				<div class="col-lg-3 col-md-4 col-sm-6 col-6">
					<div class="winner-item">
						<div class="winner-thumb">
						    <?php
						        if(strlen($user['profile_pics']) > 4) {
						            print '<img src="'.$user['profile_pics'].'" alt="'.stripslashes($user['first_name'].' '.$user['last_name']).'">';
						        } else {
						            print '<img src="assets/images/winner/default.png" alt="img">';
						        }
						    ?>
							
							<div class="winner-auction-product">
								<div class="product-icon">
									<span class="icon-gift"></span>
								</div>
								<div class="product-thumb">
									<img src="<?php print stripslashes($item['pics_1']); ?>" alt="<?php print stripslashes($item['title']); ?>">
								</div>
							</div>
						</div><!-- /.winner-thumb -->
						<div class="info">
							<h4 class="winner-name"><?php print stripslashes($user['first_name'].' '.$user['last_name']); ?></h4><!-- /.client-name -->
							<p class="auction-id">Auction Id: <a><?php print $win['auction_id']; ?></a><br /><?php print date("j M Y", strtotime($win['created_date'])) ?></p>
						</div><!-- /.info -->
					</div><!-- /.winner-item -->
				</div><!-- /.col-lg-3 -->
				<?php
				}
			}
			?>
                    <div class="col-12">
                        <!--~~~~~ Start Paging Navigation ~~~~~-->
						<!--
                        <nav class="paging-navigation paging-center pd-t-60">
                            <ul class="nav-links">                                   
                                <li><a href="winner.html#">01</a></li>
                                <li class="active"><a href="winner.html#" class="page-numbers">02</a></li>
                                <li><a href="winner.html#" class="page-numbers">03</a></li>
                                <li class="nav-next">
                                    <a href="winner.html#"><span class="icon-next1"></span></a>
                                </li>  
                            </ul>
                        </nav>
						-->
                    </div>
                </div>
            </div>    
        </div><!--~./ end winner page block ~-->