package main

import "fmt"

func main() {
	fmt.Println(handle() == nil)
	println(handle())
}

type CustomError struct {
	data string
}

func (e CustomError) Error() string {
	return e.data
}

func handle() error {
	err := &CustomError{data: "some error"}
	return err
}
