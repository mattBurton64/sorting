<!DOCTYPE html>
<html>
  <head>
    <title>Title Text</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="style.css">
    <style type=text/css>
      .bg {
        background-image: url(images/sportsballs-collage.jpg);
        background-repeat: no-repeat;
        background-size: cover;
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

    <h1 class=center style="padding: 5vw 0 1vw 0">Sign In</h1>

    <form class=center style="padding:1vw 0 7vw 0">
      <label for="email">Email: </label>
      <input type="email" required tabindex=1><br>        
      <label for="password">Password: </label>
      <input type="password" required tabindex=2><br>
        
      <input type="submit" tabindex=3></input>
      <input type="reset" tabindex=4></input> 
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
