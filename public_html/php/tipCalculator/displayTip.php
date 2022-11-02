<?php
    // get the data from the form
    $subtotal = $_POST['subtotal'];
    $tipPercent = $_POST['tipPercent'];
    
    // calculate the discount
    $tip = $subtotal * ($tipPercent * .01);
    $total = $subtotal + $tip;
    
    // apply currency formatting to the dollar and percent amounts
    $subtotalFormatted = "$".number_format($subtotal, 2);
    $tipPercentFormatted = $tipPercent."%";
    $tipFormatted = "$".number_format($tip, 2);
    $totalFormatted = "$".number_format($total, 2);            
    
?>
<!DOCTYPE html>
<html>
<head>
    <title>Tip Calculator</title>
    <link rel="stylesheet" type="text/css" href="main.css">
</head>
<body>
    <main>
        <h1>Tip Calculator</h1>

        <label>Subtotal:</label>
        <span><?php echo $subtotalFormatted; ?></span><br>

        <label>Tip Percent:</label>
        <span><?php echo $tipPercentFormatted; ?></span><br>

        <label>Tip:</label>
        <span><?php echo $tipFormatted; ?></span><br>

        <label>Total:</label>
        <span><?php echo $totalFormatted; ?></span><br>

        <div id="buttons">
          <label>&nbsp;</label>
          <a href="tipCalculator.html"><input type="reset" value="Reset"></a><br>
        </div>


    </main>
</body>
</html>
