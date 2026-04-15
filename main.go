package main

import "log"

func main() {
	data := []int{1, 2, 3, 4}
	value := 5
	offset := 0
	offset = len(data) - offset
	if offset > len(data) {
		log.Fatal("offset is out of range")
	}
	data = append(data[:offset], append([]int{value}, data[offset:]...)...)
	log.Println(data)
	//for i := 0; i <= 100; i++ {
	//	fmt.Printf("%d: %c\n", i, i)
	//}
}
