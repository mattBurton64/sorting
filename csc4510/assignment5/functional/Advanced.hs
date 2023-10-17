-- This Haskell program is designed to simulate the game Bizz Buzz
-- If a number contains a 3 or is a multiple of 3 return bizz
-- If a number contains a 7 or is a multiple of 7 return buzz
-- If a number satisfies multiple conditions, return a combination of the appropriate bizzes and buzzes
-- If a number satisfies no conditions, return the number
module Advanced (main) where

-- Define a function to check if a number contains the digit 3
containsThree :: Int -> Bool -- Takes in an integer and returns a bool
containsThree n = '3' `elem` show n -- Checks if 3 is an element of the string n 

-- Define a function to check if a number contains the digit 7
containsSeven :: Int -> Bool -- Takes in an integer and returns a bool
containsSeven n = '7' `elem` show n -- Checks if 7 is an element of the string n

-- Generate a list comprehension for numbers from 1 to 19
outputList :: [String] -- Creates a list of strings
outputList = [output x | x <- [1..19]] -- Applies the output function to x for x from 1 to 19 
  --"Where" cases provided by chatGPT
  where
    output x = if null result then show x else concat [result] -- If x meets no conditions then return x, otherwise return the list of conditions x satisfies
      where
        result = concatMap checkConditions [(x `mod` 3 == 0, "bizz"), (x `mod` 7 == 0, "buzz"), (containsThree x, "bizz"), (containsSeven x, "buzz")] -- Maps through the rules of bizz buzz and passes each into the checkConditions function
    
    -- Check conditions and return corresponding strings
    checkConditions :: (Bool, String) -> String -- Takes in a bool and a string and outputs a string
    checkConditions (True, s) = s -- If x meets the condition, return the associated string
    checkConditions (False, _) = "" -- If x doesnt meet the condition, return an empty string

main :: IO ()
main = do
  putStrLn (unwords outputList) -- Print the elements of the output list separated by spaces