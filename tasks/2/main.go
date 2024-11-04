package main

import (
	"fmt"
)

func a() {
	x := []int{}
	x = append(x, 0)  // [0] len: 1 cap: 1
	x = append(x, 1)  // [0 1] len: 2 cap: 2
	x = append(x, 2)  // [0 1 2] len: 3 cap: 4
	y := append(x, 3) // [0 1 2 3] len: 4 cap: 4
	z := append(x, 4) // [0 1 2 4] len: 4 cap: 4 // тут берем слайс x [0 1 2] и добавляем 4, но операция производится над тем же базовым массивом, что и выше
	fmt.Println(z, len(z), cap(z))
	fmt.Println(y, z)
}

func main() {
	a()
}
