-- This Haskell program is intended to test that the environment is set up to compile and run programs
-- Additionally, the doubleMe function can be executed through GHC and takes in any integer and doubles it
module Simple (main) where

main :: IO () -- The main function interacts with th ecommand line interface
main = do -- The following line will be executed when Simple.hs is run
  putStrLn "hello world" -- This prints "hello world" to the command line

-- Defines a function to take in an integer and doubles it
doubleMe :: Int -> Int
doubleMe x = x + x