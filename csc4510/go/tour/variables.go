package main

import "fmt"

var i, j int = 1, 2 // package level varaible

func main() {
	k := 3 // short variable declaration
	c, python, java := true, false, "no!"

	fmt.Println(i, j, k, c, python, java)
}
