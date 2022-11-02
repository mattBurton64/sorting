<?php
require_once('database.php');


?>
<!DOCTYPE html>
<html>
  <head>
    <title>Title Text</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="style.css">
    <style type=text/css>
    .line {
      border-color: #fcce58;
    }
    </style>
  </head>
  <body>
    <nav class=line>
      <ul>
        <li><a href="index.html">HOME</a></li>      
        <li><a href="shop.php">SHOP</a></li>
        <li><a href="checkout.php">CHECKOUT</a></li>
        <li style="float:right;padding: 0 3vw 0 0;"><a href="sign-in.php">SIGN IN</a></li>
        <li style=float:right><a href="register.php">REGISTER</a></li>
      </ul>
    </nav> 
     
    <h1 class=center>Register</h1>

    <form action="new-member.php" method="post">  
      <label for="Name">Name: </label><br>
      
      <div class=center>
         <input type="text" name=first placeholder="First" required tabindex=1><br>
         <input type="text" name=middle placeholder="Middle" tabindex=2><br>
         <input type="text" name=last placeholder="Last" required tabindex=3><br>
      </div> 
      
      <label for="email">Email:</label><br>
      <div class=center>
        <input type="email" name=email required tabindex=4><br>
      </div>
      <label for="password">Password:</label><br>
      <div class=center>
        <input type="password" name=password required tabindex=5><br>
      </div>

      <fieldset>
         <legend>Gender</legend>
            <label for="male">Male</label>
            <input type="radio" id="male" name="gender" value="male" tabindex=6><br>
            <label for="female">Female</label>
            <input type="radio" id="female" name="gender" value="female" tabindex=7><br>
            <label for="other">Other</label><br>
            <input type="text" id="other" name="gender" placeholder="Please specify here..." tabindex=8><br>
      </fieldset><br>     

      <fieldset>
         <legend>Let us know what you're interested in seeing more</legend>
            <label for="foootball">Football</label>
            <input type="checkbox" id="football" tabindex=9><br>
            <label for="basketball">Basketball</label>
            <input type="checkbox" id="basketball" tabindex=10><br>
            <label for="soccer">Soccer</label>
            <input type="checkbox" id="soccer" tabindex=11><br>
            <label for="baseball">Baseball</label>
            <input type="checkbox" id="baseball" tabindex=12><br>
            <label for="lacrosse">Lacrosse</label>
            <input type="checkbox" id="lacrosse" tabindex=13><br>
            <label for="hockey">Hockey</label>
            <input type="checkbox" id="hockey" tabindex=14><br><br>
            <label for"suggestions">Suggestions</label><br>
            <textarea placeholder="Leave suggestions here..." tabindex=15></textarea>
      </fieldset><br>
      
      <div class=center>
        <input type="submit" tabindex=16></input>
        <input type="reset" tabindex=17></input>
      </div>

    </form>

    <nav class=line>
      <ul>
        <li><a href="index.html">HOME</a></li>      
        <li><a href="shop.php">SHOP</a></li>
        <li><a href="checkout.php">CHECKOUT</a></li>
        <li style="float:right;padding: 0 3vw 0 0;"><a href="sign-in.php">SIGN IN</a></li>
        <li style=float:right><a href="register.php">REGISTER</a></li>
      </ul>
    </nav> 

    <footer>
      <p>Copyright &copy; <script>document.write(new Date().getFullYear())</script> Matthew Burton</p>
    </footer> 
  </body>
</html>
