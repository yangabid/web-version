<?php
@session_start();
if(isset($_POST['payref'])) {
    include('yanga.php');
    $bidder = $_SESSION['bidder'];
    $now = date('Y-m-d H:i:s');
    $payref = addslashes($_POST['payref']);
    $trans = addslashes($_POST['trans']);
    $status = addslashes($_POST['status']);
    $trxref = addslashes($_POST['trxref']);
    $msg = addslashes($_POST['msg']);
    $payment = mysqli_query(Yanga::db(), 'SELECT * FROM bid_purchase WHERE profile_id = "'.$bidder.'" and yanga_reference = "'.$trxref.'"');
    if(mysqli_num_rows($payment) == 1) {
        $data = mysqli_fetch_array($payment);
        $pass_day = ($data['amount']/100);
        $get_gate = mysqli_fetch_array(mysqli_query(Yanga::db(), 'SELECT * from profile_bid_account WHERE profile_id = "'.$bidder.'"'));
        $current_expiry = $get_gate['gate_pass_expiry'];
        $new_expiry = date('Y-m-d', strtotime($current_expiry. " + $pass_day days"));
        
        mysqli_query(Yanga::db(), 'UPDATE bid_purchase SET payment_reference="'.$payref.'",  payment_status="'.$status.'", payment_response = "'.$msg.'", updated_date = "'.$now.'" WHERE profile_id = "'.$bidder.'" AND reference = "'.$trxref.'"');
        
        if(mysqli_query(Yanga::db(), 'UPDATE profile_bid_account SET gate_pass_expiry = "'.$new_expiry.'", updated_date = "'.$now.'" WHERE profile_id = "'.$bidder.'"')) {
            print '<div class="card">
                <div class="card-body">
                    <h3>Gate pass successfully purchased</h3>
                    <p>You now have '.$pass_day.' pass to bid on any item</p>
                    <p>Reference: '.$payref.'</p>
                    <p>Response: '.$msg.'</p>
                    <p>Status: '.$status.'</p>
                </div>
            </div>';
        } else {
            print '<div class="alert alert-danger mt-3 mb-0"><i class="fa fa-info-circle"></i> Cannot display result at the moment, please retry.</div>';
        }
    }
} else {
    echo 'Invalid transaction';
}
?>