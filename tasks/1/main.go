package main

import "fmt"

func main() {
	s := "test"
	fmt.Println(s[0])

	// замена через использование слайса рун
	data := []byte(s)
	data[0] = 'R'
	s = string(data)

	fmt.Println(s)
}
