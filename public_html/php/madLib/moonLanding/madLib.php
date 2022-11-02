<?php
    // get the data from the form
    $one = $_POST['one'];
    $two = $_POST['two'];
    $three = $_POST['three'];
    $four = $_POST['four'];
    $five = $_POST['five'];
    $six = $_POST['six'];
    $seven = $_POST['seven'];
    $eight = $_POST['eight'];
    $nine = $_POST['nine'];
    $ten = $_POST['ten'];
    $eleven = $_POST['eleven'];
    $twelve = $_POST['twelve'];
    $thirteen = $_POST['thirteen'];
    $fourteen = $_POST['fourteen'];
    $fifteen = $_POST['fifteen'];
    $sixteen = $_POST['sixteen'];
    $seventeen = $_POST['seventeen'];
    $eighteen = $_POST['eighteen'];
    $nineteen = $_POST['nineteen'];
    $twenty = $_POST['twenty'];
    $twentyone = $_POST['twentyone'];
    $twentytwo = $_POST['twentytwo'];
    
?>
<!DOCTYPE html>
<html>
<head>
    <title>Mad Lib</title>
    <link rel="stylesheet" type="text/css" href="main.css">
</head>
<body>
    <main>
        <h1>Mad Lib</h1>
        <p> On July  
        <?php echo $one; ?>
        1996, two American
        <?php echo $two; ?>
        were the first to
        <?php echo $three; ?>
        on the moon. This
        <?php echo $four; ?>
        trip took
        <?php echo $five; ?>
        days  to reach the moon from
        <?php echo $six; ?>
        as
        <?php echo $seven; ?>
        Armstrong and
        <?php echo $eight; ?>
        Aldrin
        <?php echo $nine; ?>
        onto the 
        <?php echo $ten; ?>
        of the moon, Armstrong
        <?php echo $eleven; ?>
        the famous words, "That's
        <?php echo $twelve; ?>
        <?php echo $thirteen; ?>
        step for a man, one 
        <?php echo $fourteen; ?>
        leap for mankind." Soon after, Aldrin
        <?php echo $fifteen; ?>
        onto the moon and together, they
        <?php echo $sixteen; ?>
        a U.S.
        <?php echo $seventeen; ?>
        on the surface. They
        <?php echo $eighteen; ?>
        <?php echo $nineteen; ?>
        from the moon's surface to
        <?php echo $twenty; ?>
        back to Earth and 
        <?php echo $twentyone; ?>
        returned home
        <?php echo $twentytwo; ?>
        days later.
        </p>

        <div id="buttons">
          <label>&nbsp;</label>
          <a href="madLib.html"><input type="reset" value="Reset"></a><br>
        </div>


    </main>
</body>
</html>

